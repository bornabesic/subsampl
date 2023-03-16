/**
 * Copyright (C) 2021 Borna Bešić
 *
 * This file is part of subsampl.
 *
 * subsampl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * subsampl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with subsampl.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cmath>
#include <cstdint>
#include <numeric>
#include <thread>
#include <vector>

#include "subsampl.hpp"
#include "types.hpp"

static void _chunk_compute_inside_radius_3d(
    const float32 *data, const float32 *origin, std::vector<uint32_t> &indices,
    const uint32_t start, const uint32_t end, const float32 radius) {

    const auto &x_origin = origin[0];
    const auto &y_origin = origin[1];
    const auto &z_origin = origin[2];

    const auto radius_squared = radius * radius;

    for (uint32_t i = start; i < end; ++i) {
        const auto offset = i * 3;
        const auto &x = data[offset];
        const auto &y = data[offset + 1];
        const auto &z = data[offset + 2];

        const auto dx = x - x_origin;
        const auto dy = y - y_origin;
        const auto dz = z - z_origin;

        if ((dx * dx + dy * dy + dz * dz) <= radius_squared)
            indices.push_back(i);
    }
}

std::vector<uint32_t> *radius_select_3d(const float32 *data,
                                        const uint32_t nrows,
                                        const float32 *origin,
                                        const float32 radius) {

    if (nrows == 0)
        return new std::vector<uint32_t>();

    /*  */
    auto nthreads = std::thread::hardware_concurrency();
    const uint32_t chunk_size = std::ceil((float32)nrows / nthreads);
    nthreads = std::ceil((float32)nrows / chunk_size);

    std::vector<std::vector<uint32_t>> indices(nthreads);
    std::vector<std::thread> threads;
    for (unsigned int t = 0; t < nthreads; ++t) {
        const uint32_t start = t * chunk_size;
        const uint32_t end = std::min(start + chunk_size, nrows);
        indices[t].reserve(end - start);
        threads.emplace_back(_chunk_compute_inside_radius_3d, data, origin,
                             std::ref(indices[t]), start, end, radius);
    }

    for (auto &thread : threads)
        thread.join();

    auto ntotal = std::accumulate(
        indices.begin(), indices.end(), 0,
        [](const uint32_t sum, const std::vector<uint32_t> &indices) {
            return sum + indices.size();
        });

    std::vector<uint32_t> *indices_merged =
        new std::vector<uint32_t>(std::move(indices[0]));
    indices_merged->reserve(ntotal);

    for (unsigned int t = 1; t < nthreads; ++t) {
        const auto &indices_chunk = indices[t];
        indices_merged->insert(indices_merged->end(), indices_chunk.begin(),
                               indices_chunk.end());
    }

    return indices_merged;
}

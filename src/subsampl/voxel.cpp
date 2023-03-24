/**
 * Copyright (C) 2023 Borna Bešić
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
#include <thread>
#include <vector>

#include "hashmap.hpp"
#include "voxel.hpp"
#include <subsampl/subsampl.hpp>
#include <subsampl/types.hpp>

namespace subsampl {

std::vector<uint32_t> *voxel_grid_subsample_3d(const float32 *data,
                                               const uint32_t nrows,
                                               const float32 voxel_size) {

    if (nrows == 0)
        return new std::vector<uint32_t>();

    /* Find the bounding coordinates */
    float32 x_min = data[0];
    float32 x_max = x_min;

    float32 y_min = data[1];
    float32 y_max = y_min;

    float32 z_min = data[2];
    float32 z_max = z_min;

    for (uint32_t i = 0; i < nrows; ++i) {
        const auto offset = i * 3;
        const auto &x = data[offset];
        const auto &y = data[offset + 1];
        const auto &z = data[offset + 2];

        x_min = std::min(x_min, x);
        y_min = std::min(y_min, y);
        z_min = std::min(z_min, z);

        x_max = std::max(x_max, x);
        y_max = std::max(y_max, y);
        z_max = std::max(z_max, z);
    }

    /* Number of cells for each dimension */
    const uint64_t ny = std::max(
        static_cast<uint64_t>(std::ceil((y_max - y_min) / voxel_size)), 1UL);
    const uint64_t nz = std::max(
        static_cast<uint64_t>(std::ceil((z_max - z_min) / voxel_size)), 1UL);

    /* Compute voxel index for each point */
    auto nthreads = std::thread::hardware_concurrency();
    const uint32_t chunk_size =
        std::ceil(static_cast<float32>(nrows) /
                  nthreads); // NOLINT(cppcoreguidelines-narrowing-conversions)
    nthreads = std::ceil(
        static_cast<float32>(nrows) /
        chunk_size); // NOLINT(cppcoreguidelines-narrowing-conversions)

    std::vector<std::vector<uint64_t>> point_to_voxels(nthreads);
    std::vector<std::thread> threads;
    for (unsigned int t = 0; t < nthreads; ++t) {
        const uint32_t start = t * chunk_size;
        const uint32_t end = std::min(start + chunk_size, nrows);
        point_to_voxels[t].resize(end - start);
        threads.emplace_back(chunk_compute_voxel_index_3d, data,
                             std::ref(point_to_voxels[t]), start, end,
                             voxel_size, x_min, y_min, z_min, ny, nz);
    }

    for (auto &thread : threads)
        thread.join();

    /* Select a single point per voxel by using a hashmap */
    grouping_hashmap<uint64_t, uint32_t> map(nrows);
    for (unsigned int t = 0; t < nthreads; ++t) {
        const auto &point_to_voxel = point_to_voxels[t];
        const uint32_t start = t * chunk_size;
        for (uint32_t i = 0; i < point_to_voxel.size(); ++i) {
            const auto &v = point_to_voxel[i];
            map.insert(v, i + start);
        }
    }
    map.squeeze();

    return map.move_values();
}
} // namespace subsampl

static void chunk_compute_voxel_index_3d(
    const float32 *data, std::vector<uint64_t> &point_to_voxel,
    const uint32_t start, const uint32_t end, const float32 voxel_size,
    const float32 x_min, const float32 y_min, const float32 z_min,
    const uint64_t ny, const uint64_t nz) {

    for (uint32_t i = start; i < end; ++i) {
        const auto offset = i * 3;
        const auto &x = data[offset];
        const auto &y = data[offset + 1];
        const auto &z = data[offset + 2];

        const auto vi = static_cast<uint64_t>((x - x_min) / voxel_size);
        const auto vj = static_cast<uint64_t>((y - y_min) / voxel_size);
        const auto vk = static_cast<uint64_t>((z - z_min) / voxel_size);

        const uint64_t v = vi * ny * nz + vj * nz + vk;

        point_to_voxel[i - start] = v;
    }
}

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


#include <array>
#include <cmath>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "subsampl.hpp"
#include "types.hpp"

std::vector<uint32_t> *voxel_grid_subsample_3d(
    const float32 *data, const uint32_t nrows, const float32 voxel_size){

    /* Find the bounding coordinates */
    float32 x_min = data[0];
    float32 x_range = x_min;

    float32 y_min = data[1];
    float32 y_range = y_min;

    float32 z_min = data[2];
    float32 z_range = z_min;

    for (uint32_t i = 0; i < nrows; ++i) {
        const auto offset = i * 3;
        const auto& x = data[offset];
        const auto& y = data[offset + 1];
        const auto& z = data[offset + 2];

        x_min = std::min(x_min, x);
        y_min = std::min(y_min, y);
        z_min = std::min(z_min, z);

        x_range = std::max(x_range, x);
        y_range = std::max(y_range, y);
        z_range = std::max(z_range, z);
    }

    /* Make a grid - maps a voxel index to a point index*/
    std::unordered_map<uint64_t, uint32_t> grid;
    grid.reserve(nrows);

    /* Number of cells for each dimension */
    const uint64_t nx = std::ceil((x_range - x_min) / voxel_size);
    const uint64_t ny = std::ceil((y_range - y_min) / voxel_size);
    const uint64_t nz = std::ceil((z_range - z_min) / voxel_size);

    /* Subsample */
    for (uint32_t i = 0; i < nrows; ++i) {
        const auto offset = i * 3;
        const auto& x = data[offset];
        const auto& y = data[offset + 1];
        const auto& z = data[offset + 2];

        const uint64_t vi = (x - x_min) / voxel_size;
        const uint64_t vj = (y - y_min) / voxel_size;
        const uint64_t vk = (z - z_min) / voxel_size;

        const uint64_t v = vi * ny * nz + vj * nz + vk;

        grid[v] = i;
    }

    /* Return indices of subsampled points */
    auto *indices = new std::vector<uint32_t>();

    for (auto it = grid.cbegin(); it != grid.cend();) {
        indices->push_back(it->second);
        it = grid.erase(it);
    }

    return indices;
}

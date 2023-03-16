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

#include <cstdlib>
#include <iostream>
#include <vector>

#include <subsampl/subsampl.hpp>
#include <subsampl/types.hpp>

constexpr float32 x_range = 1000;
constexpr float32 y_range = 1000;
constexpr float32 z_range = 30;
constexpr float32 voxel_size = 0.025;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./example <n>" << '\n';
        return 1;
    }

    uint32_t n;
    {
        char *end;
        n = std::strtol(argv[1], &end, 10);
        if (*end != 0) {
            std::cout << "Invalid number.\n";
            return 1;
        }
    }

    // Generate a random point cloud
    std::vector<float32> data(n * 3);
    for (uint32_t i = 0; i < n; ++i) {
        const auto offset = i * 3;
        data[offset] = static_cast<float32>(std::rand()) / RAND_MAX * x_range;
        data[offset + 1] =
            static_cast<float32>(std::rand()) / RAND_MAX * y_range;
        data[offset + 2] =
            static_cast<float32>(std::rand()) / RAND_MAX * z_range;
    }
    std::cout << "Points: " << n << '\n';

    // Get indices of subsampled points
    auto *indices_ptr = voxel_grid_subsample_3d(&data[0], n, voxel_size);
    const auto &indices = *indices_ptr;
    std::cout << "Points (subsampled): " << indices.size() << '\n';

    // Subsample the point cloud using the indices
    for (const auto index : indices) {
        const auto offset = index * 3;
        const auto x = data[offset];
        const auto y = data[offset + 1];
        const auto z = data[offset + 2];
        // Do something with (x, y, z)
        // ...
    }

    delete indices_ptr;

    return 0;
}

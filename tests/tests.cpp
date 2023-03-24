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

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <subsampl/subsampl.hpp>

namespace ss = subsampl;

TEST_CASE("Points are subsampled within voxels", "[voxel]") {
    const uint32_t nrows = 5;
    const float voxel_size = 0.3f;

    // clang-format off
    const float32 data[nrows * 3] = {
        0.f,  0.f,   0.f,
        0.25f, 0.1f, 0.1f,
        0.5f, 0.2f, 0.2f,
        0.75f, 0.2f, 0.2f,
        1.f,  0.2f, 0.2f,
    };
    // clang-format on

    auto *indices_ptr = ss::voxel_grid_subsample_3d(data, nrows, voxel_size);
    auto &indices = *indices_ptr;
    std::sort(indices.begin(), indices.end());

    REQUIRE(indices.size() == 4);
    CHECK(indices[0] == 1);
    CHECK(indices[1] == 2);
    CHECK(indices[2] == 3);
    CHECK(indices[3] == 4);
}

TEST_CASE("Points with collapsed dimensions are subsampled within voxels",
          "[voxel]") {
    const uint32_t nrows = 5;
    const float voxel_size = 0.3f;

    // NOTE y and z are always 0
    // clang-format off
    const float32 data[nrows * 3] = {
        0.f,  0.f,   0.f,
        0.25f, 0.f, 0.f,
        0.5f, 0.f, 0.f,
        0.75f, 0.f, 0.f,
        1.f,  0.f, 0.f,
    };
    // clang-format on

    auto *indices_ptr = ss::voxel_grid_subsample_3d(data, nrows, voxel_size);
    auto &indices = *indices_ptr;
    std::sort(indices.begin(), indices.end());

    REQUIRE(indices.size() == 4);
    CHECK(indices[0] == 1);
    CHECK(indices[1] == 2);
    CHECK(indices[2] == 3);
    CHECK(indices[3] == 4);
}

TEST_CASE("Points are subsampled within the specified radius", "[radius]") {
    const uint32_t nrows = 5;
    const float32 origin[] = {-1.f, 0.5f, 0.25f};
    const float radius = 2.f;

    // clang-format off
    const float32 data[nrows * 3] = {
        0.f, -1.f, 0.f,
        1.f, 1.f, 2.f,
        -0.25f, -1.f, 0.5f,
        2.f, -2.f, 5.f,
        -0.1f, 0.1f, 0.2f,
    };
    // clang-format on

    auto *indices_ptr = ss::radius_select_3d(data, nrows, origin, radius);
    auto &indices = *indices_ptr;
    std::sort(indices.begin(), indices.end());

    REQUIRE(indices.size() == 3);
    CHECK(indices[0] == 0);
    CHECK(indices[1] == 2);
    CHECK(indices[2] == 4);
}

TEST_CASE("Points with collapsed dimensions are subsampled within the "
          "specified radius",
          "[radius]") {
    const uint32_t nrows = 5;
    const float32 origin[] = {0.f, 0.f, 0.f};
    const float radius = 2.f;

    // NOTE y and z are always 0
    // clang-format off
    const float32 data[nrows * 3] = {
        0.f, 0.f, 0.f,
        1.f, 0.f, 0.f,
        2.f, 0.f, 0.f,
        -1.f, 0.f, 0.f,
        -10.f, 0.f, 0.f,
    };
    // clang-format on

    auto *indices_ptr = ss::radius_select_3d(data, nrows, origin, radius);
    auto &indices = *indices_ptr;
    std::sort(indices.begin(), indices.end());

    REQUIRE(indices.size() == 4);
    CHECK(indices[0] == 0);
    CHECK(indices[1] == 1);
    CHECK(indices[2] == 2);
    CHECK(indices[3] == 3);
}

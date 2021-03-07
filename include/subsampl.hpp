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

#pragma once

#include <cstdint>
#include <vector>

#include "types.hpp"

/**
 * @brief Subsamples an array of 3D points using a voxel grid.
 *
 * @param data Pointer to a two-dimensional array containing 3D data points
 *             in a row-major order
 * @param nrows Number of data points in the array
 * @param voxel_size Size of a single side of a voxel
 * @return std::vector<uint32_t>* Pointer to a vector containing indices of
 *         subsampled points
 */
std::vector<uint32_t> *voxel_grid_subsample_3d(
    const float32 *data,
    const uint32_t nrows,
    const float32 voxel_size
);

/**
 * @brief Subsamples an array of 3D points by selecting points within
 *        a radius with respect to an origin.
 *
 * @param data Pointer to a two-dimensional array containing 3D data points
 *             in a row-major order
 * @param nrows Number of data points in the array
 * @param origin Pointer to a one-dimensional array containing a 3D data point
 *               representing the origin
 * @param radius Radius within the points are selected
 * @return std::vector<uint32_t>* Pointer to a vector containing indices of
 *         subsampled points
 */
std::vector<uint32_t> *radius_select_3d(
    const float32 *data,
    const uint32_t nrows,
    const float32 *origin,
    const float32 radius
);
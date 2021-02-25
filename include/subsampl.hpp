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
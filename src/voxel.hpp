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

#include <subsampl/types.hpp>

static void chunk_compute_voxel_index_3d(const float32 *data,
                                         std::vector<uint64_t> &point_to_voxel,
                                         uint32_t start, uint32_t end,
                                         float32 voxel_size, float32 x_min,
                                         float32 y_min, float32 z_min,
                                         uint64_t ny, uint64_t nz);

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

#pragma once

#include <subsampl/types.hpp>

static void chunk_compute_inside_radius_3d(const float32 *data,
                                           const float32 *origin,
                                           std::vector<uint32_t> &indices,
                                           uint32_t start, uint32_t end,
                                           float32 radius);

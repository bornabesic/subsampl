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

static_assert(sizeof(float) == 4, "The size of float should be 4 bytes");
static_assert(sizeof(double) == 8, "The size of double should be 4 bytes");

using float32 = float;
using float64 = double;

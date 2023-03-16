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

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <subsampl/subsampl.hpp>
#include <subsampl/types.hpp>

namespace py = pybind11;

template <typename T>
py::array_t<T> vector_pointer_to_numpy_array(std::vector<T> *vector) {
    py::capsule free_when_done(vector, [](void *ptr) {
        auto *vector = static_cast<std::vector<T> *>(ptr);
        delete vector;
    });

    return {
        {vector->size()}, // Shape
        {sizeof(T)},      // Strides
        &(*vector)[0],    // Data pointer
        free_when_done    // Base object (to avoid copying and to call delete)
    };
}

PYBIND11_MODULE(pysubsampl, m) {
    m.doc() = "Python bindings for subsampl";

    m.def(
        "voxel_grid_subsample_3d",
        [](const py::array_t<float32, py::array::c_style> &array,
           float32 voxel_size) {
            auto a = array.unchecked<2>();
            uint32_t nrows = a.shape(0);
            float32 *data = static_cast<float32 *>(array.request().ptr);

            auto *indices = voxel_grid_subsample_3d(data, nrows, voxel_size);

            return vector_pointer_to_numpy_array<uint32_t>(indices);
        },
        py::arg("array"), py::arg("voxel_size"));

    m.def(
        "radius_select_3d",
        [](const py::array_t<float32, py::array::c_style> &points,
           const py::array_t<float32, py::array::c_style> &origin,
           float32 radius) {
            auto p = points.unchecked<2>();
            origin.unchecked<1>();

            uint32_t nrows = p.shape(0);
            float32 *data_points = static_cast<float32 *>(points.request().ptr);
            float32 *data_origin = static_cast<float32 *>(origin.request().ptr);

            auto *indices =
                radius_select_3d(data_points, nrows, data_origin, radius);

            return vector_pointer_to_numpy_array<uint32_t>(indices);
        },
        py::arg("points"), py::arg("origin"), py::arg("radius"));
}
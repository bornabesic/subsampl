
add_library(subsampl voxel.cpp)
target_link_libraries(subsampl pthread)

if (BUILD_PYTHON_BINDINGS)
    pybind11_add_module(pysubsampl python.cpp)
    target_link_libraries(pysubsampl PRIVATE subsampl)
endif(BUILD_PYTHON_BINDINGS)

add_executable(test test.cpp)
target_link_libraries(test subsampl)
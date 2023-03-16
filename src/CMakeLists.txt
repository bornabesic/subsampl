
add_library(subsampl subsampl/voxel.cpp subsampl/radius.cpp)
target_link_libraries(subsampl pthread)

if (BUILD_PYTHON_BINDINGS)
    pybind11_add_module(pysubsampl subsampl/python.cpp)
    target_link_libraries(pysubsampl PRIVATE subsampl)
endif(BUILD_PYTHON_BINDINGS)

add_executable(test test.cpp)
target_link_libraries(test subsampl)

add_executable(test_hashmap test_hashmap.cpp)

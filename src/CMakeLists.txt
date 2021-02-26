
add_library(subsampl voxel.cpp)
target_link_libraries(subsampl pthread)

pybind11_add_module(pysubsampl python.cpp)
target_link_libraries(pysubsampl PRIVATE subsampl)

add_executable(test test.cpp)
target_link_libraries(test subsampl)
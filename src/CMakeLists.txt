
add_library(subsampl voxel.cpp)
target_link_libraries(subsampl pthread)

add_executable(test test.cpp)
target_link_libraries(test subsampl)
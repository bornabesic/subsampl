
add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE subsampl Catch2::Catch2WithMain)

message(${CMAKE_MODULE_PATH})
include(CTest)
include(Catch)
catch_discover_tests(tests)

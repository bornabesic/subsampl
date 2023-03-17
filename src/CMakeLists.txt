
add_library(subsampl STATIC subsampl/voxel.cpp subsampl/radius.cpp)
set_target_properties(subsampl PROPERTIES PUBLIC_HEADER "../include/subsampl/subsampl.hpp;../include/subsampl/types.hpp")

if (NOT WIN32)
    target_link_libraries(subsampl pthread)
endif ()

install(TARGETS subsampl PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/subsampl)

if (BUILD_PYTHON_BINDINGS)
    pybind11_add_module(pysubsampl subsampl/python.cpp)
    target_link_libraries(pysubsampl PRIVATE subsampl)
endif ()

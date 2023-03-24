
add_library(subsampl STATIC subsampl/voxel.cpp subsampl/radius.cpp)
set_property(TARGET subsampl PROPERTY POSITION_INDEPENDENT_CODE ON)
set_target_properties(subsampl PROPERTIES PUBLIC_HEADER "../include/subsampl/subsampl.hpp;../include/subsampl/types.hpp")

if (NOT WIN32)
    target_link_libraries(subsampl pthread)
endif ()

install(TARGETS subsampl PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/subsampl)

if (BUILD_PYTHON_BINDINGS)
    pybind11_add_module(subsampl-python subsampl/python.cpp)
    target_link_libraries(subsampl-python PRIVATE subsampl)
    set_property(TARGET subsampl-python PROPERTY OUTPUT_NAME subsampl)
endif ()

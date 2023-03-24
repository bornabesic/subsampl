
if (BUILD_PYTHON_BINDINGS)
    add_subdirectory(pybind11/)
endif ()

if (BUILD_TESTS)
    add_subdirectory(Catch2/)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
endif ()


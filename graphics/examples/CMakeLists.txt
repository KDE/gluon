
if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${GLUON_GRAPHICS_INCLUDES})

set(EXAMPLES_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)

add_subdirectory(basic)

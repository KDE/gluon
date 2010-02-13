cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES})

set(cameracontrollercomponent_SRCS
    cameracontrollercomponent.cpp
)

qt4_automoc(${cameracontrollercomponent_SRCS})
add_library(gluon_component_cameracontroller SHARED ${cameracontrollercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_cameracontroller GluonEngine GluonGraphics gluon_asset_texture)
endif()

target_link_libraries(gluon_component_cameracontroller GluonEngine ${GLUON_GRAPHICS_LIBS} gluon_asset_texture)

install(
    TARGETS
    gluon_component_cameracontroller
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
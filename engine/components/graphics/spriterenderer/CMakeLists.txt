cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES})

set(spriterenderercomponent_SRCS
    spriterenderercomponent.cpp
)

qt4_automoc(${spriterenderercomponent_SRCS})
add_library(gluon_component_spriterenderer SHARED ${spriterenderercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_spriterenderer GluonEngine GluonGraphics gluon_asset_texture)
endif()

set_target_properties(gluon_component_spriterenderer PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})
target_link_libraries(gluon_component_spriterenderer GluonEngine ${GLUON_GRAPHICS_LIBS} gluon_asset_texture)

install(
    TARGETS
    gluon_component_spriterenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
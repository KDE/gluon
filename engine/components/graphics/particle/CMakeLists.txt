cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDE_DIRS})

set(particlecomponent_SRCS
    particlerenderer.cpp
)

qt4_automoc(${particlecomponent_SRCS})
add_library(gluon_component_particle SHARED ${particlecomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_particle GluonEngine GluonGraphics)
endif()

set_target_properties(gluon_component_particle PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})
target_link_libraries(gluon_component_particle GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_particle
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

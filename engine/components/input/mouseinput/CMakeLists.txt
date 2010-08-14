cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonInput REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_INPUT_INCLUDES})

set(mouseinputcomponent_SRCS
    mouseinputcomponent.cpp
)

qt4_automoc(${mouseinputcomponent_SRCS})
add_library(gluon_component_mouseinput SHARED ${mouseinputcomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_mouseinput GluonEngine GluonInput)
endif()

set_target_properties(gluon_component_mouseinput PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})
target_link_libraries(gluon_component_mouseinput GluonEngine ${GLUON_INPUT_LIBS})

install(
    TARGETS
    gluon_component_mouseinput
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

message("do not install this but add it to the player and creator")

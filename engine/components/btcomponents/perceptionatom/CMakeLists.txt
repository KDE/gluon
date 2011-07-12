cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_CORE_INCLUDES})

set(perceptionatomcomponent_SRCS
    perceptionatom.cpp
    perceptionatomprivate.cpp
)

qt4_automoc(${perceptionatomcomponent_SRCS})
add_library(gluon_component_btperceptionatom SHARED ${perceptionatomcomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_btperceptionatom GluonEngine)
endif()

set_target_properties(gluon_component_btperceptionatom PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_BTPERCEPTIONATOM_LIB)
target_link_libraries(gluon_component_btperceptionatom GluonEngine)

install(
    TARGETS
    gluon_component_btperceptionatom
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
 

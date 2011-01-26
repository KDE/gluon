cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_CORE_INCLUDES})

set(spherecollisioncomponent_SRCS
    spherecollisioncomponent.cpp
)

qt4_automoc(${spherecollisioncomponent_SRCS})
add_library(gluon_component_spherecollision SHARED ${spherecollisioncomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_spherecollision GluonEngine)
endif()

set_target_properties(gluon_component_spherecollision PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_SPHERECOLLISION_LIB)
target_link_libraries(gluon_component_spherecollision GluonEngine)

install(
    TARGETS
    gluon_component_spherecollision
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
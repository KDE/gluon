 cmake_minimum_required(VERSION 2.8)

find_package(Bullet)
include_directories(${BULLET_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_CORE_INCLUDE_DIRS})

set(spherecollisioncomponent_SRCS
    spherecollisioncomponent.cpp
    physicsworld.cpp
   )

qt4_automoc(${spherecollisioncomponent_SRCS})
add_library(gluon_component_physics SHARED ${spherecollisioncomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_physics GluonEngine)
endif()

set_target_properties(gluon_component_physics PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_PHYSICS_LIB)
target_link_libraries(gluon_component_physics GluonEngine ${BULLET_LIBRARIES})

install(
    TARGETS
    gluon_component_physics
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
) 

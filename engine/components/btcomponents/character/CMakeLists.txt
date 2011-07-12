cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_CORE_INCLUDES})

set(charactercomponent_SRCS
    character.cpp
    characterprivate.cpp
)

qt4_automoc(${charactercomponent_SRCS})
add_library(gluon_component_btcharacter SHARED ${charactercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_btcharacter GluonEngine)
endif()

set_target_properties(gluon_component_btcharacter PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_BTCHARACTER_LIB)
target_link_libraries(gluon_component_btcharacter GluonEngine)

install(
    TARGETS
    gluon_component_btcharacter
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
 

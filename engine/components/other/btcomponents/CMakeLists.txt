cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonSmarts REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_SMARTS_INCLUDE_DIRS})

set(behaviortreecomponent_SRCS
    btAssetprivate.cpp
    btAsset.cpp
    treeprivate.cpp
    tree.cpp
    characterprivate.cpp
    character.cpp
    btcharacterscriptable.cpp
    btnodescriptable.cpp
    viewcone.cpp
    viewconeprivate.cpp
    perceptionatom.cpp
    perceptionatomprivate.cpp
    perceptioninfo.cpp
    perceptioninfoprivate.cpp
    btperceptioninfoscriptable.cpp
)

qt4_automoc(${behaviortreecomponent_SRCS})
add_library(gluon_component_behaviortree SHARED ${behaviortreecomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_behaviortree GluonEngine GluonSmarts)
endif()

set_target_properties(gluon_component_behaviortree PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_BEHAVIORTREE_LIB)
target_link_libraries(gluon_component_behaviortree GluonEngine ${GLUON_SMARTS_LIBS})

install(
    TARGETS
    gluon_component_behaviortree
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

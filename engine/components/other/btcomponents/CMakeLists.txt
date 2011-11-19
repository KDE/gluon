cmake_minimum_required(VERSION 2.6)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${GLUON_ENGINE_INCLUDES} ${GLUON_CORE_INCLUDES} ${QT_QTSCRIPT_INCLUDES})

set(behaviorTreeComponent_SRCS
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

qt4_automoc(${behaviorTreeComponent_SRCS})
add_library(gluon_plugin_asset_behaviortree SHARED ${behaviorTreeComponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_plugin_asset_behaviortree GluonEngine)
endif()

set_target_properties(gluon_plugin_asset_behaviortree PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_BTCOMPONENT_LIB)
target_link_libraries(gluon_plugin_asset_behaviortree GluonEngine)

install(
    TARGETS
    gluon_plugin_asset_behaviortree
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

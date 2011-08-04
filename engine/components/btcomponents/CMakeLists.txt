project(btcomponents)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_INSTALL_PREFIX}/share/kde4/apps/cmake/modules/)

find_package(Qt4 REQUIRED)
find_package(GluonCore REQUIRED)
find_package(GluonEngine REQUIRED)

set(_Init_LIB_SUFFIX "")
if ("${QT_QTCORE_LIBRARY}" MATCHES lib64)
   set(_Init_LIB_SUFFIX 64)
endif ("${QT_QTCORE_LIBRARY}" MATCHES lib64)
if ("${QT_QTCORE_LIBRARY}" MATCHES lib32)
   set(_Init_LIB_SUFFIX 32)
endif ("${QT_QTCORE_LIBRARY}" MATCHES lib32)

set(LIB_SUFFIX		    ${_Init_LIB_SUFFIX} CACHE STRING "The suffix of the system-wide library path")
set(LIB_INSTALL_DIR         ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}    CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed.")

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${GLUON_ENGINE_INCLUDES} ${GLUON_CORE_INCLUDES} ${QT_QTSCRIPT_INCLUDES})

set(behaviorTreeComponent_SRCs
    assetprivate.cpp
    asset.cpp
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

    #src/bindings/com_trolltech_qt_gui_init.cpp
    #src/bindings/qtscript_QVector2D.cpp
    #src/bindings/qtscript_QVector3D.cpp
    #src/bindings/qtscript_QVector4D.cpp
    #src/bindings/qtscript_QColor.cpp
    #src/bindings/qtscript_QQuaternion.cpp
   )

qt4_automoc(
	${behaviorTreeComponent_SRCs} 
	)

find_library(LIBBT
    NAMES
        libbtlib.so
    PATHS
        #c:/repo/gluon-bt/src/gluon-bt-lib/qtcreator-build/
        /usr/lib/
        #/usr/lib64
)
message("-- Found libbtlib:" ${LIBBT})

find_path(LIBBTPATH
    NAMES
        libbtlib.so
    PATHS
        #c:/repo/gluon-bt/src/gluon-bt-lib/qtcreator-build/
        /usr/lib/
        #/usr/lib64
)
message("-- Found libbt's path:" ${LIBBTPATH})

add_library(btlib SHARED IMPORTED)
set_property(TARGET btlib PROPERTY IMPORTED_LOCATION ${LIBBT})
set_property(TARGET btlib PROPERTY IMPORTED_IMPLIB ${LIBBT})

add_definitions(-DMAKE_BTCOMPONENT_LIB)
add_definitions(-DMAKE_GLUON_LIB)

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)

add_library(gluon_plugin_asset_behaviortree SHARED ${behaviorTreeComponent_SRCs} )

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_plugin_asset_behaviortree GluonEngine btlib)
endif()


set_target_properties(gluon_plugin_asset_behaviortree PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_BTCOMPONENT_LIB)
target_link_libraries(gluon_plugin_asset_behaviortree ${QT_QTCORE_LIBRARY} ${GLUON_CORE_LIBS} ${GLUON_ENGINE_LIBS} ${QT_QTSCRIPT_LIBRARY} btlib)

install(
    TARGETS
    gluon_plugin_asset_behaviortree
    DESTINATION ${LIB_INSTALL_DIR}/gluon
)

#add_subdirectory(testapp)
cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonEngine)
    find_package(GluonCore REQUIRED)
endif()

option(BUILD_AUDIO_COMPONENTS "Build Components dependant on Gluon Audio" ON)
option(BUILD_AUDIO_ASSETS "Build Assets dependant on Gluon Audio" ON)
option(BUILD_GRAPHICS_COMPONENTS "Build Components dependant on Gluon Graphics" ON)
option(BUILD_GRAPHICS_ASSETS "Build Assets dependant on Gluon Graphics" ON)
option(BUILD_INPUT_COMPONENTS "Build Components dependant on Gluon Input" ON)
option(BUILD_INPUT_ASSETS "Build Assets dependant on Gluon Input" ON)
option(BUILD_PHYSICS_COMPONENTS "Build Components related to physics" OFF)
option(BUILD_PHYSICS_ASSETS "Build Assets related to physics" OFF)
option(BUILD_OTHER_COMPONENTS "Build other Components" ON)
option(BUILD_OTHER_ASSETS "Build other Assets" ON)

if(NOT BUILD_GLUON_AUDIO)
    set(BUILD_AUDIO_COMPONENTS OFF)
    set(BUILD_AUDIO_ASSETS OFF)
endif()
if(NOT BUILD_GLUON_GRAPHICS)
    set(BUILD_GRAPHICS_ASSETS OFF)
    set(BUILD_GRAPHICS_COMPONENTS OFF)
endif()
if(NOT BUILD_GLUON_INPUT)
    set(BUILD_INPUT_ASSETS OFF)
    set(BUILD_INPUT_COMPONENTS OFF)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_CORE_INCLUDES}
)

add_subdirectory(assets)
add_subdirectory(components)

set(GluonEngine_SRCS
    asset.cpp
    component.cpp
    componentprivate.cpp
    gameobject.cpp
    gameobjectprivate.cpp
    gameproject.cpp
    gameprojectprivate.cpp
    prefab.cpp
    prefabprivate.cpp
    savable.cpp
    scene.cpp
    sceneprivate.cpp
    filelocation.cpp
    filelocationprivate.cpp

    game.cpp
    gameprivate.cpp
)

qt4_automoc(${GluonEngine_SRCS})
add_library(GluonEngine SHARED ${GluonEngine_SRCS})

set_target_properties(GluonEngine PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_ENGINE_LIB)

if(GLUON_BUILD_ALL)
    add_dependencies(GluonEngine GluonCore)
endif()

target_link_libraries(GluonEngine ${GLUON_CORE_LIBS})

set(GLUON_ENGINE_LIBS
    GluonEngine
    ${GLUON_CORE_LIBS}
    CACHE PATHS "Libraries required for Gluon Engine"
)

install(TARGETS GluonEngine DESTINATION ${LIB_INSTALL_DIR})

install(
    FILES
    asset.h
    component.h
    gameobject.h
    gameproject.h
    prefab.h
    savable.h
    scene.h
    filelocation.h

    gluon_engine_export.h
    gluon_engine_metatypes.h
    game.h

    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/engine
    COMPONENT Devel
)

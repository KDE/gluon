cmake_minimum_required(VERSION 2.8)

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

set(GLUON_ENGINE_INCLUDES
    ${GLUON_CORE_INCLUDES}
    ${GLUON_GRAPHICS_INCLUDES}
    CACHE INTERNAL "Include files required for Gluon Engine"
)

add_subdirectory(assets)
add_subdirectory(components)

set(GluonEngine_SRCS
    abstractstatistic.cpp
    achievement.cpp
    achievementsmanager.cpp
    asset.cpp
    component.cpp
    componentprivate.cpp
    databasemanager.cpp
    filelocation.cpp
    filelocationprivate.cpp
    gameobject.cpp
    gameobjectprivate.cpp
    gameproject.cpp
    gameprojectprivate.cpp
    prefab.cpp
    prefabprivate.cpp
    prefabinstance.cpp
    prefabinstancechild.cpp
    projectmetadata.cpp
    savable.cpp
    scene.cpp
    sceneprivate.cpp
    statistic.cpp

    game.cpp
    gameprivate.cpp
)

set(GluonEngine_HEADERS
    abstractstatistic.h
    achievement.h
    achievementsmanager.h
    asset.h
    component.h
    databasemanager.h
    filelocation.h
    gameobject.h
    gameproject.h
    prefab.h
    prefabinstance.h
    prefabinstancechild.h
    projectmetadata.h
    savable.h
    scene.h
    statistic.h

    game.h
    gluon_engine_export.h
    gluon_engine_metatypes.h
)

qt4_automoc(${GluonEngine_SRCS})
if(APPLE)
    add_library(GluonEngine SHARED ${GluonEngine_SRCS} ${GluonEngine_HEADERS})
else()
    add_library(GluonEngine SHARED ${GluonEngine_SRCS})
endif()

set_target_properties(GluonEngine PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_ENGINE_LIB)

if(APPLE)
    #hack for being able to set headers as public in a osx framework
    list(APPEND GluonEngine_HEADERS
    ${GluonEngine_HEADERS}
    )

    set_target_properties(GluonEngine PROPERTIES FRAMEWORK TRUE)
    set_target_properties(GluonEngine PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
    set_target_properties(GluonEngine PROPERTIES PUBLIC_HEADER "${GluonEngine_HEADERS}")

    set(MACOSX_FRAMEWORK_IDENTIFIER engine)
    set(MACOSX_FRAMEWORK_IDENTIFIER GluonEngine)
    set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endif()

if(GLUON_BUILD_ALL)
    add_dependencies(GluonEngine GluonCore)
endif()

target_link_libraries(GluonEngine ${GLUON_CORE_LIBS} ${GLUON_GRAPHICS_LIBS} ${QT_QTSQL_LIBRARY})

set(GLUON_ENGINE_LIBS
    GluonEngine
    ${GLUON_CORE_LIBS}
    ${GLUON_GRAPHICS_LIBS}
    CACHE INTERNAL "Libraries required for Gluon Engine"
)

install(
    TARGETS     GluonEngine
    RUNTIME     DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluonengine
    LIBRARY     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonengine
    ARCHIVE     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonengine
    FRAMEWORK   DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonengine
)

install(
    FILES
    ${GluonEngine_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/engine
    COMPONENT gluonengine
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()


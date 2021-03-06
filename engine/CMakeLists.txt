option( BUILD_AUDIO_PLUGIN "Build Assets and Components dependant on Gluon Audio" ON )
option( BUILD_INPUT_PLUGIN "Build Assets and Components dependant on Gluon Input" ON )
option( BUILD_OTHER_PLUGIN "Build other Assets and Components" ON )
option( BUILD_GRAPHICS_PLUGIN "Build Assets and Components dependant on Gluon Graphics" ON )

option( BUILD_PHYSICS_COMPONENTS "Build Components related to physics" OFF )
option( BUILD_PHYSICS_ASSETS "Build Assets related to physics" OFF )

if( NOT BUILD_GLUONAUDIO )
    set( BUILD_AUDIO_PLUGIN OFF )
endif()
if( NOT BUILD_GLUONGRAPHICS )
    set( BUILD_GRAPHICS_PLUGIN OFF )
endif()
if( NOT BUILD_GLUONINPUT )
    set( BUILD_INPUT_PLUGIN OFF )
endif()

find_package( Qt5Sql REQUIRED )

set( GluonEngine_SRCS
    abstractprefabinstance.cpp
    abstractstatistic.cpp
    achievement.cpp
    achievementsmanager.cpp
    asset.cpp
    booleanstatistic.cpp
    component.cpp
    componentprivate.cpp
    databasemanager.cpp
    filelocation.cpp
    filelocationprivate.cpp
    gameobject.cpp
    gameobjectprivate.cpp
    gameproject.cpp
    gameprojectprivate.cpp
    multiscorestatistic.cpp
    prefab.cpp
    prefabprivate.cpp
    prefabinstance.cpp
    prefabinstancechild.cpp
    projectmetadata.cpp
    savable.cpp
    scene.cpp
    sceneprivate.cpp
    statistic.cpp
    tasksstatistic.cpp
    assetaction.cpp

    game.cpp
    gameprivate.cpp
)

set( GluonEngine_HEADERS
    abstractprefabinstance.h
    abstractstatistic.h
    achievement.h
    achievementsmanager.h
    asset.h
    booleanstatistic.h
    component.h
    databasemanager.h
    filelocation.h
    gameobject.h
    gameproject.h
    multiscorestatistic.h
    prefab.h
    prefabinstance.h
    prefabinstancechild.h
    projectmetadata.h
    savable.h
    scene.h
    statistic.h
    tasksstatistic.h
    assetaction.h

    game.h
    gluon_engine_export.h
    gluon_engine_metatypes.h
)

gluon_add_library( Gluon::Engine SHARED
    SOURCES ${GluonEngine_SRCS}
    HEADERS ${GluonEngine_HEADERS}
    LIBRARIES Gluon::Core Qt5::Sql
)

gluon_add_plugin( gluonengine_types
    MODULE Gluon::Engine
    SOURCES factoryplugin.cpp
)

if( BUILD_AUDIO_PLUGIN )
    add_subdirectory( plugins/audio )
endif()

if( BUILD_INPUT_PLUGIN )
    add_subdirectory( plugins/input )
endif()

if( BUILD_OTHER_PLUGIN )
    add_subdirectory( plugins/other )
endif()

if( BUILD_GRAPHICS_PLUGIN )
    add_subdirectory( plugins/graphics )
endif()

add_subdirectory( plugins/scripting )

gluon_add_subdirectories( examples tests )

save_status( Gluon::Engine
    "Build Assets and Components dependant on Gluon Audio (BUILD_AUDIO_PLUGIN): ${BUILD_AUDIO_PLUGIN}"
    "Build Assets and Components dependant on Gluon Graphics (BUILD_GRAPHICS_PLUGIN): ${BUILD_GRAPHICS_PLUGIN}"
    "Build Components dependant on Gluon Input (BUILD_INPUT_COMPONENTS): ${BUILD_INPUT_COMPONENTS}"
    "Build Assets dependant on Gluon Input (BUILD_INPUT_ASSETS): ${BUILD_INPUT_ASSETS}"
    "Build Components related to physics (BUILD_PHYSICS_COMPONENTS): ${BUILD_PHYSICS_COMPONENTS}"
    "Build Assets related to physics (BUILD_PHYSICS_ASSETS): ${BUILD_PHYSICS_ASSETS}"
    "Build other Assets and Components (BUILD_OTHER_PLUGIN): ${BUILD_OTHER_PLUGIN}"
)


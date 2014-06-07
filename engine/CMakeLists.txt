option( BUILD_AUDIO_COMPONENTS "Build Components dependant on Gluon Audio" ON )
option( BUILD_AUDIO_ASSETS "Build Assets dependant on Gluon Audio" ON )
option( BUILD_GRAPHICS_COMPONENTS "Build Components dependant on Gluon Graphics" OFF )
option( BUILD_GRAPHICS_ASSETS "Build Assets dependant on Gluon Graphics" OFF )
option( BUILD_INPUT_COMPONENTS "Build Components dependant on Gluon Input" OFF )
option( BUILD_INPUT_ASSETS "Build Assets dependant on Gluon Input" OFF )
option( BUILD_PHYSICS_COMPONENTS "Build Components related to physics" OFF )
option( BUILD_PHYSICS_ASSETS "Build Assets related to physics" OFF )
option( BUILD_OTHER_COMPONENTS "Build other Components" ON )
option( BUILD_OTHER_ASSETS "Build other Assets" ON )

if( NOT BUILD_GLUONAUDIO )
    set( BUILD_AUDIO_COMPONENTS OFF )
    set( BUILD_AUDIO_ASSETS OFF )
endif()
if( NOT BUILD_GLUONGRAPHICS )
    set( BUILD_GRAPHICS_ASSETS OFF )
    set( BUILD_GRAPHICS_COMPONENTS OFF )
endif()
if( NOT BUILD_GLUONINPUT )
    set( BUILD_INPUT_ASSETS OFF )
    set( BUILD_INPUT_COMPONENTS OFF )
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
    INCLUDES ${Qt5Sql_INCLUDE_DIRS}
    LIBRARIES Gluon::Core Qt5::Sql
)

add_subdirectory( assets )
add_subdirectory( components )

gluon_add_subdirectories( tests )

save_status( Gluon::Engine
    "Build Components dependant on Gluon Audio (BUILD_AUDIO_COMPONENTS): ${BUILD_AUDIO_COMPONENTS}"
    "Build Assets dependant on Gluon Audio (BUILD_AUDIO_ASSETS): ${BUILD_AUDIO_ASSETS}"
    "Build Components dependant on Gluon Graphics (BUILD_GRAPHICS_COMPONENTS): ${BUILD_GRAPHICS_COMPONENTS}"
    "Build Assets dependant on Gluon Graphics (BUILD_GRAPHICS_ASSETS): ${BUILD_GRAPHICS_ASSETS}"
    "Build Components dependant on Gluon Input (BUILD_INPUT_COMPONENTS): ${BUILD_INPUT_COMPONENTS}"
    "Build Assets dependant on Gluon Input (BUILD_INPUT_ASSETS): ${BUILD_INPUT_ASSETS}"
    "Build Components related to physics (BUILD_PHYSICS_COMPONENTS): ${BUILD_PHYSICS_COMPONENTS}"
    "Build Assets related to physics (BUILD_PHYSICS_ASSETS): ${BUILD_PHYSICS_ASSETS}"
    "Build other Components (BUILD_OTHER_COMPONENTS): ${BUILD_OTHER_COMPONENTS}"
    "Build other Assets (BUILD_OTHER_ASSETS): ${BUILD_OTHER_ASSETS}"
)


option( BUILD_CREATOR_APP "Build the Creator application" ON )
option( BUILD_DESKTOP_PLAYER "Build the Desktop Player" ON )
option( BUILD_ACTIVE_PLAYER "Build the Plasma Active Player" OFF )
option( BUILD_PLASMOID "Build the Plasma Widget Player" OFF )
option( BUILD_HARMATTAN_PLAYER "Build the Harmattan Player" OFF )
option( BUILD_FREMANTLE_PLAYER "Build the Fremantle Player" OFF )

if( BUILD_CREATOR_APP )
    add_subdirectory( creator )
endif()

if( BUILD_DESKTOP_PLAYER )
    add_subdirectory( desktop )
endif()

if( BUILD_ACTIVE_PLAYER )
    add_subdirectory( active )
endif()

if( BUILD_FREMANTLE_PLAYER )
    add_subdirectory(fremantle)
endif()

if( BUILD_HARMATTAN_PLAYER )
    add_subdirectory(harmattan)
endif()

save_status( GluonApps
    "Build the Creator application (BUILD_CREATOR_APP): ${BUILD_CREATOR_APP}"
    "Build the Desktop player (BUILD_DESKTOP_PLAYER): ${BUILD_DESKTOP_PLAYER}"
    "Build the Plasma Active player (BUILD_ACTIVE_PLAYER): ${BUILD_ACTIVE_PLAYER}"
    "Build the Plasma Widget player (BUILD_PLASMOID): ${BUILD_PLASMOID}"
    "Build the Harmattan player (BUILD_HARMATTAN_PLAYER): ${BUILD_HARMATTAN_PLAYER}"
    "Build the Fremantle player (BUILD_FREMANTLE_PLAYER): ${BUILD_FREMANTLE_PLAYER}"
)

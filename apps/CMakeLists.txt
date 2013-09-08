if( WITH_KDE )
    option( BUILD_DESKTOP_PLAYER "Build the Desktop Player" ON )
    option( BUILD_ACTIVE_PLAYER "Build the Plasma Active Player" OFF )
    option( BUILD_PLASMOID "Build the Plasma Widget Player" OFF )
endif( WITH_KDE )
option( BUILD_HARMATTAN_PLAYER "Build the Harmattan Player" OFF )
option( BUILD_FREMANTLE_PLAYER "Build the Fremantle Player" OFF )

if( NOT KDE4_FOUND )
    set( BUILD_DESKTOP_PLAYER OFF )
    set( BUILD_ACTIVE_PLAYER OFF )
    message( WARNING "KDE Libraries were not found - disabling the Desktop and Active players" )
endif( NOT KDE4_FOUND )

if( BUILD_DESKTOP_PLAYER )
    add_subdirectory( desktop )
endif( BUILD_DESKTOP_PLAYER )

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
    "Build the Desktop player (BUILD_DESKTOP_PLAYER): ${BUILD_DESKTOP_PLAYER}"
    "Build the Plasma Active player (BUILD_ACTIVE_PLAYER): ${BUILD_ACTIVE_PLAYER}"
    "Build the Plasma Widget player (BUILD_PLASMOID): ${BUILD_PLASMOID)"
    "Build the Harmattan player (BUILD_HARMATTAN_PLAYER): ${BUILD_HARMATTAN_PLAYER}"
    "Build the Fremantle player (BUILD_FREMANTLE_PLAYER): ${BUILD_FREMANTLE_PLAYER}"
)

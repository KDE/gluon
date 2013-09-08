if( WITH_KDE )
    option( BUILD_DESKTOP_PLAYER "Build the Desktop Player" ON )
    option( BUILD_ACTIVE_PLAYER "Build the Plasma Active Player" OFF )
endif( WITH_KDE )
option( BUILD_HARMATTAN_PLAYER "Build the Harmattan Player" OFF )
option( BUILD_FREMANTLE_PLAYER "Build the Fremantle Player" OFF )
option( INSTALL_EXAMPLE_PROJECTS "Install the example projects" ON )

add_subdirectory(lib)

if( NOT KDE4_FOUND )
    set( BUILD_DESKTOP_PLAYER OFF )
    set( BUILD_ACTIVE_PLAYER OFF )
    message( STATUS "KDE Libraries were not found - disabling the Desktop and Active players" )
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

if( INSTALL_EXAMPLE_PROJECTS )
    add_subdirectory(examples)
endif( INSTALL_EXAMPLE_PROJECTS )

save_status( GluonPlayer
    "Build the Desktop player (BUILD_DESKTOP_PLAYER): ${BUILD_DESKTOP_PLAYER}"
    "Build the Plasma Active player (BUILD_ACTIVE_PLAYER): ${BUILD_ACTIVE_PLAYER}"
    "Build the Harmattan player (BUILD_HARMATTAN_PLAYER): ${BUILD_HARMATTAN_PLAYER}"
    "Build the Fremantle player (BUILD_FREMANTLE_PLAYER): ${BUILD_FREMANTLE_PLAYER}"
    "Install the example projects (INSTALL_EXAMPLE_PROJECTS): ${INSTALL_EXAMPLE_PROJECTS}"
)

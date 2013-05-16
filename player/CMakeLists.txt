cmake_minimum_required(VERSION 2.8)

option( BUILD_DESKTOP_PLAYER "Build the Desktop Player" ON )
option( BUILD_ACTIVE_PLAYER "Build the Plasma Active Player" OFF )
option( BUILD_HARMATTAN_PLAYER "Build the Harmattan Player" OFF )
option( BUILD_FREMANTLE_PLAYER "Build the Fremantle Player" OFF )
option( INSTALL_EXAMPLES "Install the example projects" ON )

set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

set( LIBATTICA_MIN_VERSION 0.1.90 )
find_package( LibAttica REQUIRED )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${LIBATTICA_INCLUDE_DIR}
)

add_subdirectory(lib)

if( BUILD_DESKTOP_PLAYER )
    if( KDE4_FOUND )
        include_directories( ${KDE4_INCLUDES} )
        add_subdirectory( desktop )
    else( KDE4_FOUND )
        set( BUILD_DESKTOP_PLAYER OFF )
        message( STATUS "KDE libraries are not found - not building the Desktop Player" )
    endif( KDE4_FOUND )
endif( BUILD_DESKTOP_PLAYER )

if( BUILD_ACTIVE_PLAYER )
    if( KDE4_FOUND )
        find_package( ActiveApp )
        if ( ACTIVEAPP_FOUND )
            include_directories( ${KDE4_INCLUDES} )
            include_directories( ${ACTIVEAPP_INCLUDE_DIR} )
            add_subdirectory( active )
        else( ACTIVEAPP_FOUND )
            set( BUILD_ACTIVE_PLAYER OFF )
            message(STATUS "Plasma Active common Appliation libraries are not found - not building the Plasma Active Player" )
        endif(ACTIVEAPP_FOUND )
    else( KDE4_FOUND )
        set( BUILD_ACTIVE_PLAYER OFF )
        message( STATUS "KDE libraries are not found - not building the Plasma Active Player" )
    endif( KDE4_FOUND )
endif()

if( BUILD_FREMANTLE_PLAYER )
    add_subdirectory(fremantle)
endif()

if( BUILD_HARMATTAN_PLAYER )
    add_subdirectory(harmattan)
endif()

if( INSTALL_EXAMPLES )
    add_subdirectory(examples)
endif( INSTALL_EXAMPLES )

save_status( GluonPlayer
    "Build the Desktop player (BUILD_DESKTOP_PLAYER): ${BUILD_DESKTOP_PLAYER}"
    "Build the Plasma Active player (BUILD_ACTIVE_PLAYER): ${BUILD_ACTIVE_PLAYER}"
    "Build the Harmattan player (BUILD_HARMATTAN_PLAYER): ${BUILD_HARMATTAN_PLAYER}"
    "Build the Fremantle player (BUILD_FREMANTLE_PLAYER): ${BUILD_FREMANTLE_PLAYER}"
    "Install the example projects (INSTALL_EXAMPLES): ${INSTALL_EXAMPLES}"
)

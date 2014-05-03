cmake_minimum_required( VERSION 2.8 )
project( Gluon )

#### Project Options ####
option( WITH_KDE "Build with KDE Development Platform Support" ON )
option( BUILD_GLUONAUDIO "Build Gluon Audio Library" ON )
option( BUILD_GLUONINPUT "Build Gluon Input Library" ON )
option( BUILD_GLUONSMARTS "Build SMARTS Game AI Library" ON )
option( BUILD_GLUONGRAPHICS "Build Gluon Graphics Library" ON )
option( BUILD_GLUONENGINE "Build Gluon Engine Library" ON )
option( BUILD_GLUONPLAYER "Build Gluon Player Library" ON )
option( BUILD_GLUONCREATOR "Build Gluon Creator Library" ON )
option( BUILD_GLUONAPPS "Build the Gluon applications" ON )
option( BUILD_TOOLS "Build Gluon Tools" ON )
option( BUILD_TESTS "Build Unit Tests for the Gluon libraries and applications" OFF )
option( BUILD_EXAMPLES "Build and install example applications" OFF )
option( INSTALL_GAMES "Install the example games" ON )

#### Global Dependencies ####
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
find_package( Qt4 4.7.1 REQUIRED )
find_package( Eigen3 REQUIRED )

# KDE is a global optional dependency
if( WITH_KDE )
    find_package( KDE4 )
    
    if( NOT ${KDE4_FOUND} )
        set( BUILD_GLUONCREATOR OFF )
    endif( NOT ${KDE4_FOUND} )
endif()

# Enable automoc (Internal CMake version if available, external binary if not)
if( CMAKE_VERSION VERSION_LESS "2.8.6" )
    find_package( Automoc4 REQUIRED )
else()
    set( CMAKE_AUTOMOC TRUE )
endif()

include( cmake/GluonVariables.cmake )
include( cmake/GluonMacros.cmake )

# Set some variables
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${EIGEN3_INCLUDE_DIR} )

if( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
    if( CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0" )
        set( CMAKE_CXX_FLAGS "-Wall -Wno-switch" )
    else( CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0" )
        set( CMAKE_CXX_FLAGS "-Wall -Wno-switch -Wno-unused-local-typedefs" )
    endif( CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0" )
elseif( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
    set( CMAKE_CXX_FLAGS "-Wall -Wno-switch" )
endif( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )

# To make sure we can run when not installed into $LD_LIBRARY_PATH
set( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" )
set( CMAKE_BUILD_WITH_INSTALL_RPATH TRUE )

# Always include CMAKE_CURRENT_SOURCE_DIR and CMAKE_CURRENT_BINARY_DIR by default
set( CMAKE_INCLUDE_CURRENT_DIR TRUE )

##### Gluon Libraries and Applications #####
add_subdirectory( core )

if( BUILD_GLUONAUDIO )
    add_subdirectory( audio )
endif()

if( BUILD_GLUONINPUT )
    add_subdirectory( input )
endif()

if( BUILD_GLUONGRAPHICS )
    add_subdirectory( graphics )
endif()

if( BUILD_GLUONSMARTS )
     add_subdirectory( smarts )
endif()

if( BUILD_GLUONENGINE )
    add_subdirectory( engine )
endif()

if( BUILD_GLUONPLAYER )
    add_subdirectory( player )
endif()

if( BUILD_GLUONCREATOR )
    add_subdirectory( creator )
endif()

if( BUILD_GLUONAPPS )
    add_subdirectory( apps )
endif()

if( BUILD_TOOLS )
    add_subdirectory( tools )
endif()

#### Feature Summary ####
message( STATUS )
message( STATUS "================================================================================" )
message( STATUS "                             Gluon Build Information                            " )
message( STATUS "================================================================================" )
message( STATUS )
message( STATUS "Build Version: ${GLUON_VERSION_STRING} (${GLUON_VERSION_NAME})" )
message( STATUS "Building with: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}" )
message( STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}" )
message( STATUS "Enable KDE Development Platform support (WITH_KDE): ${WITH_KDE}" )
log_status( GluonAudio )
log_status( GluonGraphics )
log_status( GluonInput )
log_status( GluonSmarts )
log_status( GluonEngine )
log_status( GluonPlayer )
log_status( GluonCreator )
log_status( GluonApps )
log_status( Tools )
log_status( Tests )
log_status( Examples )
message( STATUS "Install the example games (INSTALL_GAMES): ${INSTALL_GAMES}" )
message( STATUS )
message( STATUS "To change any of these options, override them using -D{OPTION_NAME}=ON/OFF on   " )
message( STATUS "the command line. To build and install Gluon, run \"make\" and \"make install\" " )
message( STATUS )
message( STATUS "================================================================================" )
message( STATUS )

include( CPack )

if( BUILD_TESTS )
    enable_testing()
    include( CTest )
endif()

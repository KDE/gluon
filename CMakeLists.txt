cmake_minimum_required( VERSION 2.8.12 )
project( Gluon )

if( NOT( CMAKE_MAJOR_VERSION LESS 3) )
    # Because CMake acts weird otherwise
    cmake_policy(SET CMP0028 OLD)
endif()

if( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7.0" )
    message(FATAL_ERROR "Gluon requires GCC version 4.7 or higher" )
endif()

#### Project Options ####
option( WITH_KDE "Build with KDE Development Platform Support" ON )
option( BUILD_GLUONAUDIO "Build Gluon Audio Library" ON )
option( BUILD_GLUONINPUT "Build Gluon Input Library" ON )
option( BUILD_GLUONSMARTS "Build SMARTS Game AI Library" ON )
option( BUILD_GLUONGRAPHICS "Build Gluon Graphics Library" ON )
option( BUILD_GLUONENGINE "Build Gluon Engine Library" ON )
option( BUILD_GLUONPLAYER "Build Gluon Player Library" ON )
option( BUILD_GLUONCREATOR "Build Gluon Creator Library" ON )
option( BUILD_NODEEDITOR "Build the Node Editor component" ON)
option( BUILD_GLUONAPPS "Build the Gluon applications" ON )
option( BUILD_TOOLS "Build Gluon Tools" ON )
option( BUILD_TESTS "Build Unit Tests for the Gluon libraries and applications" ON )
option( BUILD_EXAMPLES "Build and install example applications" ON )
option( INSTALL_GAMES "Install the example games" OFF )

#### Global Dependencies ####
find_package( ECM REQUIRED CONFIG )
find_package( Qt5Core REQUIRED CONFIG )
find_package( Qt5Gui REQUIRED CONFIG )

list( APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH} )
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

if( BUILD_TESTS )
    find_package( Qt5Test REQUIRED )
endif()

include( cmake/GluonMacros.cmake )

#### Global Variables and Defaults ####
include( cmake/GluonVariables.cmake )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )

# Enable moc generation by default
set( CMAKE_AUTOMOC TRUE )

# Default to hidden symbols
set( CMAKE_CXX_VISIBILITY_PRESET hidden )
set( CMAKE_VISIBILITY_INLINES_HIDDEN 1 )

# Use C++11 by default and enable almost all warnings
if( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
    set( CMAKE_CXX_FLAGS "-fPIC -std=c++11 -Wall -Wno-switch -Wno-unused-local-typedefs" )
    set( CMAKE_CXX_FLAGS_RELEASE "-DGLUON_MAX_LOG_LEVEL=GluonCore::LogWarning" )
elseif( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
    set( CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-switch" )
    set( CMAKE_CXX_FLAGS_RELEASE "-DGLUON_MAX_LOG_LEVEL=GluonCore::LogWarning" )
endif( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )

# To make sure we can run when not installed into $LD_LIBRARY_PATH
set( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}" )

# Always include CMAKE_CURRENT_SOURCE_DIR and CMAKE_CURRENT_BINARY_DIR by default
set( CMAKE_INCLUDE_CURRENT_DIR TRUE )

# Enable tests if specified
if( BUILD_TESTS )
    enable_testing()
endif()

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

if( BUILD_NODEEDITOR )
    add_subdirectory( nodeeditor )
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
log_status( NodeEditor )
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

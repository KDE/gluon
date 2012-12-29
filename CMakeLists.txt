cmake_minimum_required(VERSION 2.8)
project(Gluon)

include(cmake/GluonVariables.cmake)
include(cmake/GluonMacros.cmake)

#Project options, to provide a selective build process
#Note that some of these are mutually exclusive or just
#do not make a whole lot of sense combined.
option(WITH_KDE "Build with KDE Development Platform Support" ON)
option(BUILD_GLUONAUDIO "Build Gluon Audio Library" ON)
option(BUILD_GLUONINPUT "Build Gluon Input Library" ON)
option(BUILD_GLUONSMARTS "Build SMARTS Game AI Library" ON)
option(BUILD_GLUONGRAPHICS "Build Gluon Graphics Library" ON)
option(BUILD_GLUONENGINE "Build Gluon Engine Library" ON)
option(BUILD_GLUONPLAYER "Build Gluon Player Library" ON)
option(BUILD_GLUONCREATOR "Build Gluon Creator Application" ON)
option(BUILD_TOOLS "Build Gluon Tools" ON)
option(BUILD_TESTS "Build Unit Tests for the Gluon libraries and applications" OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
        set(CMAKE_CXX_FLAGS "-Wall -Wno-switch")
    else(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
        set(CMAKE_CXX_FLAGS "-Wall -Wno-switch -Wno-unused-local-typedefs")
    endif(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-Wall -Wno-switch")
endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Eigen3 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${EIGEN3_INCLUDE_DIR})

# Qt is a global requirement
find_package(Qt4 4.7.1 REQUIRED)
if( WITH_KDE )
    find_package( KDE4 )
endif()

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

##### Gluon Libraries #####

####### Gluon Core ########
add_subdirectory(core)

####### Gluon Audio #######
if(BUILD_GLUONAUDIO)
    add_subdirectory(audio)
endif()

####### Gluon Input #######
if(BUILD_GLUONINPUT)
    add_subdirectory(input)
endif()

###### Gluon Graphics #####
if(BUILD_GLUONGRAPHICS)
    add_subdirectory(graphics)
endif()

####### SMARTS Library #######
if(BUILD_GLUONSMARTS)
     add_subdirectory(smarts)
endif()

###### Gluon Engine #######
if(BUILD_GLUONENGINE)
    add_subdirectory(engine)
endif()

###### Gluon Player ######
if(BUILD_GLUONPLAYER)
    add_subdirectory(player)
endif()

###### Gluon Creator ######
if(BUILD_GLUONCREATOR)
    add_subdirectory(creator)
endif()

###### Gluon Tools ######
if(BUILD_TOOLS)
    add_subdirectory(tools)
endif()

message( STATUS )
message( STATUS "========== Gluon Build Information ==========" )
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
log_status( Tools )
log_status( Tests )
message( STATUS )
message( STATUS "To change any of these options, override them using -D{OPTION_NAME}=ON/OFF on the commandline." )
message( STATUS "To build and install Gluon, run \"make\" and \"make install\"" )
message( STATUS )

###### CPACK part ######
include( CPack )

###### CTEST part ######
if( BUILD_TESTS )
    enable_testing()
    include( CTest )
endif()

cmake_minimum_required(VERSION 2.8)
project(gluon)

#Project options, to provide a selective build process
#Note that some of these are mutually exclusive or just
#do not make a whole lot of sense combined.
option(WITH_KDE "Build with KDE Development Platform Support" OFF)
option(BUILD_GLUON_AUDIO "Build Gluon Audio Library" OFF)
option(BUILD_GLUON_INPUT "Build Gluon Input Library" OFF)
option(BUILD_GLUON_GRAPHICS "Build Gluon Graphics Library" OFF)
option(BUILD_GLUON_ENGINE "Build Gluon Engine Library" OFF)
option(BUILD_GLUON_PLAYER "Build Gluon Player Application" ON)
option(BUILD_GLUON_CREATOR "Build Gluon Creator Application" ON)

set(GLUON_BUILD_ALL TRUE
    CACHE BOOL "Build all of Gluon"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#Gluon Libraries
add_subdirectory(core)
if(BUILD_GLUON_AUDIO)
    add_subdirectory(audio)
endif()
if(BUILD_GLUON_INPUT)
    add_subdirectory(input)
endif()
if(BUILD_GLUON_GRAPHICS)
    add_subdirectory(graphics)
endif()
if(BUILD_GLUON_ENGINE)
    add_subdirectory(engine)
endif()

#Gluon Applications - Currently dependant on KDE Development Platform
find_package(KDE4)
if(KDE4_FOUND AND WITH_KDE)
    if(BUILD_GLUON_PLAYER)
        add_subdirectory(player)
    endif(BUILD_GLUON_PLAYER)
    if(BUILD_GLUON_CREATOR)
        add_subdirectory(creator)
    endif(BUILD_GLUON_CREATOR)
else(KDE4_FOUND AND WITH_KDE)
    if(WITH_KDE)
        message(WARNING "WITH_KDE is enabled but KDE libraries are not found - not building KDE-dependant applications")
        set(WITH_KDE OFF)
    endif(WITH_KDE)
    set(BUILD_GLUON_PLAYER OFF)
    set(BUILD_GLUON_CREATOR OFF)
endif(KDE4_FOUND AND WITH_KDE)

message(STATUS)
message(STATUS "========== Gluon Build Information ==========")
message(STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Enable KDE Development Platform support (WITH_KDE): ${WITH_KDE}")
message(STATUS "Build Gluon Audio Library (BUILD_GLUON_AUDIO): ${BUILD_GLUON_AUDIO}")
message(STATUS "Build Gluon Input Library (BUILD_GLUON_INPUT): ${BUILD_GLUON_INPUT}")
message(STATUS "Build Gluon Graphics Library (BUILD_GLUON_GRAPHICS): ${BUILD_GLUON_GRAPHICS}")
message(STATUS "Build Gluon Engine Library (BUILD_GLUON_ENGINE): ${BUILD_GLUON_ENGINE}")
message(STATUS "Build Gluon Player Application (BUILD_GLUON_PLAYER): ${BUILD_GLUON_PLAYER}")
message(STATUS "Build Gluon Creator Application (BUILD_GLUON_CREATOR): ${BUILD_GLUON_CREATOR}")
message(STATUS "To change any of these options, override them using -D{OPTION_NAME} on the commandline.")
message(STATUS "To build and install Gluon, run \"make\" and \"make install\"")
message(STATUS)


cmake_minimum_required(VERSION 2.8)
project(Gluon)

set(GLUON_VERSION_MAJOR     0)
set(GLUON_VERSION_MINOR     72)
set(GLUON_VERSION_PATCH     0)
set(GLUON_VERSION_STRING    "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}")
set(GLUON_VERSION_NAME      "Alpha Particle")

#Project options, to provide a selective build process
#Note that some of these are mutually exclusive or just
#do not make a whole lot of sense combined.
option(WITH_KDE "Build with KDE Development Platform Support" ON)
option(BUILD_GLUON_AUDIO "Build Gluon Audio Library" ON)
option(BUILD_GLUON_INPUT "Build Gluon Input Library" ON)
option(BUILD_GLUON_SMARTS "Build SMARTS Game AI Library" ON)
option(BUILD_GLUON_SMARTS_EDITOR "Build Gluon SMARTS Editor" ON)
option(BUILD_GLUON_GRAPHICS "Build Gluon Graphics Library" ON)
option(BUILD_GLUON_ENGINE "Build Gluon Engine Library" ON)
option(BUILD_GLUON_PLAYER "Build Gluon Player Library" ON)
option(BUILD_GLUON_PLAYER_ACTIVE "Build Gluon Player for Plasma Active" OFF)
option(BUILD_GLUON_PLAYER_DESKTOP "Build Gluon Player for KDE Desktop" ON)
option(BUILD_GLUON_PLAYER_FREMANTLE "Build Gluon Player for Fremantle" OFF)
option(BUILD_GLUON_PLAYER_HARMATTAN "Build Gluon Player for Harmattan" OFF)
option(BUILD_GLUON_CREATOR "Build Gluon Creator Application" ON)
option(BUILD_GLUON_CREATOR_VCS "Build Version Control System support for the Gluon Creator" OFF)
option(BUILD_GLUON_TOOLS "Build Gluon Tools" ON)
option(BUILD_GLUON_TESTS "Build Unit Tests for the Gluon libraries and applications" ON)
option(INSTALL_EXAMPLES "Install the game examples for Gluon Player" ON)

if(CMAKE_INSTALL_PREFIX STREQUAL "/usr")
    option(INSTALL_CMAKE_FILES "Install the *.cmake files into the CMake root" ON)
else()
    option(INSTALL_CMAKE_FILES "Install the *.cmake files into the CMake root" OFF)
endif()

set(GLUON_BUILD_ALL TRUE
    CACHE INTERNAL "Build all of Gluon"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -Wno-switch -O2 -g")
        set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wno-switch -O2")
        set(CMAKE_CXX_FLAGS_DEBUG  "-Wall -Wno-switch -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE)
    else(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -Wno-switch -Wno-unused-local-typedefs -O2 -g")
        set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wno-switch -Wno-unused-local-typedefs -O2")
        set(CMAKE_CXX_FLAGS_DEBUG  "-Wall -Wno-switch -Wno-unused-local-typedefs -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE)
    endif(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Eigen3 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${EIGEN3_INCLUDE_DIR})

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}")

##### Gluon Libraries #####

####### Gluon Core ########
add_subdirectory(core)

####### Gluon Audio #######
if(BUILD_GLUON_AUDIO)
    add_subdirectory(audio)
endif()

####### Gluon Input #######
if(BUILD_GLUON_INPUT)
    add_subdirectory(input)
endif()

###### Gluon Graphics #####
if(BUILD_GLUON_GRAPHICS)
    add_subdirectory(graphics)
endif()

####### SMARTS Library #######
if(BUILD_GLUON_SMARTS)
     add_subdirectory(smarts)
endif()

###### Gluon Engine #######
if(BUILD_GLUON_ENGINE)
    add_subdirectory(engine)
endif()

###### Gluon Player ######
# Checks must be done here because it does its own checks only when cmake was not called here ...
if(BUILD_GLUON_PLAYER)
    add_subdirectory(player)
else(BUILD_GLUON_PLAYER)
    set(INSTALL_EXAMPLES OFF)
endif(BUILD_GLUON_PLAYER)

set(KDE_FAILED FALSE)
######## KDE Parts ########
if(BUILD_GLUON_PLAYER_ACTIVE OR BUILD_GLUON_CREATOR OR WITH_KDE)
    find_package(KDE4)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

    if(NOT KDE4_FOUND)
        set(BUILD_GLUON_PLAYER_ACTIVE OFF)
        set(BUILD_GLUON_CREATOR OFF)
        set(KDE_FAILED TRUE)
        set(WITH_KDE FALSE)
    endif(NOT KDE4_FOUND)

    find_package(KDevPlatform 1.0.2)
    if(NOT KDevPlatform_FOUND)
        set(BUILD_GLUON_CREATOR_VCS OFF)
    endif(NOT KDevPlatform_FOUND)
endif()

###### Gluon Creator ######
if(BUILD_GLUON_CREATOR)
    add_subdirectory(creator)
endif(BUILD_GLUON_CREATOR)

###### Gluon Tools ######
if(BUILD_GLUON_TOOLS)
    add_subdirectory(tools)
endif(BUILD_GLUON_TOOLS)

message(STATUS)
message(STATUS "========== Gluon Build Information ==========")
message(STATUS "Build Version: ${GLUON_VERSION_STRING} (${GLUON_VERSION_NAME})")
message(STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Install the *.cmake files into CMake root (INSTALL_CMAKE_FILES): ${INSTALL_CMAKE_FILES}")
message(STATUS "Install the game examples for Gluon Player (INSTALL_EXAMPLES): ${INSTALL_EXAMPLES}")
message(STATUS "Enable KDE Development Platform support (WITH_KDE): ${WITH_KDE}")
message(STATUS "Build Gluon Audio Library (BUILD_GLUON_AUDIO): ${BUILD_GLUON_AUDIO}")
message(STATUS "Build Gluon Input Library (BUILD_GLUON_INPUT): ${BUILD_GLUON_INPUT}")
message(STATUS "Build Gluon Graphics Library (BUILD_GLUON_GRAPHICS): ${BUILD_GLUON_GRAPHICS}")
if(BUILD_GLUON_GRAPHICS)
    message(STATUS "    Build Mesh loading support: ${GLUON_GRAPHICS_HAS_MESH}")
endif(BUILD_GLUON_GRAPHICS)
message(STATUS "Build Smarts Game AI Library (BUILD_GLUON_SMARTS): ${BUILD_GLUON_SMARTS}")
message(STATUS "Build Gluon Engine Library (BUILD_GLUON_ENGINE): ${BUILD_GLUON_ENGINE}")
if(BUILD_GLUON_ENGINE)
    message(STATUS "    Build Components dependant on Gluon Audio (BUILD_AUDIO_COMPONENTS): ${BUILD_AUDIO_COMPONENTS}")
    message(STATUS "    Build Assets dependant on Gluon Audio (BUILD_AUDIO_ASSETS): ${BUILD_AUDIO_ASSETS}")
    message(STATUS "    Build Components dependant on Gluon Graphics (BUILD_GRAPHICS_COMPONENTS): ${BUILD_GRAPHICS_COMPONENTS}")
    message(STATUS "    Build Assets dependant on Gluon Graphics (BUILD_GRAPHICS_ASSETS): ${BUILD_GRAPHICS_ASSETS}")
    message(STATUS "    Build Components dependant on Gluon Input (BUILD_INPUT_COMPONENTS): ${BUILD_INPUT_COMPONENTS}")
    message(STATUS "    Build Assets dependant on Gluon Input (BUILD_INPUT_ASSETS): ${BUILD_INPUT_ASSETS}")
    message(STATUS "    Build Components related to physics (BUILD_PHYSICS_COMPONENTS): ${BUILD_PHYSICS_COMPONENTS}")
    message(STATUS "    Build Assets related to physics (BUILD_PHYSICS_ASSETS): ${BUILD_PHYSICS_ASSETS}")
    message(STATUS "    Build other Components (BUILD_OTHER_COMPONENTS): ${BUILD_OTHER_COMPONENTS}")
    message(STATUS "    Build other Assets (BUILD_OTHER_ASSETS): ${BUILD_OTHER_ASSETS}")
endif()
message(STATUS "Build Gluon Player for Plasma Active (BUILD_GLUON_PLAYER_ACTIVE): ${BUILD_GLUON_PLAYER_ACTIVE}")
message(STATUS "Build Gluon Player Library and Qt Application (BUILD_GLUON_PLAYER): ${BUILD_GLUON_PLAYER}")
message(STATUS "Build Gluon Creator Application (BUILD_GLUON_CREATOR): ${BUILD_GLUON_CREATOR}")
message(STATUS "Build Version Control System support for the Gluon Creator (BULD_GLUON_CREATOR_VCS): ${BUILD_GLUON_CREATOR_VCS}")
message(STATUS)
message(STATUS "To change any of these options, override them using -D{OPTION_NAME} on the commandline.")
message(STATUS "To build and install Gluon, run \"make\" and \"make install\"")
message(STATUS)
if(KDE_FAILED)
    message(STATUS)
    message(STATUS "Gluon Creator and/or Plasma Active player was/were disabled because KDE could not be found.")
    message(STATUS "Gluon KDE simple and extended players were disabled because KDE could not be found.")
    message(STATUS)
endif(KDE_FAILED)


if(INSTALL_CMAKE_FILES)
    install(
        FILES
        core/cmake/FindGluon.cmake
        core/cmake/FindGluonCore.cmake
        audio/cmake/FindGluonAudio.cmake
        audio/cmake/FindOggVorbis.cmake
        audio/cmake/FindAlure.cmake
        graphics/cmake/FindGluonGraphics.cmake
        cmake/FindOpenGLES2.cmake
        input/cmake/FindGluonInput.cmake
        engine/cmake/FindGluonEngine.cmake
        creator/lib/cmake/FindGluonCreator.cmake
        DESTINATION
        ${CMAKE_ROOT}/Modules
        OPTIONAL
    )
else()
    install(
        FILES
        core/cmake/FindGluon.cmake
        core/cmake/FindGluonCore.cmake
        audio/cmake/FindGluonAudio.cmake
        audio/cmake/FindAlure.cmake
        graphics/cmake/FindGluonGraphics.cmake
        cmake/FindOpenGLES2.cmake
        input/cmake/FindGluonInput.cmake
        engine/cmake/FindGluonEngine.cmake
        creator/lib/cmake/FindGluonCreator.cmake
        DESTINATION
        ${SHARE_INSTALL_DIR}/gluon/cmake
        OPTIONAL
    )
endif()

###### CPACK part ######
include(CPack)

###### CTEST part ######
include(CTest)

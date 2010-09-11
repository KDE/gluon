cmake_minimum_required(VERSION 2.6)
project(Gluon)

#Project options, to provide a selective build process
#Note that some of these are mutually exclusive or just
#do not make a whole lot of sense combined.
option(WITH_KDE "Build with KDE Development Platform Support" ON)
option(BUILD_GLUON_AUDIO "Build Gluon Audio Library" ON)
option(BUILD_GLUON_INPUT "Build Gluon Input Library" ON)
option(BUILD_GLUON_GRAPHICS "Build Gluon Graphics Library" ON)
option(BUILD_GLUON_ENGINE "Build Gluon Engine Library" ON)
option(BUILD_GLUON_PLAYER "Build Gluon Player Application" ON)
option(BUILD_PLASMOID "Build Gluon Player Plasmoid" ON)
option(BUILD_GLUON_CREATOR "Build Gluon Creator Application" ON)
option(INSTALL_EXAMPLES "Install the game examples for Gluon Player" ON)

if(APPLE)
	set(MAC_APPLICATIONS_PATH "/Applications")
	set(MAC_FRAMEWORK_PATH "/Library/Frameworks")
endif()

set(GLUON_BUILD_ALL TRUE
    CACHE INTERNAL "Build all of Gluon"
)

if(CMAKE_INSTALL_PREFIX STREQUAL "/usr")
    option(INSTALL_CMAKE_FILES "Install the *.cmake files into the CMake root" ON)
else()
    option(INSTALL_CMAKE_FILES "Install the *.cmake files into the CMake root" OFF)
endif()

set(GLUON_BUILD_ALL TRUE
    CACHE INTERNAL "Build all of Gluon"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})


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
###### Gluon Engine #######
if(BUILD_GLUON_ENGINE)
    add_subdirectory(engine)
endif()

######## KDE Parts ########
if(WITH_KDE)
    set(BUILD_PLASMOID ON)
    set(BUILD_GLUON_CREATOR ON)
endif(WITH_KDE)
if(BUILD_PLASMOID OR BUILD_GLUON_CREATOR)
    find_package(KDE4)
    if(NOT KDE4_FOUND)
        set(BUILD_PLASMOID OFF)
        set(BUILD_GLUON_CREATOR OFF)
        set(KDE_FAILED TRUE)
    endif(NOT KDE4_FOUND)
endif(BUILD_PLASMOID OR BUILD_GLUON_CREATOR)

###### Gluon Creator ######
if(BUILD_GLUON_CREATOR)
    add_subdirectory(creator)
endif(BUILD_GLUON_CREATOR)

###### Gluon Player ######
# Checks must be done here because it does its own checks only when cmake was not called here ... 
if(BUILD_GLUON_PLAYER)
    set(LIBATTICA_MIN_VERSION 0.1.90)
    find_package(LibAttica)
    if(LIBATTICA_FOUND)
        add_subdirectory(player)
    else(LIBATTICA_FOUND)
        set(BUILD_GLUON_PLAYER OFF)
        set(INSTALL_EXAMPLES OFF)
        set(BUILD_PLASMOID OFF)
        set(ATTICA_FAILED TRUE)
    endif(LIBATTICA_FOUND)
else(BUILD_GLUON_PLAYER)
    set(INSTALL_EXAMPLES OFF)
    set(BUILD_PLASMOID OFF)
    set(PLAYER_FAILED TRUE)
endif(BUILD_GLUON_PLAYER)

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
message(STATUS "Build Gluon Player Library and Qt Application (BUILD_GLUON_PLAYER): ${BUILD_GLUON_PLAYER}")
message(STATUS "Build Gluon Player Plasmoid (BUILD_PLASMOID): ${BUILD_PLASMOID}")
message(STATUS "Build Gluon Creator Application (BUILD_GLUON_CREATOR): ${BUILD_GLUON_CREATOR}")
message(STATUS)
message(STATUS "To change any of these options, override them using -D{OPTION_NAME} on the commandline.")
message(STATUS "To build and install Gluon, run \"make\" and \"make install\"")
message(STATUS)
if(KDE_FAILED OR ATTICA_FAILED OR PLAYER_FAILED)
    message(STATUS)
    message(STATUS "WARNING!")
endif(KDE_FAILED OR ATTICA_FAILED OR PLAYER_FAILED)
if(KDE_FAILED)
    message(STATUS)
    message(STATUS "Gluon Creator and/or Plasmoid was/were disabled because KDE could not be found.")
    message(STATUS)
endif(KDE_FAILED)
if(ATTICA_FAILED)
    message(STATUS)
    message(STATUS "Could not find LibAttica or a too old version was found.")
    message(STATUS "Building player and plasmoid and installing game examples were disabled.")
    message(STATUS)
endif(ATTICA_FAILED)
if(PLAYER_FAILED)
    message(STATUS)
    message(STATUS "Building Plasmoid and/or installing examples was/were disabled because player is not installed.")
    message(STATUS)
endif(PLAYER_FAILED)


if(NOT APPLE)
	if(INSTALL_CMAKE_FILES)
		install(
			FILES
			core/cmake/FindGluon.cmake
			core/cmake/FindGluonCore.cmake
			audio/cmake/FindGluonAudio.cmake
			audio/cmake/FindOggVorbis.cmake
			audio/cmake/FindSndFile.cmake
			graphics/cmake/FindGluonGraphics.cmake
			graphics/cmake/FindGLEW.cmake
			input/cmake/FindGluonInput.cmake
			engine/cmake/FindGluonEngine.cmake
			creator/lib/cmake/FindGluonCreator.cmake
			DESTINATION
			${CMAKE_ROOT}/Modules
			OPTIONAL
		)
	endif()
endif()

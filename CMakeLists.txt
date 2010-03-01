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
option(BUILD_GLUON_PLAYER "Build Gluon Player Application" OFF)
option(BUILD_GLUON_CREATOR "Build Gluon Creator Application" ON)
option(INSTALL_CMAKE_FILES "Install the FindGluon*.cmake files into the CMake root" OFF)

set(GLUON_BUILD_ALL TRUE
    CACHE INTERNAL "Build all of Gluon"
)

if(CMAKE_INSTALL_PREFIX STREQUAL "/usr")
    set(INSTALL_CMAKE_FILES ON)
endif()

add_definitions(-DEIGEN_DONT_ALIGN -DEIGEN_DONT_VECTORIZE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

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

#Gluon Applications - Currently dependant on KDE Development Platform
find_package(KDE4)
if(KDE4_FOUND AND WITH_KDE)
    ##### Gluon Player #####
    if(BUILD_GLUON_PLAYER)
       # add_subdirectory(player)
    endif(BUILD_GLUON_PLAYER)
    ##### Gluon Creator ####
    if(BUILD_GLUON_CREATOR)
     #   add_subdirectory(creator)
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
message(STATUS "Build Version: ${GLUON_VERSION_STRING}")
message(STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Install the FindGluon*.cmake files into CMake root (INSTALL_CMAKE_FILES): ${INSTALL_CMAKE_FILES}")
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
message(STATUS "Build Gluon Player Application (BUILD_GLUON_PLAYER): ${BUILD_GLUON_PLAYER}")
message(STATUS "Build Gluon Creator Application (BUILD_GLUON_CREATOR): ${BUILD_GLUON_CREATOR}")
message(STATUS "")
message(STATUS "To change any of these options, override them using -D{OPTION_NAME} on the commandline.")
message(STATUS "To build and install Gluon, run \"make\" and \"make install\"")
message(STATUS)

if(INSTALL_CMAKE_FILES)
    install(
        FILES
        core/cmake/FindGluon.cmake
        core/cmake/FindGluonCore.cmake
        audio/cmake/FindGluonAudio.cmake
        graphics/cmake/FindGluonGraphics.cmake
        input/cmake/FindGluonInput.cmake
        engine/cmake/FindGluonEngine.cmake
        creator/lib/cmake/FindGluonCreator.cmake
        DESTINATION
        ${CMAKE_ROOT}/Modules
        OPTIONAL
    )
endif()

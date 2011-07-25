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
option(BUILD_GLUON_GRAPHICS "Build Gluon Graphics Library" ON)
option(BUILD_GLUON_ENGINE "Build Gluon Engine Library" ON)
option(BUILD_GLUON_PLAYER "Build Gluon Player Application" ON)
option(BUILD_PLASMOID "Build Gluon Player Plasmoid" ON)
option(BUILD_GLUON_CREATOR "Build Gluon Creator Application" ON)
option(BUILD_GLUON_CREATOR_VCS "Build Version Control System support for the Gluon Creator" OFF)
option(BUILD_GLUON_TESTS "Build Unit Tests for the Gluon libraries and applications" ON)
option(INSTALL_EXAMPLES "Install the game examples for Gluon Player" ON)

if(CMAKE_INSTALL_PREFIX STREQUAL "/usr")
    option(INSTALL_CMAKE_FILES "Install the *.cmake files into the CMake root" ON)
else()
    option(INSTALL_CMAKE_FILES "Install the *.cmake files into the CMake root" OFF)
endif()

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/gluon")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(GLUON_BUILD_ALL TRUE
    CACHE INTERNAL "Build all of Gluon"
)

if(NOT MSVC)
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -Wno-switch -O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wno-switch -O2")
SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall -Wno-switch -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE)


# Build Release by default
IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF ()
endif(NOT MSVC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(OPENGL_REAL_LIBS "")
set(OPENGL_REAL_INCLUDE_DIR "")
find_package(OpenGL)
if(NOT OPENGL_FOUND)
    #try looking for GLES
    find_package(OpenGLES2)
    if(OPENGLES_FOUND)
        set(OPENGL_REAL_INCLUDE_DIR ${OPENGLES_INCLUDE_DIR})
        set(OPENGL_REAL_LIBS ${OPENGLES_LIBRARIES})
        add_definitions(-DGLUON_GRAPHICS_GLES)
        message(STATUS "Found OpenGLES2 graphics: ${OPENGL_REAL_INCLUDE_DIR}")
    endif(OPENGLES_FOUND)
else(NOT OPENGL_FOUND)
    set(OPENGL_REAL_INCLUDE_DIR ${OPENGL_INCLUDE_DIR})
    set(OPENGL_REAL_LIBS ${OPENGL_gl_LIBRARY})
    message(STATUS "Found OpenGL: ${OPENGL_REAL_INCLUDE_DIR}")
endif(NOT OPENGL_FOUND)

if(OPENGL_REAL_LIBS STREQUAL "" OR OPENGL_INCLUDE_DIR STREQUAL "")
    message(FATAL_ERROR "Could NOT find OpenGL!")
endif()

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

###### Gluon Player ######
# Checks must be done here because it does its own checks only when cmake was not called here ...
if(BUILD_GLUON_PLAYER)
    add_subdirectory(player)
else(BUILD_GLUON_PLAYER)
    set(INSTALL_EXAMPLES OFF)
endif(BUILD_GLUON_PLAYER)

set(KDE_FAILED FALSE)
######## KDE Parts ########
if(BUILD_PLASMOID OR BUILD_GLUON_CREATOR OR WITH_KDE)
    find_package(KDE4)
    if(NOT KDE4_FOUND)
        set(BUILD_PLASMOID OFF)
        set(BUILD_GLUON_CREATOR OFF)
        set(KDE_FAILED TRUE)
        set(WITH_KDE FALSE)
    endif(NOT KDE4_FOUND)

    find_package(KDevPlatform 1.0.2)
    if(NOT KDevPlatform_FOUND)
        set(BUILD_GLUON_CREATOR_VCS OFF)
    endif(NOT KDevPlatform_FOUND)
endif(BUILD_PLASMOID OR BUILD_GLUON_CREATOR OR WITH_KDE)

###### Gluon Creator ######
if(BUILD_GLUON_CREATOR)
    add_subdirectory(creator)
endif(BUILD_GLUON_CREATOR)

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
message(STATUS "Build Version Control System support for the Gluon Creator (BULD_GLUON_CREATOR_VCS): ${BUILD_GLUON_CREATOR_VCS}")
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
        audio/cmake/FindSndFile.cmake
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

#Packaging options
#common package generation settings
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An open framework to create, distribute and play games")
set(CPACK_PACKAGE_NAME "Gluon")
set(CPACK_PACKAGE_VERSION "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}")
set(CPACK_PACKAGE_FILE_NAME "Gluon-${GLUON_VERSION_STRING}")
set(CPACK_GENERATOR "RPM;DEB;TGZ;NSIS")
set(CPACK_PACKAGE_CONTACT "Laszlo Papp <lpapp@kde.org>, Arjen Hiemstra <ahiemstra@heimr.nl>")

#debian package generation
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt4-gui (>= 4.6), libqt4-opengl (>= 4.6), libopenal1, libsndfile1, libgles2")
set(CPACK_DEBIAN_PACKAGE_SECTION "Games")

#rpm package generation
#set(CPACK_RPM_PACKAGE_REQUIRES "libqt-devel (>= 4.7.1), libsndfile")

#Windows NSIS
#set(CPACK_NSIS_MUI_ICON "installer.ico")
#set(CPACK_NSIS_MUI_UNIICON "uninstaller.ico")
#set(CPACK_PACKAGE_ICON "installer.bmp")
#set(CPACK_NSIS_COMPRESSOR "/SOLID lzma")
#set(CPACK_NSIS_INSTALLED_ICON_NAME "")
set(CPACK_NSIS_HELP_LINK "http://gluon.gamingfreedom.org/about-gluon/contact")
set(CPACK_NSIS_URL_INFO_ABOUT "http://gluon.gamingfreedom.org/")
set(CPACK_NSIS_CONTACT "gluon@kde.org")

include(InstallRequiredSystemLibraries)
include(CPack)
include(CTest)

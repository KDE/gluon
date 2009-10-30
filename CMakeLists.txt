cmake_minimum_required(VERSION 2.6)
project(gluon)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(Qt4 REQUIRED)

if(APPLE)
find_library(IOKIT_LIBRARY NAMES IOKit)
find_library(COREFOUNDATION_LIBRARY NAMES CoreFoundation)
find_library(PHONON_LIBRARY NAMES phonon)
endif()

IF(NOT WIN32 AND NOT APPLE)
find_package(KDE4 REQUIRED)
ENDIF()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Eigen2 REQUIRED)

IF(NOT WIN32 AND NOT APPLE)
find_package(X11 REQUIRED)
ENDIF(NOT WIN32 AND NOT APPLE)

IF(NOT WIN32 AND NOT APPLE)
find_package(OpenAL REQUIRED)
find_package(Alut REQUIRED)
find_package(SndFile REQUIRED)
find_package(OggVorbis REQUIRED)
ENDIF(NOT WIN32 AND NOT APPLE)

IF(NOT WIN32 AND NOT APPLE)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES})
ENDIF()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${OPENAL_INCLUDE_DIR})
include_directories(${QT_QTOPENGL_INCLUDE_DIR})
include_directories(${EIGEN2_INCLUDE_DIR})

## TODO: are those really needed?  Yes it's ! Otherwise a lot of Box2d warning appear!
if(NOT WIN32)
add_definitions(-W -Wall -Wno-unused) 
add_definitions(-fvisibility=default)
add_definitions( -DKDE_DEFAULT_DEBUG_AREA=12500 )
endif(NOT WIN32)


add_subdirectory(Box2D)
add_subdirectory(common)
add_subdirectory(kgl)
IF(NOT WIN32)
add_subdirectory(kal)
add_subdirectory(kcl)
add_subdirectory(src)
ENDIF(NOT WIN32)
add_subdirectory(cmake)
IF(NOT WIN32 AND NOT Q_WS_MAC)
add_subdirectory(icons)
add_subdirectory(systemsettings)
#add_subdirectory(creator)
ENDIF(NOT WIN32 AND NOT Q_WS_MAC)

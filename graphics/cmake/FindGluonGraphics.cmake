# - Try to find Gluon's common files
#
# Once done this will define
#   GLUON_GRAPHICS_FOUND - system has Gluon graphics files
#   GLUON_GRAPHICS_INCLUDES - all include directories required for Gluon's graphics files
#   GLUON_GRAPHICS_INCLUDE_DIR - the Gluon graphics include directory
#   GLUON_GRAPHICS_LIBRARY - The Gluon Graphics library location
#   GLUON_GRAPHICS_LIBS - All libraries necessary for Gluon Graphics to work
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (GLUON_GRAPHICS_LIBRARY AND GLUON_GRAPHICS_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_GRAPHICS_FOUND TRUE)
endif (GLUON_GRAPHICS_LIBRARY AND GLUON_GRAPHICS_INCLUDE_DIR)

if (GluonGraphics_FIND_REQUIRED)
    set(_gluonGraphicsReq "REQUIRED")
endif (GluonGraphics_FIND_REQUIRED)

find_package(GluonCore ${_gluonGraphicsReq})

set(CMAKE_MODULE_PATH ${SHARE_INSTALL_DIR}/gluon/cmake)

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
        message(STATUS "Found OpenGLES2: ${OPENGL_REAL_INCLUDE_DIR}")
    endif(OPENGLES_FOUND)
else(NOT OPENGL_FOUND)
    set(OPENGL_REAL_INCLUDE_DIR ${OPENGL_INCLUDE_DIR})
    set(OPENGL_REAL_LIBS ${OPENGL_gl_LIBRARY})
    message(STATUS "Found OpenGL: ${OPENGL_REAL_INCLUDE_DIR}")
endif(NOT OPENGL_FOUND)

if(GluonGraphics_FIND_REQUIRED)
    if(OPENGL_REAL_LIBS STREQUAL "" OR OPENGL_REAL_LIBS STREQUAL "")
        message(FATAL_ERROR "Could NOT find OpenGL!")
    endif()
endif()

find_path(GLUON_GRAPHICS_INCLUDE_DIR
    NAMES
    graphics/engine.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
    PATH_SUFFIXES
    gluon
)

set(GLUON_GRAPHICS_INCLUDES
    ${GLUON_GRAPHICS_INCLUDE_DIR}
    ${GLUON_CORE_INCLUDES}
    ${OPENGL_REAL_INCLUDE_DIR}
)

find_library(GLUON_GRAPHICS_LIBRARY
    NAMES
    GluonGraphics
    PATHS
    ${LIB_INSTALL_DIR}
)

set(GLUON_GRAPHICS_LIBS
    ${GLUON_GRAPHICS_LIBRARY}
    ${GLUON_CORE_LIBS}
    ${QT_QTOPENGL_LIBRARY}
    ${OPENGL_REAL_LIBS}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonGraphics DEFAULT_MSG GLUON_GRAPHICS_LIBRARY GLUON_GRAPHICS_INCLUDE_DIR)

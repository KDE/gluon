# - Try to find the Gluon Core library.
#
# Once done this will define
#  GLUON_CORE_FOUND - The Gluon Core library was found
#  GLUON_CORE_LIBRARY - The Gluon Core library location
#  GLUON_CORE_INCLUDES - all include directories required for the Gluon Core library
#  GLUON_CORE_INCLUDE_DIR - the Gluon Core include directory
#
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the COPYING-CMAKE-SCRIPTS file from Gluon's Source tree.

if (GLUON_CORE_LIBRARY AND GLUON_CORE_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_CORE_FOUND TRUE)
endif (GLUON_CORE_LIBRARY AND GLUON_CORE_INCLUDE_DIR)

if (GluonCore_FIND_REQUIRED)
    set(_gluonCoreReq "REQUIRED")
endif (GluonCore_FIND_REQUIRED)

find_package(Qt4 ${_gluonCoreReq})
find_package(Eigen2 ${_gluonCoreReq})

set(GLUON_VERSION_MAJOR     0       CACHE STRING "Gluon Major Version")
set(GLUON_VERSION_MINOR     60      CACHE STRING "Gluon Minor Version")
set(GLUON_VERSION_PATCH     0       CACHE STRING "Gluon Patch Version")
set(GLUON_VERSION_STRING    "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}" CACHE STRING "Gluon Version String")

if(NOT INCLUDE_INSTALL_DIR)
    set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include CACHE PATH "The subdirectory relative to the install prefix where header files will be installed.")
endif()
if(NOT LIB_INSTALL_DIR)
    set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed.")
endif()
if(NOT SHARE_INSTALL_DIR)
    set(SHARE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share CACHE PATH "The subdiractory relative to the install prefix where data and other files will be installed.")
endif()

find_path(GLUON_CORE_INCLUDE_DIR
    NAMES
    core/singleton.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
    PATH_SUFFIXES
    gluon
)

set(GLUON_CORE_INCLUDES
    ${GLUON_CORE_INCLUDE_DIR}
    ${QT_INCLUDES}
    ${EIGEN2_INCLUDE_DIR}
    CACHE PATHS "Includes required for Gluon Core"
)

find_library(GLUON_CORE_LIBRARY
    NAMES
    GluonCore
    PATHS
    ${LIB_INSTALL_DIR}
)

set(GLUON_CORE_LIBS
    ${GLUON_CORE_LIBRARY}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    CACHE PATHS "Libraries required for Gluon Core"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonCore DEFAULT_MSG GLUON_CORE_LIBRARY GLUON_CORE_INCLUDE_DIR)

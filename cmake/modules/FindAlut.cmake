# Locate FreeAlut
# This module defines
# ALUT_LIBRARY
# ALUT_FOUND, if false, do not try to link to FreeAlut 
# ALUT_INCLUDE_DIR, where to find the headers
#
# $ALUTDIR is an environment variable that would
# correspond to the ./configure --prefix=$ALUTDIR
# used in building FreeAlut.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake module.
# Modified by Guillaume Martres to locate FreeAlut instead of OpenAL 

# For more informations, see FindOpenAL.cmake which is included in cmake 2.6

if (ALUT_LIBRARIES AND ALUT_INCLUDE_DIRS)
  # in cache already
  set(ALUT_FOUND TRUE)
else (ALUT_LIBRARIES AND ALUT_INCLUDE_DIRS)

  FIND_PATH(ALUT_INCLUDE_DIR alut.h
    HINTS
    $ENV{ALUTDIR}
    PATH_SUFFIXES include/AL include/OpenAL include
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
    [HKEY_LOCAL_MACHINE\\SOFTWARE\\Creative\ Labs\\OpenAL\ 1.1\ Software\ Development\ Kit\\1.00.0000;InstallDir]
  )

  FIND_LIBRARY(ALUT_LIBRARY 
    NAMES FreeAlut alut
    HINTS
    $ENV{ALUTDIR}
    PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
    [HKEY_LOCAL_MACHINE\\SOFTWARE\\Creative\ Labs\\OpenAL\ 1.1\ Software\ Development\ Kit\\1.00.0000;InstallDir]
  )

  INCLUDE(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set ALUT_FOUND to TRUE if
  # all listed variables are TRUE
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(FreeAlut DEFAULT_MSG ALUT_LIBRARY ALUT_INCLUDE_DIR)

  # show the ALUT_INCLUDE_DIRS and ALUT_LIBRARIES variables only in the advanced view
  mark_as_advanced(ALUT_INCLUDE_DIRS ALUT_LIBRARIES)

endif (ALUT_LIBRARIES AND ALUT_INCLUDE_DIRS)

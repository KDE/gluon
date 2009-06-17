# - Find the OGG includes and libraries.
# The following variables are set if Ogg is found.  If Ogg is not
# found, OGG_FOUND is set to false.
#  OGG_FOUND        - True when the Ogg include directory is found.
#  OGG_INCLUDE_DIRS - the path to where the Ogg include files are.
#  OGG_LIBRARIES    - The Ogg library.
MESSAGE(STATUS "Looking for Ogg")

FIND_PATH(OGG_INCLUDE_DIRS ogg/ogg.h /usr/include /usr/local/include)
FIND_LIBRARY(OGG_LIBRARIES NAMES ogg PATHS /usr/lib /usr/local/lib)

IF(OGG_INCLUDE_DIRS AND OGG_LIBRARIES)
  SET(OGG_FOUND 1)
  IF(NOT OGG_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for Ogg - found")
  ENDIF(NOT OGG_FIND_QUIETLY)
ELSE(OGG_INCLUDE_DIRS AND OGG_LIBRARIES)
  IF(NOT OGG_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for Ogg - not found")
  ENDIF(NOT OGG_FIND_QUIETLY)
ENDIF(OGG_INCLUDE_DIRS AND OGG_LIBRARIES)

MARK_AS_ADVANCED(OGG_INCLUDE_DIRS OGG_LIBRARIES)

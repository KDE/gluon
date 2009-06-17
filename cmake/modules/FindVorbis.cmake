# - Find the Ogg Vorbis includes and libraries.
# The following variables are set if Ogg Vorbis is found.  If Ogg is
# not found, VORBIS_FOUND is set to false.
#  VORBIS_FOUND        - True when the Ogg Vorbis include directory is
#                       found.
#  VORBIS_INCLUDE_DIRS - the path to where the Ogg Vorbis include files
#                        are.
#  VORBIS_LIBRARIES    - The Ogg library.
#
# Vorbisenc:
#  VORBISENC_FOUND        - True when the Vorbisfile include
#                            directory is found.
#  VORBISENC_INCLUDE_DIRS - the path to where the Vorbisfile include
#                            files are.
#  VORBISENC_LIBRARIES    - The Vorbisfile library.
#
# Vorbisfile:
#  VORBISFILE_FOUND        - True when the Vorbisfile include
#                            directory is found.
#  VORBISFILE_INCLUDE_DIRS - the path to where the Vorbisfile include
#                            files are.
#  VORBISFILE_LIBRARIES    - The Vorbisfile library.
MESSAGE(STATUS "Looking for Ogg Vorbis")

FIND_PATH(VORBIS_INCLUDE_DIRS vorbis/codec.h /usr/include /usr/local/include)
FIND_LIBRARY(VORBIS_LIBRARIES NAMES vorbis PATHS /usr/lib /usr/local/lib)

IF(VORBIS_INCLUDE_DIRS AND VORBIS_LIBRARIES)
  SET(VORBIS_FOUND 1)
  IF(NOT VORBIS_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for Ogg Vorbis - found")
  ENDIF(NOT VORBIS_FIND_QUIETLY)
ELSE(VORBIS_INCLUDE_DIRS AND VORBIS_LIBRARIES)
  IF(NOT VORBIS_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for Ogg Vorbis - not found")
  ENDIF(NOT VORBIS_FIND_QUIETLY)
ENDIF(VORBIS_INCLUDE_DIRS AND VORBIS_LIBRARIES)

# Vorbisenc
MESSAGE(STATUS "Looking for Vorbisenc")

FIND_PATH(VORBISENC_INCLUDE_DIRS vorbis/vorbisenc.h /usr/include /usr/local/include)
FIND_LIBRARY(VORBISENC_LIBRARIES NAMES vorbisenc PATHS /usr/lib /usr/local/lib)

IF(VORBISENC_INCLUDE_DIRS AND VORBISENC_LIBRARIES)
  SET(VORBISENC_FOUND 1)
  IF(NOT VORBISENC_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for Vorbisenc - found")
  ENDIF(NOT VORBISENC_FIND_QUIETLY)
ELSE(VORBISENC_INCLUDE_DIRS AND VORBISENC_LIBRARIES)
  IF(NOT VORBISENC_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for Vorbisenc - not found")
  ENDIF(NOT VORBISENC_FIND_QUIETLY)
ENDIF(VORBISENC_INCLUDE_DIRS AND VORBISENC_LIBRARIES)

# Vorbisfile
FIND_PATH(VORBISFILE_INCLUDE_DIRS vorbis/vorbisfile.h /usr/include /usr/local/include)
FIND_LIBRARY(VORBISFILE_LIBRARIES NAMES vorbisfile PATHS /usr/lib /usr/local/lib)

IF(VORBISFILE_INCLUDE_DIRS AND VORBISFILE_LIBRARIES)
  SET(VORBISFILE_FOUND 1)
  IF(NOT VORBISFILE_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for Vorbisfile - found")
  ENDIF(NOT VORBISFILE_FIND_QUIETLY)
ELSE(VORBISFILE_INCLUDE_DIRS AND VORBISFILE_LIBRARIES)
  IF(NOT VORBISFILE_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for Vorbisfile - not found")
  ENDIF(NOT VORBISFILE_FIND_QUIETLY)
ENDIF(VORBISFILE_INCLUDE_DIRS AND VORBISFILE_LIBRARIES)


MARK_AS_ADVANCED(VORBIS_INCLUDE_DIRS VORBIS_LIBRARIES)
MARK_AS_ADVANCED(VORBISENC_INCLUDE_DIRS VORBISENC_LIBRARIES)
MARK_AS_ADVANCED(VORBISFILE_INCLUDE_DIRS VORBISFILE_LIBRARIES)

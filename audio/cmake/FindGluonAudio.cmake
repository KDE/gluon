# - Try to find Gluon Audio
#
# Once done this will define
#  GLUON_AUDIO_FOUND - system has KAL
#  GLUON_AUDIO_INCLUDES - all include directories required for KAL, use it with KDE4_INCLUDES
#  GLUON_AUDIO_INCLUDE_DIR - the KAL include directory
#  GLUON_AUDIO_LIBRARY - the KAL library
#  GLUON_AUDIO_LIBS - All libraries needed for Gluon Audio functionality
#
# Copyright (C) 2009 Guillaume Martres
# Copyright (C) 2010 Arjen Hiemstra
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (GLUON_AUDIO_LIBRARY AND GLUON_AUDIO_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_AUDIO_FOUND TRUE)
endif (GLUON_AUDIO_LIBRARY AND GLUON_AUDIO_INCLUDE_DIR)

if (GLUON_AUDIO_FIND_REQUIRED)
    set(_gluonAudioReq "REQUIRED")
endif (GLUON_AUDIO_FIND_REQUIRED)

find_package(GluonCore ${_gluonAudioReq})

set(CMAKE_MODULE_PATH ${SHARE_INSTALL_DIR}/gluon/cmake)

find_package(OpenAL ${_gluonAudioReq})
find_package(Alure ${_gluonAudioReq})
find_package(SndFile ${_gluonAudioReq})

find_path(GLUON_AUDIO_INCLUDE_DIR
    NAMES
    gluon/audio/engine.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
    PATH_SUFFIXES
    gluon
)

set(GLUON_AUDIO_INCLUDES
    ${GLUON_CORE_INCLUDES}
    ${GLUON_AUDIO_INCLUDE_DIR}
    ${OPENAL_INCLUDE_DIR}
    ${SNDFILE_INCLUDE_DIR}
    ${OGGVORBIS_INCLUDE_DIR}
    CACHE PATHS "Includes needed for Gluon Audio"
)

find_library(GLUON_AUDIO_LIBRARY
    NAMES
    GluonAudio
    PATHS
    ${LIB_INSTALL_DIR}
)

set(GLUON_AUDIO_LIBS
    ${GLUON_CORE_LIBS}
    ${OPENAL_LIBRARY}
    ${SNDFILE_LIBRARY}
    ${OGGVORBIS_LIBRARY}
    ${GLUON_AUDIO_LIBRARY}
    CACHE PATHS "Libraries needed for Gluon Audio"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonAudio DEFAULT_MSG GLUON_AUDIO_LIBRARY GLUON_AUDIO_INCLUDE_DIR)

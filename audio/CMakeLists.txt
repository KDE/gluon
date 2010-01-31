cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonAudio)
    find_package(GluonCore REQUIRED)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenAL REQUIRED)
find_package(SndFile REQUIRED)
find_package(OggVorbis REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}

    ${GLUON_CORE_INCLUDES}

    ${OPENAL_INCLUDE_DIR}
    #TODO: Make use of phonon instead of these libs for file input. Saves us another few dependencies.
    ${SNDFILE_INCLUDE_DIR}
    ${OGG_INCLUDE_DIR}
    ${VORBISFILE_INCLUDE_DIR}
)

set(GLUON_AUDIO_INCLUDES
    ${GLUON_CORE_INCLUDES}

    ${OPENAL_INCLUDE_DIR}
    ${SNDFILE_INCLUDE_DIR}
    ${OGG_INCLUDE_DIR}
    ${VORBISFILE_INCLUDE_DIR}
    CACHE PATHS "Includes required for Gluon Audio"
)

set(GluonAudio_SRCS
    engine.cpp
    soundreader.cpp
    music.cpp
    capture.cpp
    buffer.cpp
    sound.cpp

    capturedevice_p.cpp
    device_p.cpp
)

qt4_automoc(${GluonAudio_SRCS})
add_library(GluonAudio SHARED ${GluonAudio_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(GluonAudio GluonCore)
endif()

target_link_libraries(
    GluonAudio
    ${GLUON_CORE_LIBS}
    ${OPENAL_LIBRARY}
    ${SNDFILE_LIBRARY}
    ${OGG_LIBRARY}
    ${VORBISFILE_LIBRARY}
)

set(GLUON_AUDIO_LIBS
    GluonAudio
    ${GLUON_CORE_LIBS}
    ${OPENAL_LIBRARY}
    ${SNDFILE_LIBRARY}
    ${OGG_LIBRARY}
    ${VORBISFILE_LIBRARY}
    CACHE PATHS "Libraries required for Gluon audio"
)

set_target_properties(GluonAudio PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})

install(TARGETS GluonAudio DESTINATION ${LIB_INSTALL_DIR})

install(
    FILES
    buffer.h
    engine.h
    soundreader.h
    sound.h
    music.h
    capture.h
    gluon_audio_export.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/audio
    COMPONENT Devel
)

install(
    FILES
    cmake/FindGluonAudio.cmake
    cmake/FindOggVorbis.cmake
    cmake/FindSndFile.cmake
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/cmake
    COMPONENT Devel
)

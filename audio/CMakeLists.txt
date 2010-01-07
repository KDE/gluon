cmake_minimum_required(VERSION 2.6)

find_package(OpenAL REQUIRED)
find_package(SndFile REQUIRED)
find_package(OggVorbis REQUIRED)

include_directories(${OPENAL_INCLUDE_DIR}
		    ${SNDFILE_INCLUDE_DIR}
                    ${OGG_INCLUDE_DIR}
                    ${VORBISFILE_INCLUDE_DIR})

include_directories(./)

set(GluonAudio_SRCS
    engine.cpp
    phonon.cpp
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

set_target_properties(GluonAudio PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})

target_link_libraries(GluonAudio
                      ${OPENAL_LIBRARY}
                      ${SNDFILE_LIBRARY}
                      ${OGG_LIBRARY}
                      ${VORBISFILE_LIBRARY}
		      ${PHONON_LIBRARY}
		      ${QT_QTCORE_LIBRARY}
)

install(TARGETS GluonAudio DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

install(FILES
  buffer.h
  engine.h
  soundreader.h
  phonon.h
  sound.h
  music.h
  capture.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/audio COMPONENT Devel)

cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonAudio)
    find_package(GluonCore REQUIRED)
    include_directories(${GLUON_CORE_INCLUDES})
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenAL REQUIRED)
find_package(SndFile REQUIRED)
find_package(OggVorbis REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${OPENAL_INCLUDE_DIR}
                    ${SNDFILE_INCLUDE_DIR}
                    ${OGG_INCLUDE_DIR}
                    ${VORBISFILE_INCLUDE_DIR}
                    )


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

if(GLUON_BUILD_ALL)
    add_dependencies(GluonAudio GluonCore)
    target_link_libraries(GluonAudio GluonCore)
else(GLUON_BUILD_ALL)
    target_link_libraries(GluonAudio ${GLUON_CORE_LIBRARY})
endif()

target_link_libraries(
                GluonAudio
                ${OPENAL_LIBRARY}
                ${SNDFILE_LIBRARY}
                ${OGG_LIBRARY}
                ${VORBISFILE_LIBRARY}
                ${PHONON_LIBRARY}
                ${QT_QTCORE_LIBRARY}
)

set_target_properties(GluonAudio PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})

install(TARGETS GluonAudio DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

install(
    FILES
    buffer.h
    engine.h
    soundreader.h
    phonon.h
    sound.h
    music.h
    capture.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/audio
    COMPONENT Devel
)

install(
    FILES
    cmake/FindGluonAudio.cmake
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/gluon/cmake
    COMPONENT Devel
)

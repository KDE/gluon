cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonAudio)
    find_package(GluonCore REQUIRED)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenAL 1.8 REQUIRED)
find_package(SndFile REQUIRED)
find_package(Alure 1.1 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}

    ${GLUON_CORE_INCLUDES}

    ${ALURE_INCLUDE_DIRS}
    ${OPENAL_INCLUDE_DIR}
    #TODO: Make use of phonon instead of these libs for file input. Saves us another few dependencies.
    ${SNDFILE_INCLUDE_DIR}
)

set(GLUON_AUDIO_INCLUDES
    ${GLUON_CORE_INCLUDES}

    ${ALURE_INCLUDE_DIRS}
    ${OPENAL_INCLUDE_DIR}
    ${SNDFILE_INCLUDE_DIR}
    CACHE INTERNAL "Includes required for Gluon Audio"
)

set(GluonAudio_SRCS
    engine.cpp
    capture.cpp
    sound.cpp
    player.cpp

    capturedevice_p.cpp
    device_p.cpp
)

set(GluonAudio_HEADERS
    engine.h
    sound.h
    player.h
    capture.h
    gluon_audio_export.h
)

qt4_automoc(${GluonAudio_SRCS})

if(APPLE)
    add_library(GluonAudio SHARED ${GluonAudio_SRCS} ${GluonAudio_HEADERS})
else()
    add_library(GluonAudio SHARED ${GluonAudio_SRCS})
endif()

if(GLUON_BUILD_ALL)
    add_dependencies(GluonAudio GluonCore)
endif()

target_link_libraries(
    GluonAudio
    ${GLUON_CORE_LIBS}
    ${OPENAL_LIBRARY}
    ${SNDFILE_LIBRARIES}
    ${ALURE_LIBRARIES}
)

set(GLUON_AUDIO_LIBS
    GluonAudio
    ${GLUON_CORE_LIBS}
    ${OPENAL_LIBRARY}
    ${SNDFILE_LIBRARIES}
    ${ALURE_LIBRARIES}
    CACHE INTERNAL "Libraries required for Gluon audio"
)

set_target_properties(GluonAudio PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_AUDIO_LIB)

if(APPLE)
    #hack for being able to set headers as public in a osx framework
    list(APPEND GluonAudio_HEADERS
        ${GluonAudio_HEADERS}
    )

    set_target_properties(GluonAudio PROPERTIES FRAMEWORK TRUE)
    set_target_properties(GluonAudio PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
    set_target_properties(GluonAudio PROPERTIES PUBLIC_HEADER "${GluonAudio_HEADERS}")

    set(MACOSX_FRAMEWORK_IDENTIFIER audio)
    set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endif()

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif()

install(
    TARGETS GluonAudio
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    FRAMEWORK DESTINATION ${LIB_INSTALL_DIR}
)

install(
    FILES
    ${GluonAudio_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/audio
    COMPONENT Devel
)

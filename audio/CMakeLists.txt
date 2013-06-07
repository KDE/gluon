set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenAL 1.8 REQUIRED)
find_package(Alure 1.2 REQUIRED)

gluon_include_directories(GluonAudio
    ${GLUONCORE_INCLUDE_DIRS}

    ${ALURE_INCLUDE_DIRS}
    ${OPENAL_INCLUDE_DIR}
    #TODO: Make use of phonon instead of these libs for file input. Saves us another few dependencies.
)

if( BUILD_EXAMPLES )
    add_subdirectory(examples)
endif()

set(GluonAudio_SRCS
    #capture.cpp
    engine.cpp
    player.cpp
    sound.cpp

    #capturedevice_p.cpp
    device_p.cpp
)

set(GluonAudio_HEADERS
    #capture.h
    engine.h
    gluon_audio_export.h
    player.h
    sound.h
)

gluon_add_library(GluonAudio SHARED
    SOURCES ${GluonAudio_SRCS}
    HEADERS ${GluonAudio_HEADERS}
    LIBRARIES ${GLUONCORE_LIBRARIES} ${OPENAL_LIBRARY} ${ALURE_LIBRARIES}
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

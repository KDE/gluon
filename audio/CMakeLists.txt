option(BUILD_GLUONAUDIO "Build GluonAudio Library" ON)
if( NOT BUILD_GLUONAUDIO )
    return()
endif( NOT BUILD_GLUONAUDIO )

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenAL 1.8 REQUIRED)
find_package(Alure 1.2 REQUIRED)

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

gluon_include_directories(${GLUONCORE_INCLUDES} ${ALURE_INCLUDE_DIRS} ${OPENAL_INCLUDE_DIR})
gluon_add_library(GluonAudio SHARED ${GluonAudio_SRCS} ${GluonAudio_HEADERS})
gluon_target_link_libraries(GluonAudio ${GLUONCORE_LIBS} ${OPENAL_LIBRARY} ${ALURE_LIBRARIES})
gluon_setup_framework(GluonAudio ${GluonAudio_HEADERS})

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif()

install(
    TARGETS     GluonAudio
    RUNTIME     DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluonaudio
    LIBRARY     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonaudio
    ARCHIVE     DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonaudio
    FRAMEWORK   DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluonaudio
)

install(
    FILES
    ${GluonAudio_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/audio
    COMPONENT gluonaudio
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()


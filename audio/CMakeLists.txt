set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

find_package( OpenAL 1.8 REQUIRED )
find_package( Alure 1.2 REQUIRED )

set( GluonAudio_SRCS
    engine.cpp
    player.cpp
    sound.cpp
    device_p.cpp
)

set( GluonAudio_HEADERS
    engine.h
    gluon_audio_export.h
    player.h
    sound.h
)

gluon_add_library( Gluon::Audio SHARED
    SOURCES ${GluonAudio_SRCS}
    HEADERS ${GluonAudio_HEADERS}
    INCLUDES ${ALURE_INCLUDE_DIRS} ${OPENAL_INCLUDE_DIR}
    LIBRARIES Gluon::Core ${OPENAL_LIBRARY} ${ALURE_LIBRARIES}
)

gluon_add_subdirectories( examples tests )


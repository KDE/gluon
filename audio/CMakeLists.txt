set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

find_package( OpenAL 1.8 REQUIRED )

set( GluonAudio_SRCS
    source.cpp
    channel.cpp
    listener.cpp
    decoderplugin.cpp
)

set( GluonAudio_HEADERS
    source.h
    channel.h
    listener.h
    decoder.h
    decoderplugin.h
)

gluon_add_library( Gluon::Audio SHARED
    SOURCES ${GluonAudio_SRCS}
    HEADERS ${GluonAudio_HEADERS}
    INCLUDES ${OPENAL_INCLUDE_DIR}
    LIBRARIES Gluon::Core ${OPENAL_LIBRARY}
)

add_subdirectory( plugins/decoder )

#gluon_add_subdirectories( examples tests )


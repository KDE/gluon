cmake_minimum_required(VERSION 2.6)
project(gluonexamples_audio_playlist)

find_package(GluonAudio REQUIRED)

include_directories(${GLUON_AUDIO_INCLUDES})

set(gluonexamples_audio_playlist_SRCS
    main.cpp
)

add_executable(gluonexamples_audio_playlist ${gluonexamples_audio_playlist_SRCS})
target_link_libraries(gluonexamples_audio_playlist ${GLUON_AUDIO_LIBS})

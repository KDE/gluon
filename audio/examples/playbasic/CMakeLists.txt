cmake_minimum_required(VERSION 2.6)
project(gluonexamples_audio_playbasic)

find_package(GluonCore REQUIRED)
find_package(GluonAudio REQUIRED)

include_directories(${GLUON_CORE_INCLUDES} ${GLUON_AUDIO_INCLUDES})

set(gluonexamples_audio_playbasic_SRCS
    main.cpp
)

add_executable(gluonexamples_audio_playbasic ${gluonexamples_audio_playbasic_SRCS})
target_link_libraries(gluonexamples_audio_playbasic ${GLUON_AUDIO_LIBS})

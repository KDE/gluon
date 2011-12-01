cmake_minimum_required(VERSION 2.8)

project(gluonexamples_audio_playbasic)

include_directories(${GLUON_CORE_INCLUDE_DIRS} ${GLUON_AUDIO_INCLUDE_DIRS})

set(gluonexamples_audio_playbasic_SRCS
    main.cpp
)

add_executable(gluonexamples_audio_playbasic ${gluonexamples_audio_playbasic_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_audio_playbasic GluonAudio)
endif()

target_link_libraries(gluonexamples_audio_playbasic ${GLUON_AUDIO_LIBS})

install(TARGETS gluonexamples_audio_playbasic DESTINATION ${EXAMPLES_INSTALL_DIR})

project(gluonexamples_audio_play3d)

cmake_minimum_required(VERSION 2.6)

include_directories(${GLUON_AUDIO_INCLUDES})

set(gluonexamples_audio_play3d_SRCS
    main.cpp
)

add_executable(gluonexamples_audio_play3d ${gluonexamples_audio_play3d_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_audio_play3d GluonAudio)
endif()

target_link_libraries(gluonexamples_audio_play3d ${GLUON_AUDIO_LIBS})

set(GluonAudio_SOUNDS
    Front_Center.wav
    Front_Left.wav
    Front_Right.wav
)

install(
    FILES
    ${GluonAudio_SOUNDS}
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/audio/sounds
    COMPONENT Devel
)

install(TARGETS gluonexamples_audio_play3d DESTINATION ${EXAMPLES_INSTALL_DIR})

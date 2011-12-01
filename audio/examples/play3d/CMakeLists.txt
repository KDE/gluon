cmake_minimum_required(VERSION 2.8)

project(gluonexamples_audio_play3d)

include_directories(${GLUON_AUDIO_INCLUDE_DIRS})

set(gluonexamples_audio_play3d_SRCS
    main.cpp
)

add_executable(gluonexamples_audio_play3d ${gluonexamples_audio_play3d_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_audio_play3d GluonAudio)
endif()

target_link_libraries(gluonexamples_audio_play3d ${GLUON_AUDIO_LIBS})

install(FILES
    Front_Center.wav
    Front_Left.wav
    Front_Right.wav
    DESTINATION ${EXAMPLES_DATA_INSTALL_DIR}
    COMPONENT Devel
)

install(TARGETS gluonexamples_audio_play3d DESTINATION ${EXAMPLES_INSTALL_DIR})

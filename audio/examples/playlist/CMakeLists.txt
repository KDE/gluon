include_directories(${GLUON_AUDIO_INCLUDE_DIRS})

set(gluonexamples_audio_playlist_SRCS
    main.cpp
)

add_executable(gluonexamples_audio_playlist ${gluonexamples_audio_playlist_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluonexamples_audio_playlist GluonAudio)
endif()

target_link_libraries(gluonexamples_audio_playlist ${GLUON_AUDIO_LIBS})

install(TARGETS gluonexamples_audio_playlist DESTINATION ${EXAMPLES_INSTALL_DIR})

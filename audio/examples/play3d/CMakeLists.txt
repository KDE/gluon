include_directories(${GLUONAUDIO_INCLUDES})

set(gluonexamples_audio_play3d_SRCS
    main.cpp
)

gluon_add_executable(gluonexamples_audio_play3d
    SOURCES main.cpp
    LIBRARIES ${GLUONAUDIO_LIBRARIES}
)

install(FILES
    Front_Center.wav
    Front_Left.wav
    Front_Right.wav
    DESTINATION ${EXAMPLE_DATA_INSTALL_DIR}/audio
    COMPONENT Devel
)

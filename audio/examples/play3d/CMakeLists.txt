gluon_add_executable(gluonexamples_audio_play3d
    SOURCES main.cpp
    LIBRARIES Gluon::Audio
)

install(FILES
    Front_Center.wav
    Front_Left.wav
    Front_Right.wav
    DESTINATION ${EXAMPLE_DATA_INSTALL_DIR}/audio
    COMPONENT Devel
)

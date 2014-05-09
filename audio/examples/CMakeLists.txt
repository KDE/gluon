include_directories(${GLUON_AUDIO_INCLUDE_DIRS})

set(EXAMPLES_INSTALL_DIR ${BIN_INSTALL_DIR})
set(AUDIO_EXAMPLES_DATA_INSTALL_DIR ${DATA_INSTALL_DIR}/examples/audio)

add_subdirectory(play3d)
add_subdirectory(playbasic)
add_subdirectory(playlist)

include_directories(${GLUONAUDIO_INCLUDES})

set(EXAMPLES_INSTALL_DIR ${BIN_INSTALL_DIR})
set(EXAMPLES_DATA_INSTALL_DIR ${SHARE_INSTALL_DIR}/gluon/examples/audio)

add_subdirectory(play3d)
add_subdirectory(playbasic)
add_subdirectory(playlist)

include_directories(${GLUON_INPUT_INCLUDE_DIRS})

set(EXAMPLES_INSTALL_DIR ${BIN_INSTALL_DIR})

add_subdirectory(devicesloop)
add_subdirectory(keyboardloop)
add_subdirectory(listdevices)
add_subdirectory(qteventfilter)

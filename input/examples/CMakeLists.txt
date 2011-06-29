if(NOT GLUON_BUILD_ALL)
    find_package(GluonInput REQUIRED)
endif()

include_directories(${GLUON_INPUT_INCLUDES})

set(EXAMPLES_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)

add_subdirectory(devicesloop)
add_subdirectory(keyboardloop)
add_subdirectory(listdevices)
add_subdirectory(qteventfilter)

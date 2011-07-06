if(NOT GLUON_BUILD_ALL)
    find_package(GluonAudio REQUIRED)
endif()

include_directories(${GLUON_AUDIO_INCLUDES})

set(EXAMPLES_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)

add_subdirectory(play3d)
add_subdirectory(playbasic)
add_subdirectory(playlist)

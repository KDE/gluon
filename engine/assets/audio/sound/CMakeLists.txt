cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonAudio REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_AUDIO_INCLUDES})

set(soundasset_SRCS
    soundasset.cpp
)

qt4_automoc(${soundasset_SRCS})
add_library(gluon_asset_sound SHARED ${soundasset_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_asset_sound GluonEngine GluonAudio)
endif()

set_target_properties(gluon_asset_sound PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_ASSET_SOUND_LIB)
target_link_libraries(gluon_asset_sound GluonEngine ${GLUON_AUDIO_LIBS})

install(
    TARGETS
    gluon_asset_sound
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

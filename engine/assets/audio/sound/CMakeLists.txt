include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLUONAUDIO_INCLUDES})

set(soundasset_SRCS
    soundasset.cpp
)

gluon_add_plugin(gluon_asset_sound ${soundasset_SRCS})
target_link_libraries(gluon_asset_sound GluonEngine ${GLUONAUDIO_LIBS})

install(
    TARGETS
    gluon_asset_sound
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)

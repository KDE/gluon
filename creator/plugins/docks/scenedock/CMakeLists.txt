set(scenedock_SRCS
    scenedock.cpp
    scenedockplugin.cpp
)

kde4_add_plugin(gluon_creator_dockplugin_scenedock ${scenedock_SRCS})
target_link_libraries(gluon_creator_dockplugin_scenedock ${GLUON_CREATOR_LIBS})

install(TARGETS gluon_creator_dockplugin_scenedock DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_dockplugin_scenedock.desktop DESTINATION ${SERVICES_INSTALL_DIR})

set(messagedock_SRCS
    messagedock.cpp
    messagedockplugin.cpp
)

kde4_add_plugin(gluon_creator_dockplugin_messagedock ${messagedock_SRCS})
target_link_libraries(gluon_creator_dockplugin_messagedock ${GLUON_CREATOR_LIBS})

install(TARGETS gluon_creator_dockplugin_messagedock DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_dockplugin_messagedock.desktop DESTINATION ${SERVICES_INSTALL_DIR})

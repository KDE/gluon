gluon_add_plugin(gluoncreator_dockplugin_messagedock GluonCreator
    SOURCES messagedock.cpp messagedockplugin.cpp
    LIBRARIES ${GLUONCREATOR_LIBRARIES}
    DESTINATION ${KDE4_PLUGIN_INSTALL_DIR}
)

install(FILES gluoncreator_dockplugin_messagedock.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

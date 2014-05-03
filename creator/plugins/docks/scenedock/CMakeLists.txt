gluon_add_plugin( gluoncreator_dockplugin_scenedock GluonCreator
    SOURCES scenedock.cpp scenedockplugin.cpp
    LIBRARIES ${GLUONCREATOR_LIBRARIES}
    DESTINATION ${KDE4_PLUGIN_INSTALL_DIR}
)

install( FILES gluoncreator_dockplugin_scenedock.desktop
    DESTINATION ${SERVICES_INSTALL_DIR}
    COMPONENT gluoncreator
)

gluon_add_plugin(gluoncreator_dockplugin_componentsdock GluonCreator
    SOURCES componentsdock.cpp componentsdockplugin.cpp
    LIBRARIES ${GLUONCREATOR_LIBRARIES}
    DESTINATION ${KDE4_PLUGIN_INSTALL_DIR}
)

install(FILES gluoncreator_dockplugin_componentsdock.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

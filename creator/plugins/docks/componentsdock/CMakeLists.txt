gluon_add_plugin(gluoncreator_dockplugin_componentsdock 
    MODULE Gluon::Creator
    SOURCES componentsdock.cpp componentsdockplugin.cpp
    LIBRARIES Gluon::Creator
)

install(FILES gluoncreator_dockplugin_componentsdock.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

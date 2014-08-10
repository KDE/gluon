gluon_add_plugin(gluoncreator_dockplugin_projectdock 
    MODULE Gluon::Creator
    SOURCES projectdock.cpp projectdockplugin.cpp
    LIBRARIES Gluon::Creator
)

install(FILES gluoncreator_dockplugin_projectdock.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

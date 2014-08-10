gluon_add_plugin( gluoncreator_dockplugin_scenedock 
    MODULE Gluon::Creator
    SOURCES scenedock.cpp scenedockplugin.cpp
    LIBRARIES Gluon::Creator
)

install( FILES gluoncreator_dockplugin_scenedock.desktop
    DESTINATION ${SERVICES_INSTALL_DIR}
    COMPONENT gluoncreator
)

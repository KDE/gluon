gluon_add_plugin(gluon_viewer_part 
    MODULE Gluon::Creator
    SOURCES gluonviewerpart.cpp
    LIBRARIES Gluon::Engine KF5::Parts #Gluon::Graphics Gluon::Input
)

install(FILES gluon_viewer_part.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluonviewerpartui.rc
        DESTINATION ${SHARE_INSTALL_DIR}/apps/gluonviewerpart
        COMPONENT gluoncreator)

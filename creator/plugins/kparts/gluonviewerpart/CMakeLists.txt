gluon_add_plugin(gluon_viewer_part 
    MODULE Gluon::Creator
    SOURCES gluonviewerpart.cpp
    LIBRARIES Gluon::Graphics Gluon::Input Gluon::Engine KF5::Parts
    DESTINATION ${LIB_INSTALL_DIR}/qt/plugins
)

kservice_desktop_to_json( gluon_viewer_part gluon_viewer_part.desktop )

install(FILES gluon_viewer_part.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluonviewerpartui.rc
        DESTINATION ${XMLGUI_INSTALL_DIR}
        COMPONENT gluoncreator)

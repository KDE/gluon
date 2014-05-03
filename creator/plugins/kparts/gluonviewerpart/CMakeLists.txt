gluon_add_plugin(gluon_viewer_part GluonCreator
    SOURCES gluonviewerpart.cpp
    LIBRARIES ${GLUONENGINE_LIBRARIES} ${GLUONGRAPHICS_LIBRARIES} ${GLUONINPUT_LIBRARIES} ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS}
    DESTINATION ${KDE4_PLUGIN_INSTALL_DIR}
)

install(FILES gluon_viewer_part.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluonviewerpartui.rc
        DESTINATION ${SHARE_INSTALL_DIR}/apps/gluonviewerpart
        COMPONENT gluoncreator)

set(projectinspector_SRCS
    propertylist.cpp
    projectinspectorwindow.cpp
    projectinspectorplugin.cpp
    qobjecttreemodel.cpp
)

gluon_add_plugin(gluoncreator_toolplugin_projectinspector GluonCreator
    SOURCES ${projectinspector_SRCS}
    LIBRARIES ${GLUONCREATOR_LIBRARIES}
    DESTINATION ${KDE4_PLUGIN_INSTALL_DIR}
)

install(FILES gluoncreator_toolplugin_projectinspector.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluoncreator_toolplugin_projectinspectorui.rc
        DESTINATION ${SHARE_INSTALL_DIR}/apps/gluoncreator
        COMPONENT gluoncreator
)

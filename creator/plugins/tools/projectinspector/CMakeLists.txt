set(projectinspector_SRCS
    propertylist.cpp
    projectinspectorwindow.cpp
    projectinspectorplugin.cpp
    qobjecttreemodel.cpp
)

gluon_add_plugin(gluoncreator_toolplugin_projectinspector 
    MODULE Gluon::Creator
    SOURCES ${projectinspector_SRCS}
    LIBRARIES Gluon::Creator
)

install(FILES gluoncreator_toolplugin_projectinspector.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluoncreator_toolplugin_projectinspectorui.rc
        DESTINATION ${SHARE_INSTALL_DIR}/apps/gluoncreator
        COMPONENT gluoncreator
)

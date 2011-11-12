set(projectinspector_SRCS
    propertylist.cpp
    projectinspectorwindow.cpp
    projectinspectorplugin.cpp
    qobjecttreemodel.cpp
)

kde4_add_plugin(gluon_creator_toolplugin_projectinspector ${projectinspector_SRCS})
target_link_libraries(gluon_creator_toolplugin_projectinspector ${GLUON_CREATOR_LIBS})

install(TARGETS gluon_creator_toolplugin_projectinspector
        DESTINATION ${PLUGIN_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluon_creator_toolplugin_projectinspector.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluon_creator_toolplugin_projectinspectorui.rc
        DESTINATION ${DATA_INSTALL_DIR}/gluoncreator
        COMPONENT gluoncreator
)
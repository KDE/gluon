set(tagmanager_SRCS
    tagmanagerplugin.cpp
    tagmanagerwindow.cpp
)

kde4_add_plugin(gluon_creator_toolplugin_tagmanager ${tagmanager_SRCS})
target_link_libraries(gluon_creator_toolplugin_tagmanager ${GLUON_CREATOR_LIBS})

install(TARGETS gluon_creator_toolplugin_tagmanager
        DESTINATION ${PLUGIN_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluon_creator_toolplugin_tagmanager.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
        COMPONENT gluoncreator)

install(FILES gluon_creator_tagmanagerui.rc
        DESTINATION ${DATA_INSTALL_DIR}/gluoncreator
        COMPONENT gluoncreator
)
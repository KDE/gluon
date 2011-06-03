set(sceneview_SRCS
    scenedock.cpp
    sceneviewplugin.cpp
)

kde4_add_plugin(gluon_creator_viewplugin_sceneview ${sceneview_SRCS})
target_link_libraries(gluon_creator_viewplugin_sceneview ${KDE4_KTEXTEDITOR_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KNEWSTUFF3_LIBS} ${GLUON_CREATOR_LIBS} kdevplatformlanguage kdevplatforminterfaces)

install(TARGETS gluon_creator_viewplugin_sceneview DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_viewplugin_sceneview.desktop DESTINATION ${SERVICES_INSTALL_DIR})

set(projectview_SRCS
    projectview.cpp
    vcslogwidget.cpp
    projectviewplugin.cpp
)

kde4_add_plugin(gluon_creator_viewplugin_projectview ${projectview_SRCS})
target_link_libraries(gluon_creator_viewplugin_projectview ${KDE4_KTEXTEDITOR_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KNEWSTUFF3_LIBS} ${GLUON_CREATOR_LIBS} ${KDEVPLATFORM_LANGUAGE_LIBRARIES} ${KDEVPLATFORM_INTERFACE_LIBRARIES} ${KDEVPLATFORM_VCS_LIBRARIES} ${KDEVPLATFORM_SHELL_LIBRARIES})

install(TARGETS gluon_creator_viewplugin_projectview DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_viewplugin_projectview.desktop DESTINATION ${SERVICES_INSTALL_DIR})

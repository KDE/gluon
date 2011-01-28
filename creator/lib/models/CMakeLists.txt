set(projectdock_SRCS
    projectdock.cpp
    projectdockplugin.cpp
)

kde4_add_plugin(gluon_creator_dockplugin_projectdock ${projectdock_SRCS})
target_link_libraries(gluon_creator_dockplugin_projectdock ${GLUON_CREATOR_LIBS})

install(TARGETS gluon_creator_dockplugin_projectdock DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_dockplugin_projectdock.desktop DESTINATION ${SERVICES_INSTALL_DIR})

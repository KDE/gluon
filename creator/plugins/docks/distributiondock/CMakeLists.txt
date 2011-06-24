set(distributiondock_SRCS
    distributiondock.cpp
    distributiondockplugin.cpp
)

kde4_add_ui_files(
    distributiondock_SRCS
    distributiondock.ui
)

kde4_add_plugin(gluon_creator_dockplugin_distributiondock ${distributiondock_SRCS})

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(gluon_creator_dockplugin_distributiondock ${GLUON_CREATOR_LIBS})

install(TARGETS gluon_creator_dockplugin_distributiondock DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_dockplugin_distributiondock.desktop DESTINATION ${SERVICES_INSTALL_DIR})

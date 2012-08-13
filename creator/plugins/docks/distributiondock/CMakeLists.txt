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
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_PLAYER_INCLUDE_DIRS}
)

target_link_libraries(gluon_creator_dockplugin_distributiondock ${GLUON_CREATOR_LIBS} ${GLUON_PLAYER_LIBS} ${QT_QTWEBKIT_LIBRARY})

install(TARGETS gluon_creator_dockplugin_distributiondock DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_dockplugin_distributiondock.desktop DESTINATION ${SERVICES_INSTALL_DIR})

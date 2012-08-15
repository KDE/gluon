set(distributionwizard_SRCS
	distributionwizard.cpp
)


kde4_add_ui_files(
    distributionwizard_SRCS
    distributionwizard.ui
)

kde4_add_plugin(gluon_creator_dockplugin_distributionwizard ${distributionwizard_SRCS})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_PLAYER_INCLUDE_DIRS}
)

install(TARGETS gluon_creator_dockplugin_distributionwizard
        DESTINATION ${PLUGIN_INSTALL_DIR}
        )
target_link_libraries(gluon_creator_dockplugin_distributionwizard  ${GLUON_CREATOR_LIBS} ${GLUON_PLAYER_LIBS})

install(FILES gluon_creator_dockplugin_distributionwizard.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}
       )

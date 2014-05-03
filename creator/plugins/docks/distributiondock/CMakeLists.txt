set(distributiondock_SRCS
    distributiondock.cpp
    distributiondockplugin.cpp
)

kde4_add_ui_files(
    distributiondock_SRCS
    distributiondock.ui
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

gluon_add_plugin(gluoncreator_dockplugin_distributiondock GluonCreator
    SOURCES ${distributiondock_SRCS}
    LIBRARIES ${GLUONCREATOR_LIBRARIES}
    DESTINATION ${KDE4_PLUGIN_INSTALL_DIR}
)

install(FILES gluoncreator_dockplugin_distributiondock.desktop DESTINATION ${SERVICES_INSTALL_DIR})

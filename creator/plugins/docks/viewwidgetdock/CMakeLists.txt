if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${GLUON_GRAPHICS_INCLUDES})

set(viewwidgetdock_SRCS
    viewwidgetdock.cpp
    viewwidgetdockplugin.cpp
)

kde4_add_plugin(gluon_creator_dockplugin_viewwidgetdock ${viewwidgetdock_SRCS})
target_link_libraries(gluon_creator_dockplugin_viewwidgetdock ${GLUON_CREATOR_LIBS} ${GLUON_GRAPHICS_LIBS})

install(TARGETS gluon_creator_dockplugin_viewwidgetdock DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_dockplugin_viewwidgetdock.desktop DESTINATION ${SERVICES_INSTALL_DIR})
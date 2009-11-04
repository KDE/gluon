cmake_minimum_required(VERSION 2.6)
project(gluon_creator_dockplugin_scenedock)

find_package(KDE4 REQUIRED)
find_package(GluonCreator REQUIRED)

include_directories(${GLUON_CREATOR_INCLUDES})

set(scenedock_SRCS
    scenedockplugin.cpp
    scenemodel.cpp
)

kde4_add_plugin(gluon_creator_dockplugin_scenedock ${scenedock_SRCS})
target_link_libraries(gluon_creator_dockplugin_scenedock ${GLUON_CREATOR_LIBS})

install(TARGETS gluon_creator_dockplugin_scenedock DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES gluon_creator_dockplugin_scenedock.desktop DESTINATION ${SERVICES_INSTALL_DIR})

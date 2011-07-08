cmake_minimum_required(VERSION 2.8)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_GRAPHICS_INCLUDES}
    ${GLUON_INPUT_INCLUDES}
)

set(gluonplasmaapplet_SRCS
    gamedetailsoverlay.cpp
    gamesoverlay.cpp
    glfboapplet.cpp
    loginform.cpp
    overlay.cpp
    plasmaapplet.cpp

    views/achievementsview.cpp
    views/commentsviewitem.cpp
    views/commentsview.cpp
    views/highscoresview.cpp
    views/highscoresviewitem.cpp
    views/newcommentform.cpp
    views/gamesviewitem.cpp
    views/gamesview.cpp
    views/abstractitemview.cpp
)

kde4_add_plugin(plasma_applet_gluonplayer ${gluonplasmaapplet_SRCS})

target_link_libraries(plasma_applet_gluonplayer ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS} ${GLUON_INPUT_LIBS} ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_PLAYER_LIBS})

install(TARGETS plasma_applet_gluonplayer
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-applet-gluonplayer.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

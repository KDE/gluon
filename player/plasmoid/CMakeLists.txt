cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonPlasmaApplet)
    find_package(GluonCore REQUIRED)
    find_package(GluonEngine REQUIRED)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${GLUON_ENGINE_INCLUDES} ${GLUON_GRAPHICS_INCLUDES} 
                    ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
                    ${KDE4_INCLUDES})

set(gluonplasmaapplet_SRCS
    plasmaapplet.cpp
)

kde4_add_plugin(plasma_applet_gluonplayer ${gluonplasmaapplet_SRCS})

target_link_libraries(plasma_applet_gluonplayer ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS}
                        ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS})

install(TARGETS plasma_applet_gluonplayer
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-applet-gluonplayer.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

cmake_minimum_required(VERSION 2.6)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(gluonplayerimports_SRCS
    gluonplayerimportsplugin.cpp
)

INCLUDE_DIRECTORIES(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${KDE4_INCLUDES}
)

qt4_automoc(${gluonplayerimports_SRCS})

add_library(gluonplayerimportsplugin SHARED ${gluonplayerimports_SRCS})
target_link_libraries(gluonplayerimportsplugin
                        ${KDE4_PLASMA_LIBS}
                        ${QT_QTSCRIPT_LIBRARY}
                        ${QT_QTDECLARATIVE_LIBRARY}
                        ${GLUON_PLAYER_LIBS})

install(TARGETS gluonplayerimportsplugin DESTINATION ${IMPORTS_INSTALL_DIR}/org/gamingfreedom/gluon/gluonplayerimports)
install(FILES qmldir DESTINATION ${IMPORTS_INSTALL_DIR}/org/gamingfreedom/gluon/gluonplayerimports)


include_directories(
    ${KDE4_INCLUDES}
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLUON_INPUT_INCLUDE_DIRS}
    ${ACTIVEAPP_INCLUDE_DIR}
)

set(gluonplayer-active_SRCS
    main.cpp
    mainwindow.cpp
)

KDE4_ADD_EXECUTABLE(gluonplayer-active ${gluonplayer-active_SRCS})

target_link_libraries(gluonplayer-active
    ${QT_QTDECLARATIVE_LIBRARY}
    ${QT_QTOPENGL_LIBRARY}
    ${QT_QTSCRIPT_LIBRARY}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KIO_LIBS}
    ${KDE4_PLASMA_LIBS}
    kdeclarative
    ${GLUON_PLAYER_LIBS}
    ${GLUON_ENGINE_LIBS}
    ${GLUON_GRAPHICS_LIBS}
    ${GLUON_INPUT_LIBS}
    ${ACTIVEAPP_LIBRARIES}
)

install(TARGETS gluonplayer-active ${INSTALL_TARGETS_DEFAULT_ARGS} )

cmake_minimum_required(VERSION 2.6)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDES}
)

set(QMLPLAYER_SRCS
    main.cpp
)

qt4_automoc(${QMLPLAYER_SRCS})

add_executable(gluon_qmlplayer ${QMLPLAYER_SRCS})
target_link_libraries(gluon_qmlplayer ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS} ${GLUON_PLAYER_LIBS} ${QT_QTDECLARATIVE_LIBRARY})

set(GLUON_DECLARATIVE_LIBS
    GluonPlayer
    ${GLUON_CORE_LIBS}
    ${QT_QTDECLARATIVE_LIBRARY}
    CACHE PATHS "Libraries required for Gluon Player (QML version)"
)

if(NOT APPLE)
    install(TARGETS gluon_qmlplayer DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
    install(FILES gluon_qmlplayer.desktop DESTINATION ${SHARE_INSTALL_DIR}/applications)
endif()





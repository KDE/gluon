cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(qtplayer_SRCS
    main.cpp
    mainwindow.cpp
)

qt4_automoc(${qtplayer_SRCS})
add_executable(gluon_qtplayer ${qtplayer_SRCS})
target_link_libraries(gluon_qtplayer ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS})

install(TARGETS gluon_qtplayer DESTINATION ${BIN_INSTALL_DIR})

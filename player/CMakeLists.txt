cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonPlayer)
    find_package(GluonCore REQUIRED)
    find_package(GluonEngine REQUIRED)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${GLUON_ENGINE_INCLUDES} ${GLUON_GRAPHICS_INCLUDES} 
                    ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(gluonplayer_SRCS
    main.cpp
    mainwindow.cpp
)

qt4_automoc(${gluonplayer_SRCS})
add_executable(gluonplayer ${gluonplayer_SRCS})
target_link_libraries(gluonplayer ${GLUON_ENGINE_LIBS} ${GLUON_GRAPHICS_LIBS})

install(TARGETS gluonplayer DESTINATION ${BIN_INSTALL_DIR})

add_subdirectory(plasmoid)

cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonPlayer)
    find_package(GluonCore REQUIRED)
    find_package(GluonEngine REQUIRED)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${GLUON_ENGINE_INCLUDES} ${GLUON_GRAPHICS_INCLUDES} 
                    ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(qt)

if(KDE4_FOUND AND WITH_KDE)
    include_directories(${KDE4_INCLUDES})
    add_subdirectory(plasmoid)
else(KDE4_FOUND AND WITH_KDE)
    if(WITH_KDE)
        message(WARNING "WITH_KDE is enabled but KDE libraries are not found - not building KDE-dependant Players")
    endif(WITH_KDE)
endif(KDE4_FOUND AND WITH_KDE)

if(INSTALL_EXAMPLES)
    install(DIRECTORY examples/invaders DESTINATION ${SHARE_INSTALL_DIR}/gluon/games/invaders)
    install(DIRECTORY examples/pong DESTINATION ${SHARE_INSTALL_DIR}/gluon/games/pong)
endif()

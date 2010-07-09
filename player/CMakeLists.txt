cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(NOT GLUON_BUILD_ALL)
    project(GluonPlayer)
    find_package(GluonCore REQUIRED)
    find_package(GluonEngine REQUIRED)
    find_package(GluonGraphics REQUIRED)
endif()

find_package(LibAttica REQUIRED)

include_directories(${GLUON_ENGINE_INCLUDES} ${GLUON_GRAPHICS_INCLUDES} 
                    ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
                    ${ATTICA_INCLUDE_DIRS})

set(libGluonPlayer_SRCS
    models/commentsmodel.cpp
    models/gamesmodel.cpp
)

qt4_automoc(${libGluonPlayer_SRCS})

add_library(GluonPlayer SHARED ${libGluonPlayer_SRCS})

set_target_properties(GluonPlayer PROPERTIES VERSION ${GLUON_VERSION_STRING}
    SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_PLAYER_LIB)

target_link_libraries(
    GluonPlayer
    ${LIBATTICA_LIBRARIES}
    ${GLUON_CORE_LIBS} ${GLUON_ENGINE_LIBS}
)

set(GLUON_PLAYER_LIBS
   GluonPlayer
   ${GLUON_CORE_LIBS}
   CACHE PATHS "Libraries required for Gluon Player"
)
install(TARGETS GluonPlayer DESTINATION ${LIB_INSTALL_DIR})
install(FILES models/comments.gdl DESTINATION $ENV{HOME}/.gluon/gamingfreedom.org)

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
    install(DIRECTORY examples/invaders DESTINATION ${SHARE_INSTALL_DIR}/gluon/games)
    install(DIRECTORY examples/pong DESTINATION ${SHARE_INSTALL_DIR}/gluon/games)
endif()

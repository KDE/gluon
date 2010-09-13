cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(NOT GLUON_BUILD_ALL)
    project(GluonPlayer)
    option(BUILD_PLASMOID "Build Gluon Player Plasmoid" ON)
    option(INSTALL_EXAMPLES "Install the game examples for Gluon Player" ON)
    find_package(GluonCore REQUIRED)
    find_package(GluonEngine REQUIRED)
    find_package(GluonGraphics REQUIRED)
    set(LIBATTICA_MIN_VERSION 0.2.0)
    find_package(LibAttica)
    if(LIBATTICA_FOUND)
        if(BUILD_PLASMOID)
            find_package(KDE4)
            if(NOT KDE4_FOUND)
                message(STATUS "BUILD_PLASMOID is enabled but KDE libraries are not found - not building the Plasmoid")
            endif(NOT KDE4_FOUND)
        endif(BUILD_PLASMOID)
    else(LIBATTICA_FOUND)
        message(STATUS "Could not find LibAttica or a too old version was found.")
        message(STATUS "Building Player Qt Application and Plasmoid and installing game examples wer disabled.")
    endif(LIBATTICA_FOUND)
endif(NOT GLUON_BUILD_ALL)

if(LIBATTICA_FOUND)
    include_directories(${GLUON_ENGINE_INCLUDES} ${GLUON_GRAPHICS_INCLUDES} 
                        ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
                        ${ATTICA_INCLUDE_DIRS})

    set(libGluonPlayer_SRCS
        models/highscoresmodel.cpp
        models/commentsmodel.cpp
        models/gamesmodel.cpp
        lib/authentication.cpp
        lib/atticamanager.cpp
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
    install(FILES models/highscores.gdl DESTINATION $ENV{HOME}/.gluon/gamingfreedom.org)
    
    add_subdirectory(qt)
    
    if(BUILD_PLASMOID)
        include_directories(${KDE4_INCLUDES})
        add_subdirectory(plasmoid)
    endif(BUILD_PLASMOID)

    if(INSTALL_EXAMPLES)
        install(DIRECTORY examples/invaders DESTINATION ${SHARE_INSTALL_DIR}/gluon/games)
        install(DIRECTORY examples/pong DESTINATION ${SHARE_INSTALL_DIR}/gluon/games)
    endif(INSTALL_EXAMPLES)

endif(LIBATTICA_FOUND)

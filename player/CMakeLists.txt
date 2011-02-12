cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(NOT GLUON_BUILD_ALL)
    project(GluonPlayer)
    option(BUILD_PLASMOID "Build Gluon Player Plasmoid" ON)
    option(INSTALL_EXAMPLES "Install the game examples for Gluon Player" ON)
    find_package(GluonCore REQUIRED)
    find_package(GluonInput REQUIRED)
    find_package(GluonEngine REQUIRED)
    find_package(GluonGraphics REQUIRED)
endif(NOT GLUON_BUILD_ALL)

set(LIBATTICA_MIN_VERSION 0.1.90)
find_package(LibAttica)
if(LIBATTICA_FOUND)
    if(BUILD_PLASMOID)
        find_package(KDE4)
        if(NOT KDE4_FOUND)
            message(STATUS "BUILD_PLASMOID is enabled but KDE libraries are not found - not building the Plasmoid")
        endif(NOT KDE4_FOUND)
    endif(BUILD_PLASMOID)
else(LIBATTICA_FOUND)
    message(WARNING "Could not find LibAttica or a too old version was found.")
    message(WARNING "Building libGluonPlayer without Attica support!")
endif(LIBATTICA_FOUND)

if(LIBATTICA_FOUND)
    include_directories(${GLUON_ENGINE_INCLUDES} ${GLUON_GRAPHICS_INCLUDES}
                        ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
                        ${ATTICA_INCLUDE_DIRS})

    set(libGluonPlayer_SRCS
        lib/models/highscoresmodel.cpp
        lib/models/commentsmodel.cpp
        lib/models/gamesmodel.cpp
        lib/models/gameitemsmodel.cpp
        lib/authentication.cpp
        lib/atticamanager.cpp
    )
else(LIBATTICA_FOUND)
    include_directories(${GLUON_ENGINE_INCLUDES} ${GLUON_GRAPHICS_INCLUDES}
                        ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
    set(libGluonPlayer_SRCS
        lib/models/gamesmodel.cpp
        lib/models/gameitemsmodel.cpp
    )
endif(LIBATTICA_FOUND)

qt4_automoc(${libGluonPlayer_SRCS})

add_library(GluonPlayer SHARED ${libGluonPlayer_SRCS})

set_target_properties(GluonPlayer PROPERTIES VERSION ${GLUON_VERSION_STRING}
    SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_PLAYER_LIB)

if(LIBATTICA_FOUND)
    target_link_libraries(
        GluonPlayer
        ${LIBATTICA_LIBRARIES}
        ${GLUON_CORE_LIBS} ${GLUON_ENGINE_LIBS}
    )

    set(GLUON_PLAYER_LIBS
        GluonPlayer
        ${LIBATTICA_LIBRARIES}
        ${GLUON_CORE_LIBS}
        CACHE PATHS "Libraries required for Gluon Player"
    )

    if(WITH_KDE)
        include_directories(${KDE4_INCLUDES})
        add_subdirectory(kde)
		add_subdirectory(kdeext)
    endif(WITH_KDE)

    if(BUILD_PLASMOID)
        include_directories(${KDE4_INCLUDES})
        add_subdirectory(plasmoid)
        add_subdirectory(qtext)
        if(QT_QTDECLARATIVE_FOUND)
            add_subdirectory(touch)
        else(QT_QTDECLARATIVE_FOUND)
            message(WARNING "Qt installation lacks Qt Declarative - disabling touch based player")
        endif(QT_QTDECLARATIVE_FOUND)
    endif(BUILD_PLASMOID)
else(LIBATTICA_FOUND)
    target_link_libraries(
        GluonPlayer
        ${GLUON_CORE_LIBS} ${GLUON_ENGINE_LIBS}
    )

    set(GLUON_PLAYER_LIBS
        GluonPlayer
        ${GLUON_CORE_LIBS}
        CACHE PATHS "Libraries required for Gluon Player"
    )
endif(LIBATTICA_FOUND)

install(TARGETS GluonPlayer RUNTIME DESTINATION bin LIBRARY DESTINATION ${LIB_INSTALL_DIR} ARCHIVE DESTINATION ${LIB_INSTALL_DIR})

add_subdirectory(qt)

add_subdirectory(icons)

if(INSTALL_EXAMPLES)
    install(DIRECTORY examples/apocalypse DESTINATION ${SHARE_INSTALL_DIR}/gluon/games)
    install(DIRECTORY examples/invaders DESTINATION ${SHARE_INSTALL_DIR}/gluon/games)
    install(DIRECTORY examples/pong DESTINATION ${SHARE_INSTALL_DIR}/gluon/games)
endif(INSTALL_EXAMPLES)



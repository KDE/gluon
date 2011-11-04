cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

if(NOT GLUON_BUILD_ALL)
    project(GluonPlayer)
    option(INSTALL_EXAMPLES "Install the game examples for Gluon Player" ON)
    find_package(GluonCore REQUIRED)
    find_package(GluonInput REQUIRED)
    find_package(GluonEngine REQUIRED)
    find_package(GluonGraphics REQUIRED)
endif(NOT GLUON_BUILD_ALL)

set(LIBATTICA_MIN_VERSION 0.1.90)
find_package(LibAttica)
if(LIBATTICA_FOUND)
    include_directories(${LIBATTICA_INCLUDE_DIR})
    add_subdirectory(lib)

    find_package(Qt4)
    if(BUILD_GLUON_PLAYER_FREMANTLE)
        if(QT_QTDECLARATIVE_FOUND)
            add_subdirectory(fremantle)
        else(QT_QTDECLARATIVE_FOUND)
            message(WARNING "Qt installation lacks Qt Declarative - disabling handset based player")
        endif(QT_QTDECLARATIVE_FOUND)
    endif()

    if(BUILD_GLUON_PLAYER_DESKTOP)
        find_package(KDE4)
        if(KDE4_FOUND)
            include_directories(${KDE4_INCLUDES})
            add_subdirectory(desktop)
        else(KDE4_FOUND)
            message(STATUS "KDE libraries are not found - not building the KDE Desktop Player")
        endif(KDE4_FOUND)
    endif()

    if(BUILD_GLUON_PLAYER_PLASMOID)
        find_package(KDE4)
        if(KDE4_FOUND)
            include_directories(${KDE4_INCLUDES})
            add_subdirectory(plasmoid)
        else(KDE4_FOUND)
            message(STATUS "KDE libraries are not found - not building the Plasmoid Desktop Player")
        endif(KDE4_FOUND)
    endif()

    if(BUILD_GLUON_PLAYER_ACTIVE)
        find_package(KDE4)
        if(KDE4_FOUND)
            include_directories(${KDE4_INCLUDES})
            add_subdirectory(active)
        else(KDE4_FOUND)
            message(STATUS "KDE libraries are not found - not building the Plasmoid Active Player")
        endif(KDE4_FOUND)
    endif()

else(LIBATTICA_FOUND)
    message(WARNING "Could not find LibAttica or a too old version was found.")
    message(WARNING "Building libGluonPlayer without Attica support!")
endif(LIBATTICA_FOUND)

add_subdirectory(icons)
set(PLAYER_ICONS_INSTALLED TRUE)

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif(INSTALL_EXAMPLES)

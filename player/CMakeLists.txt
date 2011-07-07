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

    if(WITH_KDE)
        find_package(KDE4)
        if(KDE4_FOUND)
            include_directories(${KDE4_INCLUDES})
            add_subdirectory(kde)
            add_subdirectory(kdeext)

            if(BUILD_PLASMOID)
                add_subdirectory(plasmoid)
            endif(BUILD_PLASMOID)
        else(KDE4_FOUND)
            message(STATUS "WITH_KDE is enabled but KDE libraries are not found - not building the KDE players or the Plasmoid")
        endif(KDE4_FOUND)
    endif(WITH_KDE)

    find_package(Qt4)
    if(QT_QTDECLARATIVE_FOUND)
        add_subdirectory(touch)
    else(QT_QTDECLARATIVE_FOUND)
        message(WARNING "Qt installation lacks Qt Declarative - disabling touch based player")
    endif(QT_QTDECLARATIVE_FOUND)

else(LIBATTICA_FOUND)
    message(WARNING "Could not find LibAttica or a too old version was found.")
    message(WARNING "Building libGluonPlayer without Attica support!")
endif(LIBATTICA_FOUND)

add_subdirectory(icons)
set(PLAYER_ICONS_INSTALLED TRUE)
add_subdirectory(qt)

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif(INSTALL_EXAMPLES)

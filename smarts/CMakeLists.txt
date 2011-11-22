project(BehaviorTrees)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(common)

find_package(KDE4)
if(KDE4_FOUND)
    include_directories(${KDE4_INCLUDES})
    if(BUILD_GLUON_SMARTS_EDITOR)
        add_subdirectory(editor)
    endif(BUILD_GLUON_SMARTS_EDITOR)
else(KDE4_FOUND)
    message(STATUS "KDE libraries are not found - not building the Smarts BtEditor")
endif(KDE4_FOUND)


add_subdirectory(lib)



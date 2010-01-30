cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonEngine)
    find_package(GluonCore REQUIRED)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(${GLUON_CORE_INCLUDES})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

#TODO: Make the assets and components build.
#add_subdirectory(assets)
#add_subdirectory(components)

set(GluonEngine_SRCS
    savable.cpp
    asset.cpp
    component.cpp
    componentprivate.cpp
    gameobject.cpp
    gameobjectprivate.cpp
    prefab.cpp
    prefabprivate.cpp
    scene.cpp
    sceneprivate.cpp
    filelocation.cpp
    filelocationprivate.cpp

    game.cpp
    gameprivate.cpp
)

qt4_automoc(${GluonEngine_SRCS})
add_library(GluonEngine SHARED ${GluonEngine_SRCS})

set_target_properties(GluonEngine PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})
if(GLUON_BUILD_ALL)
    add_dependencies(GluonEngine GluonCore)
    target_link_libraries(GluonEngine GluonCore)
else()
    target_link_libraries(GluonEngine ${GLUON_CORE_LIBS})
endif()

install(TARGETS GluonEngine DESTINATION ${LIB_INSTALL_DIR})

install(
    FILES
    savable.h
    asset.h
    component.h
    gameobject.h
    prefab.h
    scene.h
    filelocation.h

    gluon_engine_export.h
    game.h

    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/engine
    COMPONENT Devel
)

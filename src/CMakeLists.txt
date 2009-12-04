cmake_minimum_required(VERSION 2.6)
project(libgluon)

add_definitions(-DMAKE_GLUON_LIB)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake/modules")

find_package(Qt4 REQUIRED)

IF(NOT WIN32 AND NOT APPLE)
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES})
ENDIF()

find_package(Eigen2 REQUIRED)
find_package(GluonCommon REQUIRED)
find_package(KGL REQUIRED)

message("-- Found KGL include dir: " ${KGL_INCLUDE_DIR})
message("-- Found KGL includes: " ${KGL_INCLUDES})
message("-- Found KGL library: " ${KGL_LIBRARY})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${KGL_INCLUDE_DIR}/gluon/kgl
    ${KGL_INCLUDE_DIR}/gluon
    ${KGL_INCLUDE_DIR}
    ${GLUONCOMMON_INCLUDES}
    ${EIGEN2_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}/..
    gameproject)


set(gluon_LIB_SRCS
    gameproject/asset.cpp
    gameproject/component.cpp
    gameproject/componentprivate.cpp
    gameproject/gameobject.cpp
    gameproject/gameobjectprivate.cpp
    gameproject/prefab.cpp
    gameproject/prefabprivate.cpp
    gameproject/gameproject.cpp
    gameproject/gameprojectprivate.cpp

    gluonmainwindow.cpp
    gluonobject.cpp
    gluonobjectprivate.cpp
    gluonobjectfactory.cpp
    gdlhandler.cpp
    game.cpp
    gameprivate.cpp

    components/soundcomponents/soundemittercomponent.cpp
    components/soundcomponents/soundlistenercomponent.cpp
    components/spriterendercomponent/spriterendercomponent.cpp
    components/spriterendercomponent/spriterendercomponentprivate.cpp

    assets/soundasset/soundasset.cpp
    assets/textureasset/textureasset.cpp

    debughelper.cpp
   )

qt4_automoc(${gluon_LIB_SRCS})

SET(gluon_RCCS
    ../resources/resources.qrc
   )

QT4_ADD_RESOURCES(gluon_RCC_SRCS ${gluon_RCCS})
add_library(gluon SHARED ${gluon_LIB_SRCS} ${gluon_RCC_SRCS})

set_target_properties(gluon PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})
target_link_libraries(gluon kgl kal ${KDE4_KDEUI_LIBS})
target_link_libraries(kcl)
target_link_libraries(gluon ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY} ${X11_Xrandr_LIB} ${X11_LIBRARY} )
target_link_libraries(gluon
                      ${KDE4_KDEUI_LIBS} ${KDE4_PHONON_LIBS} ${KDE4_KIO_LIBS}
                      ${OPENAL_LIBRARY}
                      ${SNDFILE_LIBRARY} ${OGG_LIBRARIES} ${VORBISFILE_LIBRARIES})
########### INSTALL FILES ###############

if(APPLE)

install(TARGETS gluon DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

else()

install(TARGETS gluon ${INSTALL_TARGETS_DEFAULT_ARGS} )

endif()

install(FILES
    gameproject/asset.h
    gameproject/component.h
    gameproject/gameobject.h
    gameproject/prefab.h
    gameproject/gameproject.h

    gluon_export.h
    gluonmainwindow.h
    gluonobject.h
    gluonobjectfactory.h
    gdlhandler.h
    game.h
    gluonvarianttypes.h
    debughelper.h

    components/spriterendercomponent/spriterendercomponent.h

    assets/textureasset/textureasset.h

DESTINATION ${INCLUDE_INSTALL_DIR}/gluon COMPONENT Devel)

#add_subdirectory(Components)

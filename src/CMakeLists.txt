include_directories(../)
include_directories(${EIGEN2_INCLUDE_DIR})
include_directories(gameproject)
include_directories(./)


set(gluon_LIB_SRCS
    gameproject/asset.cpp
    gameproject/component.cpp
    gameproject/componentprivate.cpp
    gameproject/gameobject.cpp
    gameproject/gameobjectprivate.cpp
    gameproject/prefab.cpp
    gameproject/prefabprivate.cpp
    gameproject/project.cpp
    gameproject/projectprivate.cpp
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

#      gluondialog.cpp
#      kglconfig.cpp
#      kalconfig.cpp
#      kclconfig.cpp
#      gluonintroitem.cpp

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
include_directories(${GLEW_INCLUDE_DIR}/..)
target_link_libraries(gluon ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY} ${X11_Xrandr_LIB} ${X11_LIBRARY} )
target_link_libraries(gluon
                      ${KDE4_KDEUI_LIBS} ${KDE4_PHONON_LIBS} ${KDE4_KIO_LIBS}
                      ${OPENAL_LIBRARY} #${ALUT_LIBRARY}
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
    gameproject/project.h
    gameproject/gameproject.h

    gluon_export.h
    gluonmainwindow.h
    gluonobject.h
    gluonobjectfactory.h
    gdlhandler.h
    game.h
    gluonvarianttypes.h

    components/spriterendercomponent/spriterendercomponent.h

    assets/textureasset/textureasset.h 
#    gluondialog.h
#    kglconfig.h
#    kalconfig.h
#    kclconfig.h
#   gluonintroitem.h
   DESTINATION ${INCLUDE_INSTALL_DIR}/gluon COMPONENT Devel)

#add_subdirectory(Components)

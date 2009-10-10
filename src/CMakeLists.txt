include_directories(../)
include_directories(${EIGEN2_INCLUDE_DIR})
include_directories(gameproject)

set(gluon_LIB_SRCS
    gameproject/asset.cpp
    gameproject/assetprivate.cpp
    gameproject/component.cpp
    gameproject/componentprivate.cpp
    gameproject/gameobject.cpp
    gameproject/gameobjectprivate.cpp
    gameproject/prefab.cpp
    gameproject/prefabprivate.cpp
    gameproject/project.cpp
    gameproject/projectprivate.cpp

    gluonmainwindow.cpp
    gluonobject.cpp
    gluonobjectprivate.cpp
    gluonobjectfactory.cpp
    gluonobjectfactoryprivate.cpp
    gdlhandler.cpp
    game.cpp
    gameprivate.cpp
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
kde4_add_library(gluon SHARED ${gluon_LIB_SRCS} ${gluon_RCC_SRCS})

set_target_properties(gluon PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)
target_link_libraries(gluon kgl kal kcl ${KDE4_KDEUI_LIBS})
target_link_libraries(gluon ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY} ${X11_Xrandr_LIB} ${X11_LIBRARY} )
target_link_libraries(gluon
                      ${KDE4_KDEUI_LIBS} ${KDE4_PHONON_LIBS} ${KDE4_KIO_LIBS}
                      ${OPENAL_LIBRARY} ${ALUT_LIBRARY}
                      ${SNDFILE_LIBRARY} ${OGG_LIBRARIES} ${VORBISFILE_LIBRARIES})
########### INSTALL FILES ###############

install(TARGETS gluon ${INSTALL_TARGETS_DEFAULT_ARGS} )

install(FILES
    gameproject/asset.h
    gameproject/component.h
    gameproject/gameobject.h
    gameproject/prefab.h
    gameproject/project.h

    gluonmainwindow.h
    gluonobject.h
    gluonobjectfactory.h
    gdlhandler.h
    game.h
#    gluondialog.h
#    kglconfig.h
#    kalconfig.h
#    kclconfig.h
#   gluonintroitem.h
   DESTINATION ${INCLUDE_INSTALL_DIR}/gluon COMPONENT Devel)


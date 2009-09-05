include_directories(../)

set(gluon_LIB_SRCS 
     gluonmainwindow.cpp
#      gluondialog.cpp
#      kglconfig.cpp
#      kalconfig.cpp
#      kclconfig.cpp
#      gluonintroitem.cpp

   )

SET(gluon_RCCS
    ../resources/resources.qrc
   )

QT4_ADD_RESOURCES(gluon_RCC_SRCS ${gluon_RCCS})
kde4_add_library(gluon SHARED ${gluon_LIB_SRCS} ${gluon_RCC_SRCS})

set_target_properties(gluon PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)
target_link_libraries(gluon ${KDE4_KDEUI_LIBS} kgl kal kcl)
target_link_libraries(gluon ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY} ${X11_Xrandr_LIB} ${X11_LIBRARY} )
target_link_libraries(gluon
                      ${KDE4_KDEUI_LIBS} ${KDE4_PHONON_LIBS} ${KDE4_KIO_LIBS}
                      ${OPENAL_LIBRARY} ${ALUT_LIBRARY}
                      ${SNDFILE_LIBRARY} ${OGG_LIBRARIES} ${VORBISFILE_LIBRARIES})
########### INSTALL FILES ###############

install(TARGETS gluon ${INSTALL_TARGETS_DEFAULT_ARGS} )

install(FILES
    gluonmainwindow.h
#    gluondialog.h
#    kglconfig.h
#    kalconfig.h
#    kclconfig.h
#   gluonintroitem.h
   DESTINATION ${INCLUDE_INSTALL_DIR}/gluon COMPONENT Devel)


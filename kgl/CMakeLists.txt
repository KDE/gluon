include_directories(Box2D/Include)
include_directories(physics)

set(kgl_LIB_SRCS 
    #kglanimitem.cpp
    kglbaseitem.cpp
    #kglblurprogram.cpp
    kglboxitem.cpp
    kglcircleitem.cpp
    #kglcontaineritem.cpp
	kglengine.cpp
    kglgriditem.cpp
    kglintroitem.cpp
    kglitem.cpp
    kglitemlist.cpp
    kglparticlesitem.cpp
    kglphysicsengine.cpp
    kglphysicsitem.cpp
    kglpixmapitem.cpp
    kglpoint.cpp
    kglpolygonitem.cpp
    kglprogram.cpp
    kglshader.cpp
    kglshadowitem.cpp
    kgltextitem.cpp
    kgltexture.cpp
    kglview.cpp
    kglscreenconfig.cpp
    kglinfowidget.cpp

)

SET(kgl_RCCS
     shaders/shaders.qrc
    )

QT4_ADD_RESOURCES(kgl_RCC_SRCS ${kgl_RCCS})
kde4_add_library(kgl SHARED ${kgl_LIB_SRCS} ${kgl_RCC_SRCS})
set_target_properties(kgl PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)

target_link_libraries(kgl ${QT_QTOPENGL_LIBRARY})
target_link_libraries(kgl ${KDE4_KDEUI_LIBS})
target_link_libraries(kgl ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY} ${X11_Xrandr_LIB} ${X11_LIBRARY} )
target_link_libraries(kgl Box2D)

# add_subdirectory(examples)
# add_subdirectory(includes)
# add_subdirectory(screensavers)
# add_subdirectory(script)
# add_subdirectory(tests)
########### INSTALL FILES ###############

install(TARGETS kgl ${INSTALL_TARGETS_DEFAULT_ARGS} )

install(FILES
    #kglanimitem.h
    kglbaseitem.h
    #kglblurprogram.h
    kglboxitem.h
    kglcircleitem.h
    #kglcontaineritem.h
    kglengine.h
    kglgriditem.h
    kglintroitem.h
    kglitem.h
    kglitemlist.h
    kglparticlesitem.h
    kglphysicsengine.h
    kglphysicsitem.h
    kglpixmapitem.h
    kglpoint.h
    kglpolygonitem.h
    kglprogram.h
    kglshader.h
    kglshadowitem.h
    kgltextitem.h
    kgltexture.h
    kglview.h
    kglscreenconfig.h
    kglinfowidget.h


    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kgl COMPONENT Devel)
add_subdirectory(Box2D) #add header installation

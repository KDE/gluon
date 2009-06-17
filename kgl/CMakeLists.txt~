include_directories(Box2D/Include)
include_directories(physics)

set(kgl_LIB_SRCS 
    kglwidget.cpp
    glpoint.cpp
    #kgamekey.cpp
    #kglintro.cpp
    kglitembase.cpp
    kglitem.cpp
    #kglcontaineritem.cpp
    kglpixmapitem.cpp
    #kglanimitem.cpp
    kgltextitem.cpp
    #kglparticle.cpp
    #kglparticlesitem.cpp
    kglboxitem.cpp
    #kglpolygonitem.cpp
    #kglcircleitem.cpp
    kglphysicswidget.cpp
    kglphysicsitem.cpp
    kgltexture.cpp
    kglitemlist.cpp
    kglshader.cpp
    kglprogram.cpp

    #fx/kglshadowitem.cpp
   )

SET(kgl_RCCS
    resources/resources.qrc
   )

QT4_ADD_RESOURCES(kgl_RCC_SRCS ${kgl_RCCS})
kde4_add_library(kgl SHARED ${kgl_LIB_SRCS} ${kgl_RCC_SRCS})
set_target_properties(kgl PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION 1)

target_link_libraries(kgl ${QT_QTOPENGL_LIBRARY})
target_link_libraries(kgl ${KDE4_KDEUI_LIBS})
target_link_libraries(kgl ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY} ${X11_Xrandr_LIB} ${X11_LIBRARY} )
target_link_libraries(kgl Box2D)

# add_subdirectory(script)
# add_subdirectory(screensavers)
# add_subdirectory(tests)
# add_subdirectory(examples)
# add_subdirectory(includes)
########### INSTALL FILES ###############

install(TARGETS kgl ${INSTALL_TARGETS_DEFAULT_ARGS} )

install(FILES
    glpoint.h
    kgamekey.h
    kglwidget.h
    kglintro.h
    kglanimitem.h
    kglitemlist.h
    kglitem.h
    kglitembase.h
    kglcontaineritem.h
    kgltextitem.h
    kglparticle.h
    kglparticlesitem.h
    kglpixmapitem.h
    kglboxitem.h
    kglpolygonitem.h
    kglcircleitem.h
    #kglcollisionrule.h
    kglphysicswidget.h
    kglphysicsitem.h
    kgltexture.h
    kglshader.h
    kglprogram.h
   fx/kglshadowitem.h



    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kgl COMPONENT Devel)
add_subdirectory(Box2D) #add header installation

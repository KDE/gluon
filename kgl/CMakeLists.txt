cmake_minimum_required(VERSION 2.6)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

#TODO: We should really find a way not to include Box2D stuff manually.
#find_package(Box2D REQUIRED)

IF(Q_WS_X11)
    find_package(X11 REQUIRED)
ENDIF(Q_WS_X11)

include_directories(Box2D/Include)
include_directories(physics)
include_directories(${QT_QTOPENGL_INCLUDE_DIR})
include_directories(./)

set(kgl_LIB_SRCS
    kgldisplay.cpp
    #kglanimitem.cpp
    kglbaseitem.cpp
    kglboxitem.cpp
    kglcircleitem.cpp
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
    kglshader.cpp
    kglshadowitem.cpp
    kgltextitem.cpp
    kgltexture.cpp
    kglview.cpp
    kglscreen.cpp
    kglinfowidget.cpp
    kgldebugphysicsview.cpp
    kglresolution.cpp
    kglpainter.cpp
    widgets/kglresolutiondialog.cpp
)

IF(NOT WIN32 AND NOT Q_WS_MAC)
SET(kgl_LIB_SRCS
    kglfx.cpp
    kglprogram.cpp
    ${kgl_LIB_SRCS})
ENDIF(NOT WIN32 AND NOT Q_WS_MAC)

if(Q_WS_X11)
    set(kgl_LIB_SRCS
        kglrandrscreen.cpp
        ${kgl_LIB_SRCS})
endif(Q_WS_X11)

SET(kgl_RCCS
shaders/shaders.qrc
)

QT4_ADD_RESOURCES(kgl_RCC_SRCS ${kgl_RCCS})

qt4_automoc(${kgl_LIB_SRCS} ${kgl_RCC_SRCS})
add_library(kgl SHARED ${kgl_LIB_SRCS} ${kgl_RCC_SRCS})

set_target_properties(kgl PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})

include_directories(${GLEW_INCLUDE_DIR}/..)

target_link_libraries(kgl
                      ${QT_QTOPENGL_LIBRARY}
                      ${OPENGL_gl_LIBRARY}
                      ${OPENGL_glu_LIBRARY}
                      ${GLEW_LIBRARY}
                      Box2D)

target_link_libraries(kgl ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

#Only link X11 if we are actually using X11
if(Q_WS_X11)
    target_link_libraries(kgl ${X11_Xrandr_LIB} ${X11_LIBRARIES} )
endif(Q_WS_X11)

# add_subdirectory(examples)
# add_subdirectory(includes)
# add_subdirectory(screensavers)
# add_subdirectory(script)
# add_subdirectory(tests)
########### INSTALL FILES ###############

if(APPLE)

install(TARGETS kgl DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

else()

install(TARGETS kgl ${INSTALL_TARGETS_DEFAULT_ARGS} )

endif()

install(FILES
  kgl_export.h
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
  kglshader.h
  kglshadowitem.h
  kgltextitem.h
  kgltexture.h
  kglview.h
  kgldisplay.h
  kglscreen.h
  kglinfowidget.h
  kgldebugphysicsview.h
  kglpainter.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kgl COMPONENT Devel
)

IF(NOT WIN32)
  INSTALL(FILES
    kglfx.h
    kglprogram.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kgl COMPONENT Devel
  )
ENDIF(NOT WIN32)

if(Q_WS_X11)
    install(FILES
        kglrandrscreen.h
        DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kgl COMPONENT Devel
    )
endif(Q_WS_X11)

INSTALL(FILES
  widgets/kglresolutiondialog.h
  DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/kgl/widgets COMPONENT Devel
)

add_subdirectory(Box2D) #add header installation

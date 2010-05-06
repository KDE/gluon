cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
project(GluonGraphics)
find_package(GluonCore REQUIRED)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}

    ${GLUON_CORE_INCLUDES}

    ${OPENGL_INCLUDE_DIR}
      ${GLEW_INCLUDE_DIR}
        )

set(GLUON_GRAPHICS_INCLUDES
${CMAKE_CURRENT_SOURCE_DIR}
  ${GLUON_CORE_INCLUDES}

    ${OPENGL_INCLUDE_DIR}
      ${GLEW_INCLUDE_DIR}
        CACHE PATHS "Includes required for Gluon Graphics"
        )

set(GluonGraphics_SRCS
camera.cpp
glwidget.cpp
fpscounter.cpp
textrenderer.cpp
vertex.cpp
texture.cpp
glpainter.cpp
item.cpp
itemlist.cpp
engine.cpp
mesh.cpp
transform.cpp
widgetproxy.cpp
textitem.cpp


    meshes/polygonmesh.cpp
    meshes/cubemesh.cpp
    meshes/gridmesh.cpp
    meshes/conemesh.cpp
    meshes/discmesh.cpp
    meshes/discsectionmesh.cpp
    meshes/icospheremesh.cpp
    meshes/uvspheremesh.cpp
    meshes/cylindremesh.cpp
    meshes/spritemesh.cpp

    shaders/lightshader.cpp
    shaders/posterizeshader.cpp
    shaders/mosaicshader.cpp
)

set(GluonGraphics_RESOURCES
shaders/GLSL/shaders.qrc
)

qt4_add_resources( GluonGraphics_RC_SRCS ${GluonGraphics_RESOURCES})
qt4_automoc(${GluonGraphics_SRCS})
add_library(GluonGraphics SHARED ${GluonGraphics_SRCS} ${GluonGraphics_RC_SRCS})

set_target_properties(GluonGraphics PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_GRAPHICS_LIB)

if(GLUON_BUILD_ALL)
add_dependencies(GluonGraphics GluonCore)
endif()

target_link_libraries(
GluonGraphics
${GLUON_CORE_LIBS}
  ${QT_QTOPENGL_LIBRARY}
    ${OPENGL_gl_LIBRARY}
      ${OPENGL_glu_LIBRARY}
        ${GLEW_LIBRARY}
          )

set(GLUON_GRAPHICS_LIBS
GluonGraphics
${GLUON_CORE_LIBS}
  ${QT_QTOPENGL_LIBRARY}
    ${OPENGL_gl_LIBRARY}
      ${OPENGL_glu_LIBRARY}
        ${GLEW_LIBRARY}
          CACHE PATHS "Libraries required for Gluon Graphics"
          )

install(TARGETS GluonGraphics DESTINATION ${LIB_INSTALL_DIR})

install(
FILES
gluon_graphics_export.h
camera.h
glwidget.h
fpscounter.h
textrenderer.h
vertex.h
texture.h
glpainter.h
item.h
itemlist.h
engine.h
transform.h
mesh.h
widgetproxy.h
textitem.h

DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/graphics
COMPONENT Devel
)

install(
FILES
meshes/polygonmesh.h
meshes/cubemesh.h
meshes/gridmesh.h
meshes/conemesh.h
meshes/discmesh.h
meshes/discsectionmesh.h
meshes/icospheremesh.h
meshes/uvspheremesh.h
meshes/cylindremesh.h
meshes/spritemesh.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/graphics/meshes
COMPONENT Devel
)

install(
FILES
shaders/lightshader.h
shaders/posterizeshader.h
shaders/mosaicshader.h
DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/graphics/shaders
COMPONENT Devel
)

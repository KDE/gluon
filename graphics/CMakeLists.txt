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

set(GluonGraphics_SRCS
    camera.cpp
    glwidget.cpp
    fpscounter.cpp
    textrenderer.cpp
    vertex.cpp
    texture.cpp
    glpainter.cpp
    baseitem.cpp
    item.cpp
    itemlist.cpp
    engine.cpp
    program.cpp
    shader.cpp
    fx.cpp
    widgetproxy.cpp
)

qt4_automoc(${GluonGraphics_SRCS})
add_library(GluonGraphics SHARED ${GluonGraphics_SRCS})

set_target_properties(GluonGraphics PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})

if(GLUON_BUILD_ALL)
    add_dependencies(GluonGraphics GluonCore)
    target_link_libraries(GluonGraphics GluonCore)
else(GLUON_BUILD_ALL)
    target_link_libraries(GluonGraphics ${GLUON_CORE_LIBS})
endif()

target_link_libraries(
    GluonGraphics
    ${QT_QTOPENGL_LIBRARY}
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${GLEW_LIBRARY}
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
    baseitem.h
    item.h
    itemlist.h
    engine.h
    engine_p.h
    program.h
    shader.h
    fx.h
    widgetproxy.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/graphics
    COMPONENT Devel
)

install(
    FILES
    cmake/FindGluonGraphics.cmake
    cmake/FindGLEW.cmake
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/cmake
    COMPONENT Devel
)
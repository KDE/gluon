find_package( OpenGL REQUIRED )
find_package( Qt5X11Extras REQUIRED CONFIG )
find_package( Qt5Quick REQUIRED CONFIG )
find_package( Qt5OpenGL REQUIRED CONFIG )

include_directories( ${OPENGL_INCLUDE_DIR} )

set( gluongraphics_backend_SRCS
    glxbackend.cpp
    glxcontext.cpp
    glxfunctions.cpp
    glxoutputsurface.cpp
    glxshader.cpp
    glxbuffer.cpp
    glxtexturedata.cpp
    glxrendertarget.cpp
    glxmeshdata.cpp
    glxqtquickrenderer.cpp
)

gluon_add_plugin( gluongraphics_backend
    MODULE Gluon::Graphics
    SOURCES ${gluongraphics_backend_SRCS}
    LIBRARIES ${OPENGL_LIBRARIES} dl Qt5::X11Extras Qt5::Quick Qt5::OpenGL
)

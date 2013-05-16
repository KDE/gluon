find_package( OpenGL REQUIRED )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/graphics ${OPENGL_INCLUDE_DIR} )

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
)

gluon_add_plugin( gluongraphics_backend GluonGraphics 
    "${gluongraphics_backend_SRCS}"  
    ${GLUONGRAPHICS_LIBRARIES} ${OPENGL_LIBRARIES} dl
)

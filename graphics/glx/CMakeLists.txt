
find_package( OpenGL )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${OPENGL_INCLUDE_DIR} )

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

qt4_automoc( ${gluongraphics_backend_SRCS} )
add_library( gluongraphics_backend MODULE ${gluongraphics_backend_SRCS} )
set_target_properties( gluongraphics_backend PROPERTIES PREFIX "" )

target_link_libraries(
    gluongraphics_backend
    ${GLUON_GRAPHICS_LIBS}
    ${OPENGL_LIBRARIES}
)

install(
    TARGETS gluongraphics_backend
    DESTINATION ${LIB_INSTALL_DIR}/gluon
)

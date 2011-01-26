
#ifndef GL_HEADERS_H
#define GL_HEADERS_H

#ifdef _WIN32
#include <windows.h>
#include <GL/glee.h>
#else
#ifdef GLUON_GRAPHICS_GLES
typedef char GLchar;
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#endif

#include <QtCore/QDebug>

#define GL_CHECK(X) X;\
    {\
        int error = glGetError(); \
        if(error != 0) qDebug() << "GL Error" << error;\
    }

#endif //GL_HEADERS_H

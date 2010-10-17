#ifdef GLUON_GRAPHICS_GLES
  #include <GLES2/gl2.h>
  #include <GLES2/gl2ext.h>
#else
  #include <gl.h>
  #include <glext.h>
#endif

#include <QtCore/QDebug>

#define GL_CHECK(X) X;\
{\
    int error = glGetError(); \
    if(error != 0) qDebug() << "GL Error" << error;\
}

#include "glxfunctions.h"

#include <dlfcn.h>

#include <GL/gl.h>

namespace GluonGraphics
{
namespace GLX
{

#define FIND_GLFUNCTION( type, function )\
    function = (type)getProcAddress( #function );

static glXFuncPtr getProcAddress( const char* name )
{
    glXFuncPtr ret = NULL;
    if( _glXGetProcAddress != NULL )
        ret = _glXGetProcAddress( ( const GLubyte* ) name);
    if( ret == NULL )
        ret = (glXFuncPtr)dlsym( RTLD_DEFAULT, name );
    return ret;
}

void initializeFunctions()
{
    _glXGetProcAddress = (glXGetProcAddress_func)getProcAddress( "glXGetProcAddress" );
    if( _glXGetProcAddress == NULL )
        _glXGetProcAddress = (glXGetProcAddress_func)getProcAddress( "glXGetProcAddressARB" );

    FIND_GLFUNCTION( PFNGLGENBUFFERSARBPROC, glGenBuffersARB );
    FIND_GLFUNCTION( PFNGLDELETEBUFFERSARBPROC, glDeleteBuffersARB );
    FIND_GLFUNCTION( PFNGLBUFFERDATAARBPROC, glBufferDataARB );
    FIND_GLFUNCTION( PFNGLBUFFERSUBDATAARBPROC, glBufferSubDataARB );
    FIND_GLFUNCTION( PFNGLBINDBUFFERARBPROC, glBindBufferARB );

    FIND_GLFUNCTION( PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer );
    FIND_GLFUNCTION( PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray );
    FIND_GLFUNCTION( PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray );

    FIND_GLFUNCTION( PFNGLCREATESHADERPROC, glCreateShader );
    FIND_GLFUNCTION( PFNGLDELETESHADERPROC, glDeleteShader );
    FIND_GLFUNCTION( PFNGLSHADERSOURCEPROC, glShaderSource );
    FIND_GLFUNCTION( PFNGLCOMPILESHADERPROC, glCompileShader );
    FIND_GLFUNCTION( PFNGLGETSHADERIVPROC, glGetShaderiv );
    FIND_GLFUNCTION( PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog );
    FIND_GLFUNCTION( PFNGLUNIFORM1IPROC, glUniform1i );
    FIND_GLFUNCTION( PFNGLUNIFORM1FPROC, glUniform1f );
    FIND_GLFUNCTION( PFNGLUNIFORM2FPROC, glUniform2f );
    FIND_GLFUNCTION( PFNGLUNIFORM3FPROC, glUniform3f );
    FIND_GLFUNCTION( PFNGLUNIFORM4FPROC, glUniform4f );
    FIND_GLFUNCTION( PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv );

    FIND_GLFUNCTION( PFNGLCREATEPROGRAMPROC, glCreateProgram );
    FIND_GLFUNCTION( PFNGLDELETEPROGRAMPROC, glDeleteProgram );
    FIND_GLFUNCTION( PFNGLUSEPROGRAMPROC, glUseProgram );
    FIND_GLFUNCTION( PFNGLLINKPROGRAMPROC, glLinkProgram );
    FIND_GLFUNCTION( PFNGLATTACHSHADERPROC, glAttachShader );
    FIND_GLFUNCTION( PFNGLGETPROGRAMIVPROC, glGetProgramiv );
    FIND_GLFUNCTION( PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog );
    FIND_GLFUNCTION( PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib );
    FIND_GLFUNCTION( PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation );
    FIND_GLFUNCTION( PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform );
    FIND_GLFUNCTION( PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation );

    FIND_GLFUNCTION( PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffersEXT );
    FIND_GLFUNCTION( PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffersEXT );
    FIND_GLFUNCTION( PFNGLISRENDERBUFFEREXTPROC, glIsRenderbufferEXT );
    FIND_GLFUNCTION( PFNGLBINDRENDERBUFFEREXTPROC, glBindRenderbufferEXT );
    FIND_GLFUNCTION( PFNGLRENDERBUFFERSTORAGEEXTPROC, glRenderbufferStorageEXT );
    FIND_GLFUNCTION( PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC, glGetRenderbufferParamterivEXT );

    FIND_GLFUNCTION( PFNGLGENFRAMEBUFFERSEXTPROC, glGenFramebuffersEXT );
    FIND_GLFUNCTION( PFNGLDELETEFRAMEBUFFERSEXTPROC, glDeleteFramebuffersEXT );
    FIND_GLFUNCTION( PFNGLISFRAMEBUFFEREXTPROC, glIsFramebufferEXT );
    FIND_GLFUNCTION( PFNGLBINDFRAMEBUFFEREXTPROC, glBindFramebufferEXT );
    FIND_GLFUNCTION( PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC, glCheckFramebufferStatusEXT );
    FIND_GLFUNCTION( PFNGLFRAMEBUFFERTEXTURE1DEXTPROC, glFramebufferTexture1DEXT );
    FIND_GLFUNCTION( PFNGLFRAMEBUFFERTEXTURE2DEXTPROC, glFramebufferTexture2DEXT );
    FIND_GLFUNCTION( PFNGLFRAMEBUFFERTEXTURE3DEXTPROC, glFramebufferTexture3DEXT );
    FIND_GLFUNCTION( PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC, glFramebufferRenderbufferEXT );
    FIND_GLFUNCTION( PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC, glGetFramebufferAttachmentParameterivEXT );
    FIND_GLFUNCTION( PFNGLGENERATEMIPMAPEXTPROC, glGenerateMipMapEXT );
}

glXGetProcAddress_func _glXGetProcAddress;

PFNGLGENBUFFERSARBPROC glGenBuffersARB;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
PFNGLBUFFERDATAARBPROC glBufferDataARB;
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
PFNGLBINDBUFFERARBPROC glBindBufferARB;

PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLUNIFORM4FPROC glUniform4f;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

PFNGLGENRENDERBUFFERSPROC glGenRenderbuffersEXT;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffersEXT;
PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT;
PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT;
PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParamterivEXT;

PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT;
PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT;
PFNGLGENERATEMIPMAPEXTPROC glGenerateMipMapEXT;

}
}
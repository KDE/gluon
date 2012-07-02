/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef GLUONGRAPHICS_GLXFUNCTIONS_H
#define GLUONGRAPHICS_GLXFUNCTIONS_H

#include <GL/gl.h>

typedef void (*glXFuncPtr)();

namespace GluonGraphics
{
    namespace GLX
    {
        void initializeFunctions();

        typedef glXFuncPtr(*glXGetProcAddress_func)(const GLubyte*);
        extern glXGetProcAddress_func _glXGetProcAddress;

//Buffers
// typedef void (*glGenBuffers_func)(GLsizei, GLuint*);
        extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;
        extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
        extern PFNGLBUFFERDATAARBPROC glBufferDataARB;
        extern PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
        extern PFNGLBINDBUFFERARBPROC glBindBufferARB;

        extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
        extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
        extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

        //Shaders
        extern PFNGLCREATESHADERPROC glCreateShader;
        extern PFNGLDELETESHADERPROC glDeleteShader;
        extern PFNGLSHADERSOURCEPROC glShaderSource;
        extern PFNGLCOMPILESHADERPROC glCompileShader;
        extern PFNGLGETSHADERIVPROC glGetShaderiv;
        extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
        extern PFNGLUNIFORM1IPROC glUniform1i;
        extern PFNGLUNIFORM1FPROC glUniform1f;
        extern PFNGLUNIFORM2FPROC glUniform2f;
        extern PFNGLUNIFORM3FPROC glUniform3f;
        extern PFNGLUNIFORM4FPROC glUniform4f;
        extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

        //Programs
        extern PFNGLCREATEPROGRAMPROC glCreateProgram;
        extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
        extern PFNGLUSEPROGRAMPROC glUseProgram;
        extern PFNGLLINKPROGRAMPROC glLinkProgram;
        extern PFNGLATTACHSHADERPROC glAttachShader;
        extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
        extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
        extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
        extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
        extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

        //Renderbuffers
        extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffersEXT;
        extern PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffersEXT;
        extern PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT;
        extern PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT;
        extern PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT;
        extern PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParamterivEXT;

        //Framebuffers
        extern PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT;
        extern PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
        extern PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT;
        extern PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT;
        extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT;
        extern PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT;
        extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT;
        extern PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT;
        extern PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT;
        extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT;
        extern PFNGLGENERATEMIPMAPEXTPROC glGenerateMipMapEXT;
    }
}

#endif
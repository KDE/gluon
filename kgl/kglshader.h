/*
 * This file is part of the Gluon library.
 * Copyright 2008 Rivo Laks <rivolaks@hot.ee>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */


#ifndef KGLSHADER_H
#define KGLSHADER_H

#include <GL/glew.h>

class QString;
class QByteArray;

/**
 * \defgroup KGL KGL
 */
//@{


/**
 * @short Shader class
 *
 * Encapsulates a shader object. Note that shaders are only intermediate
 *  objects used to create @ref Program objects.
 * For simple use cases, you can use @ref Program class which can automatically
 *  create and use necessary Shader objects.
 *
 * @see Program
 **/
class KGLShader
{
    public:
       /**
        * Creates a shader of given type.
        * You need to manually call setSource() and compile() before
        * the shader can be added to a Program.
        **/
        KGLShader(GLenum type);
       /**
        * Loads shader of given type from given file.
        * Loaded shader is automatically compiled, so if the compilation succeeds,
        * you can add it to a Program object.
        **/
        KGLShader(GLenum type, const QString& filename);
       /**
        * Deletes a shader.
        * Shaders can be deleted after they are added to a @ref Program and the
        * program is linked.
        **/
        virtual ~KGLShader();

       /**
        * Sets shader source to @p source.
        * Next you will need to compile the shader.
        **/
        void setSource(const QString& source);
        void setSource(const QByteArray& source);

       /**
        * Compiles the shader.
        * If compilation succeeds, you can add it to a Program object.
        * If compilation fails, you can see the error using compileLog() method.
        **/
        bool compile();

        bool isValid() const
        {
            return mValid;
        }

        bool isCompiled() const
        {
            return mCompiled;
        }
       /**
        * @return Compile log of the shader or null if there was none or the
        *  shader hasn't been compiled.
        * Note that Shader keeps ownership of the returned string, so you
        * mustn't delete it.
        * TODO: maybe return QString?
        **/
        char* compileLog() const
        {
            return mCompileLog;
        }

        GLenum type() const
        {
            return mType;
        }

        GLuint glId() const
        {
            return mGLId;
        }

    protected:
        void init(GLenum type);

    protected:
        GLuint mGLId;
        GLenum mType;
        bool mValid;
        bool mCompiled;
        char* mCompileLog;
};

/**
 * Vertex shader subclass, so you needn't pass the type=GL_VERTEX_SHADER
 *  parameter to Shader constructor yourself.
 **/
class KGLVertexShader : public KGLShader
{
    public:
        KGLVertexShader();
        KGLVertexShader(const QString& filename);
};

/**
 * Fragment shader subclass, so you needn't pass the type=GL_FRAGMENT_SHADER
 *  parameter to Shader constructor yourself.
 **/
class KGLFragmentShader : public KGLShader
{
    public:
        KGLFragmentShader();
        KGLFragmentShader(const QString& filename);
};

//@}
#endif //KGLSHADER_H

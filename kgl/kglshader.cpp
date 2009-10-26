/*
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <GL/glew.h>

#include "kglshader.h"

#include <QFile>
#include <QDebug>


KGLShader::KGLShader(GLenum type)
{
    init(type);
}

KGLShader::KGLShader(GLenum type, const QString& filename)
{
    init(type);

    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << " Can't open file" << filename << "for reading";
        return;
    }
    setSource(f.readAll());
    compile();
}

KGLShader::~KGLShader()
{
    glDeleteShader(glId());
    delete[] mCompileLog;
}

void KGLShader::init(GLenum type)
{
    mType = type;
    mValid = false;
    mCompiled = false;
    mCompileLog = false;
    mGLId = glCreateShader(mType);
}

void KGLShader::setSource(const QString& source)
{
    setSource(source.toLatin1());
}

void KGLShader::setSource(const QByteArray& source)
{
    if (isCompiled()) {
        qDebug() <<"Can't set source for compiled shaders";
        return;
    }
    const char* src = source.data();
    glShaderSource(glId(), 1, &src, NULL);
}

bool KGLShader::compile()
{
    if (isCompiled()) {
        qDebug() << " Can't compile a shader twice";
        return false;
    }
    // Compile the shader
    glCompileShader(glId());
    mCompiled = true;
    // Make sure it compiled correctly
    int compiled;
    glGetShaderiv(glId(), GL_COMPILE_STATUS, &compiled);
    mValid = compiled;
    // Get info log
    GLsizei logsize, logarraysize;
    glGetShaderiv(glId(), GL_INFO_LOG_LENGTH, &logarraysize);
    mCompileLog = new char[logarraysize];
    glGetShaderInfoLog(glId(), logarraysize, &logsize, mCompileLog);
    // Output the log if compilation failed
    if (!mValid) {
       qDebug() << " Couldn't compile shader. Log follows:" << "\n"<< mCompileLog;
    }
    if (!logsize) {
        delete[] mCompileLog;
        mCompileLog = 0;
    }
    return mValid;
 }

KGLVertexShader::KGLVertexShader() : KGLShader(GL_VERTEX_SHADER)
{
}

KGLVertexShader::KGLVertexShader(const QString& filename) : KGLShader(GL_VERTEX_SHADER, filename)
{
}

KGLFragmentShader::KGLFragmentShader() : KGLShader(GL_FRAGMENT_SHADER)
{
}

KGLFragmentShader::KGLFragmentShader(const QString& filename) : KGLShader(GL_FRAGMENT_SHADER, filename)
{
}




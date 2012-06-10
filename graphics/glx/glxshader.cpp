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

#include "glxshader.h"

#include <GL/gl.h>
#include <GL/glext.h>
#include <QString>
#include <QDebug>

using namespace GluonGraphics;

class GLXShader::Private
{
    public:
        Private() : shaderProgram( 0 ), bound( false ) { }

        GLuint vertShader;
        GLuint fragShader;
        GLuint shaderProgram;

        bool bound;

        QList< GLuint > uniforms;
        QList< int > attributes;
};

GLXShader::GLXShader() : d( new Private )
{

}

GLXShader::~GLXShader()
{

}

bool GLXShader::build()
{
    GLuint vertShader = glCreateShader( GL_VERTEX_SHADER );
    const GLchar* vertSource[1] = { source( VertexProgramSource ).toAscii() };
    GLint vertSourceLength[1] = { source( VertexProgramSource ).toAscii().length() };
    glShaderSource( vertShader, 1, vertSource, vertSourceLength );
    glCompileShader( vertShader );

    char* out = new char[500];
    int length = 0;
    glGetShaderInfoLog( vertShader, 500, &length, out );
    if( length > 0 )
    {
        setError( QString( out ) );
        glDeleteShader( vertShader );
        return false;
    }

    GLuint fragShader = glCreateShader( GL_FRAGMENT_SHADER );
    const GLchar* fragSource[1] = { source( FragmentProgramSource ).toAscii() };
    GLint fragSourceLength[1] = { source( FragmentProgramSource ).toAscii().length() };
    glShaderSource( fragShader, 1, fragSource, fragSourceLength );
    glCompileShader( fragShader );

    glGetShaderInfoLog( fragShader, 500, &length, out );
    if( length > 0 )
    {
        setError( QString( out ) );
        glDeleteShader( vertShader );
        glDeleteShader( fragShader );
        return false;
    }

    d->shaderProgram = glCreateProgram();
    glAttachShader( d->shaderProgram, vertShader );
    glAttachShader( d->shaderProgram, fragShader );
    glLinkProgram( d->shaderProgram );

    glGetProgramInfoLog( d->shaderProgram, 500, &length, out );
    if( length > 0 )
    {
        setError( QString( out ) );
        glDeleteShader( vertShader );
        glDeleteShader( fragShader );
        glDeleteProgram( d->shaderProgram );
        return false;
    }

    delete[] out;

    //glUseProgram( d->shaderProgram );
    //glGetUni

    return true;
}

bool GLXShader::bind()
{
    if( !d->shaderProgram )
        return false;

    if( d->bound )
        return true;

    glUseProgram( d->shaderProgram );
    d->bound = true;
    return true;
}

void GLXShader::release()
{
    if( !d->bound )
        return;

    glUseProgram( 0 );
    d->bound = false;
}

void GLXShader::setProperty( const QString& name, const QVariant& value )
{

}

void GLXShader::setProperty( const QString& name, Texture* texture, int textureID )
{

}

QList< int > GLXShader::attributes()
{
    return QList<int>();
}

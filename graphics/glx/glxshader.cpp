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
#include <QColor>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QMatrix4x4>

#include <graphics/mathutils.h>
#include <graphics/texture.h>

#include "glxtexturedata.h"

using namespace GluonGraphics;

class GLXShader::Private
{
    public:
        Private() : shaderProgram( 0 ), bound( false ) { }
        void setUniform( GLint uniform, const QVariant& value );

        GLuint vertShader;
        GLuint fragShader;
        GLuint shaderProgram;

        uint currentTextureUnit;

        bool bound;

        QHash< QString, GLint > uniforms;
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
    QByteArray vertSourceArray = source( VertexProgramSource ).toLatin1();
    const GLchar* vertSource[1] = { vertSourceArray.data() };
    GLint vertSourceLength[1] = { vertSourceArray.size() };
    glShaderSource( vertShader, 1, vertSource, vertSourceLength );
    glCompileShader( vertShader );

    int status;
    glGetShaderiv( vertShader, GL_COMPILE_STATUS, &status );
    if( status != GL_TRUE )
    {
        char out[500];
        int length = 0;
        glGetShaderInfoLog( vertShader, 500, &length, out );

        setError( QString( out ) );
        glDeleteShader( vertShader );
        return false;
    }

    GLuint fragShader = glCreateShader( GL_FRAGMENT_SHADER );
    QByteArray fragSourceArray = source( FragmentProgramSource ).toLatin1();
    const GLchar* fragSource[1] = { fragSourceArray.data() };
    GLint fragSourceLength[1] = { fragSourceArray.size() };
    glShaderSource( fragShader, 1, fragSource, fragSourceLength );
    glCompileShader( fragShader );

    glGetShaderiv( fragShader, GL_COMPILE_STATUS, &status );
    if( status != GL_TRUE )
    {
        char out[500];
        int length = 0;
        glGetShaderInfoLog( fragShader, 500, &length, out );

        setError( QString( out ) );
        glDeleteShader( vertShader );
        glDeleteShader( fragShader );
        return false;
    }

    d->shaderProgram = glCreateProgram();
    glAttachShader( d->shaderProgram, vertShader );
    glAttachShader( d->shaderProgram, fragShader );
    glLinkProgram( d->shaderProgram );

    glGetProgramiv( d->shaderProgram, GL_LINK_STATUS, &status );
    if( status != GL_TRUE )
    {
        char out[500];
        int length = 0;

        glGetProgramInfoLog( d->shaderProgram, 500, &length, out );

        setError( QString( out ) );
        glDeleteShader( vertShader );
        glDeleteShader( fragShader );
        glDeleteProgram( d->shaderProgram );
        d->shaderProgram = 0;
        return false;
    }

    int count;
    glGetProgramiv( d->shaderProgram, GL_ACTIVE_ATTRIBUTES, &count );
    int maxNameLength;
    glGetProgramiv( d->shaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxNameLength );

    QHash< QString, int > attributes;
    char* buffer = new char[ maxNameLength ];
    for( int i = 0; i < count; ++i )
    {
        int length, size;
        GLenum type;
        glGetActiveAttrib( d->shaderProgram, i, maxNameLength, &length , &size, &type, buffer );
        attributes.insert( QString( buffer ), i );
    }
    delete[] buffer;
    setAttributes( attributes );

    glGetProgramiv( d->shaderProgram, GL_ACTIVE_UNIFORMS, &count );
    glGetProgramiv( d->shaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength );

    QStringList uniformNames;
    buffer = new char[ maxNameLength ];
    for( int i = 0; i < count; ++i )
    {
        int length, size;
        GLenum type;
        glGetActiveUniform( d->shaderProgram, i, maxNameLength, &length , &size, &type, buffer );

        GLint uniformLoc = glGetUniformLocation( d->shaderProgram, buffer );
        if( uniformLoc != -1 )
        {
            QString uniform( buffer );
            uniformNames.append( uniform );
            d->uniforms.insert( uniform, uniformLoc );
        }
    }
    delete[] buffer;
    setUniformNames( uniformNames );

    return true;
}

bool GLXShader::bind()
{
    if( !d->shaderProgram )
        return false;

    if( d->bound )
        return true;

    glUseProgram( d->shaderProgram );

    d->currentTextureUnit = 0;

    QHash< QString, QVariant > unis = uniforms();
    QHash< QString, QVariant >::iterator itr;
    for( itr = unis.begin(); itr != unis.end(); ++itr )
    {
        d->setUniform( d->uniforms.value( itr.key() ), itr.value() );
    }

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

void GLXShader::Private::setUniform( GLint uniform, const QVariant& value )
{
    switch( value.type() )
    {
        case QVariant::UInt:
        case QVariant::Int:
            glUniform1i( uniform, value.toInt() );
            break;
        case 137:
        case QVariant::Double:
            glUniform1f( uniform, value.toFloat() );
            break;
        case QVariant::Color:
        {
            QColor color = value.value<QColor>();
            glUniform4f( uniform, color.red() / 255.f, color.green() / 255.f, color.blue() / 255.f, color.alpha() / 255.f );
            break;
        }
        case QVariant::Vector2D:
        {
            QVector2D vector = value.value<QVector2D>();
            glUniform2f( uniform, vector.x(), vector.y() );
            break;
        }
        case QVariant::Vector3D:
        {
            QVector3D vector = value.value<QVector3D>();
            glUniform3f( uniform, vector.x(), vector.y(), vector.z() );
            break;
        }
        case QVariant::Vector4D:
        {
            QVector4D vector = value.value<QVector4D>();
            glUniform4f( uniform, vector.x(), vector.y(), vector.z(), vector.w() );
            break;
        }
        case QVariant::Quaternion:
        {
            QQuaternion quat = value.value<QQuaternion>();
            glUniform4f( uniform, quat.x(), quat.y(), quat.z(), quat.scalar() );
            break;
        }
        case QVariant::Matrix4x4:
        {
            QMatrix4x4 mat = value.value<QMatrix4x4>();
            float glMatrix[16];
            MathUtils::qmatrixToGLMatrix( mat, glMatrix );
            glUniformMatrix4fv( uniform, 1, false, glMatrix );
            break;
        }
        default:
            Texture* tex = value.value< GluonGraphics::Texture* >();
            if( tex != 0 )
            {
                tex->data()->bind( currentTextureUnit );
                glUniform1i( uniform, currentTextureUnit );
                currentTextureUnit++;
            }
            break;
    }
}

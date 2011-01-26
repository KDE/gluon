/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "material.h"
#include "materialinstance.h"
#include "technique.h"

#include <QDebug>

#include "glheaders.h"
#include <core/gdlhandler.h>
#include <QFile>
#include <QMetaProperty>
#include "backendcapabilities.h"
#include <qtextcodec.h>
#include <qvarlengtharray.h>
#include <QtOpenGL/QGLShaderProgram>

REGISTER_OBJECTTYPE( GluonGraphics, Material )

using namespace GluonGraphics;

class Material::MaterialPrivate
{
    public:
        MaterialPrivate() :
            vertShader( 0 ),
            fragShader( 0 ),
            glProgram( 0 ),
            program( 0 )
        {
        }

        QHash<QString, Technique*> techniques;

        uint vertShader;
        QByteArray vertShaderSource;
        uint fragShader;
        QByteArray fragShaderSource;
        uint glProgram;
        QString languageVersion;

        QHash<QString, MaterialInstance*> instances;

        QGLShaderProgram* program;
};

Material::Material( QObject* parent )
    : GluonObject( parent ),
      d( new MaterialPrivate )
{
    createInstance( "default" );
}

Material::~Material()
{
    delete d;
}

bool Material::load( const QUrl& url )
{
    if( d->program )
    {
        delete d->program;
        d->program = 0;
    }
    d->glProgram = 0;

    if( !url.isValid() )
        return false;

    QFile file( url.toLocalFile() );
    if( !file.open( QIODevice::ReadOnly ) )
        return false;

    QByteArray data = file.readAll();

    QList<GluonObject*> objects = GluonCore::GDLHandler::instance()->parseGDL( data, this );
    if( objects.count() <= 0 )
        return false;

    GluonCore::GluonObject* obj = objects.at( 0 );
    QList<QByteArray> properties = obj->dynamicPropertyNames();
    MaterialInstance* defaultInstance = d->instances.find( "default" ).value();

    foreach( const QByteArray& propertyName, properties )
    {
        if( propertyName == "vertexShader" )
        {
            d->vertShaderSource = obj->property( propertyName ).toByteArray();
        }
        else if( propertyName == "fragmentShader" )
        {
            d->fragShaderSource = obj->property( propertyName ).toByteArray();
        }
        else if( propertyName == "languageVersion" )
        {
            d->languageVersion = obj->property( propertyName ).toString();
        }
        else
        {
            defaultInstance->setProperty( propertyName, obj->property( propertyName ) );
        }
    }

    return true;
}

void Material::build( const QString& name )
{
    if( d->glProgram )
        return;

     if( d->fragShaderSource.isEmpty() || d->vertShaderSource.isEmpty() )
        return;

    QByteArray vertShaderSource;
    QByteArray fragShaderSource;
//     if( BackendCapabilities::type() == BackendCapabilities::BT_OPENGL )
//     {
//         if( d->languageVersion.isEmpty() )
//         {
//             vertShaderSource.append( "#version 110\n" );
//             vertShaderSource.append( "#define lowp\n" );
//             vertShaderSource.append( "#define mediunmp\n" );
//             vertShaderSource.append( "#define highp\n" );
//         }
//     }
//     else if( BackendCapabilities::type() == BackendCapabilities::BT_OPENGLES )
//     {
//         vertShaderSource.append( "#ifndef GL_FRAGMENT_PRECISION_HIGH\n" );
//         vertShaderSource.append( "#define highp mediump\n" );
//         vertShaderSource.append( "#endif\n" );
//     }

    fragShaderSource.append( vertShaderSource );

    vertShaderSource.append( d->vertShaderSource );
    fragShaderSource.append( d->fragShaderSource );

    const char* vertShaderData = vertShaderSource.data();
    const char* fragShaderData = fragShaderSource.data();

    d->program = new QGLShaderProgram();
    d->program->addShaderFromSourceCode( QGLShader::Vertex, vertShaderSource );
    d->program->addShaderFromSourceCode( QGLShader::Fragment, fragShaderSource );
    d->program->link();

    if( !d->program->isLinked() )
    {
        debug( "An error occurred during shader compilation!" );
        debug( d->program->log() );
    }

    //     d->vertShader = glCreateShader( GL_VERTEX_SHADER );
    //     glShaderSource( d->vertShader, 1, &vertShaderData, NULL );
    //     glCompileShader( d->vertShader );
    //
    //     int status;
    //     glGetShaderiv( d->vertShader, GL_COMPILE_STATUS, &status );
    //     if( status != GL_TRUE )
    //     {
    //         char log[500];
    //         glGetShaderInfoLog( d->vertShader, 500, NULL, log );
    //         debug( "An error occured when compiling a vertex shader:\n%1", QString( log ) );
    //     }
    //
    //     d->fragShader = glCreateShader( GL_FRAGMENT_SHADER );
    //     glShaderSource( d->fragShader, 1, &fragShaderData, NULL );
    //     glCompileShader( d->fragShader );
    //
    //     glGetShaderiv( d->fragShader, GL_COMPILE_STATUS, &status );
    //     if( status != GL_TRUE )
    //     {
    //         char log[500];
    //         glGetShaderInfoLog( d->fragShader, 500, NULL, log );
    //         debug( "An error occurred when compiling a fragment shader:\n%1", QString( log ) );
    //     }
    //
    //     d->glProgram = glCreateProgram();
    //     glAttachShader( d->glProgram, d->vertShader );
    //     glAttachShader( d->glProgram, d->fragShader );
    //     glLinkProgram( d->glProgram );
    //
    //     glGetProgramiv( d->glProgram, GL_LINK_STATUS, &status );
    //     if( status != GL_TRUE )
    //     {
    //         char log[500];
    //         glGetProgramInfoLog( d->fragShader, 500, NULL, log );
    //         debug( "An error occurred when linking a program:\n%1", QString( log ) );
    //     }
}

Technique*
Material::technique( const QString& name ) const
{
    return 0;
}

void
Material::addTechnique( Technique* technique )
{

}

void
Material::removeTechnique( const QString& name )
{

}

void
Material::setDefaultTechnique( const QString& name )
{

}

uint
Material::glProgram()
{
    if( !d->program )
        build();

    if( !d->program || !d->program->isLinked() )
        return 0;

    return d->program->programId();
}

MaterialInstance*
Material::createInstance( const QString& name )
{
    MaterialInstance* instance;
    if( !d->instances.contains( name ) )
    {
        instance = new MaterialInstance( this );
        instance->setMaterial( this );
        d->instances.insert( name, instance );
    }
    else
    {
        instance = d->instances.value( name );
    }
    return instance;
}

MaterialInstance*
Material::instance( const QString& name )
{
    if( d->instances.contains( name ) )
        return d->instances.value( name );

    return 0;
}

QHash< QString, QVariant >
Material::uniformList()
{
    QHash<QString, QVariant> uniforms;
    uniforms.insert( "materialColor", Qt::white );
    uniforms.insert( "texture0", "default" );
    return uniforms;
}

#include "material.moc"

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
#include "backendcapabilities.h"
#include "glheaders.h"

#include <core/gdlhandler.h>

#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QMetaProperty>
#include <QtCore/QTextCodec>
#include <QtCore/QVarLengthArray>
#include <QtCore/QTime>

REGISTER_OBJECTTYPE( GluonGraphics, Material )

using namespace GluonGraphics;

class Material::MaterialPrivate
{
    public:
        MaterialPrivate() :
            vertShader( 0 ),
            fragShader( 0 ),
            glProgram( 0 )
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
    d->glProgram = 0;

    if( !url.isValid() )
        return false;

    QList<GluonObject*> objects = GluonCore::GDLHandler::instance()->parseGDL( url, this );
    if( objects.count() <= 0 )
        return false;

    GluonCore::GluonObject* obj = objects.at( 0 );
    QList<QByteArray> properties = obj->dynamicPropertyNames();
    MaterialInstance* defaultInstance = d->instances.find( "default" ).value();

    foreach( const QByteArray & propertyName, properties )
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
    if( BackendCapabilities::type() == BackendCapabilities::BT_OPENGL )
    {
        if( d->languageVersion.isEmpty() )
        {
            vertShaderSource.append( "#version 110\n" );
            vertShaderSource.append( "#define lowp\n" );
            vertShaderSource.append( "#define mediump\n" );
            vertShaderSource.append( "#define highp\n" );
        }
    }
    else if( BackendCapabilities::type() == BackendCapabilities::BT_OPENGLES )
    {
        vertShaderSource.append( "#ifndef GL_FRAGMENT_PRECISION_HIGH\n" );
        vertShaderSource.append( "#define highp mediump\n" );
        vertShaderSource.append( "#endif\n" );
    }

    fragShaderSource.append( vertShaderSource );

    vertShaderSource.append( d->vertShaderSource );
    fragShaderSource.append( d->fragShaderSource );

    const char* vertShaderData = vertShaderSource.data();
    const char* fragShaderData = fragShaderSource.data();

    qDebug() << "VERTEX SHADER CODE:" << d->vertShaderSource;
    qDebug() << "\nFRAGMENT SHADER CODE:" << d->fragShaderSource;

    // Vertex shader compilation process
    d->vertShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( d->vertShader, 1, &vertShaderData, NULL );
    glCompileShader( d->vertShader );
    
    int vertCompiledStatus;
    glGetShaderiv( d->vertShader, GL_COMPILE_STATUS, &vertCompiledStatus );
    if( vertCompiledStatus != GL_TRUE )
    {
        int slog;
        glGetShaderiv( d->vertShader, GL_INFO_LOG_LENGTH, &slog );
        char *log = new char [slog];
        glGetShaderInfoLog( d->vertShader, slog, NULL, log );
        debug( "An error occurred when compiling a vertex shader:\n%1", QString( log ) );
        delete [] log;
    }
    
    // Fragment shader compilation process
    d->fragShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( d->fragShader, 1, &fragShaderData, NULL );
    glCompileShader( d->fragShader );
    
    int fragCompiledStatus;
    glGetShaderiv( d->fragShader, GL_COMPILE_STATUS, &fragCompiledStatus );
    if( fragCompiledStatus != GL_TRUE )
    {
        int slog;
        glGetShaderiv( d->fragShader, GL_INFO_LOG_LENGTH, &slog );
        char *log = new char [slog];
        glGetShaderInfoLog( d->fragShader, slog, NULL, log );
        debug( "An error occurred when compiling a fragment shader:\n%1", QString( log ) );
        delete [] log;
    }
    
    // Link the shaders into a program and then use it
    d->glProgram = glCreateProgram();
    glAttachShader( d->glProgram, d->vertShader );
    glAttachShader( d->glProgram, d->fragShader );
    glLinkProgram( d->glProgram );
    
    int programLinkStatus;
    glGetProgramiv( d->glProgram, GL_LINK_STATUS, &programLinkStatus );
    if( programLinkStatus != GL_TRUE )
    {
        int slog;
        glGetProgramiv( d->glProgram, GL_INFO_LOG_LENGTH, &slog );
        char *log = new char [slog];
        glGetProgramInfoLog( d->fragShader, slog, NULL, log );
        debug( "An error occurred when linking a program:\n%1", QString( log ) );
        delete [] log;
    }
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
    if( !d->glProgram )
        build();

    if( !d->glProgram )
        return 0;

    int linked;

    glGetProgramiv( d->glProgram, GL_LINK_STATUS, &linked );

    if (!linked)
        return 0;

    return d->glProgram;
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
    uniforms.insert( "texture0", GluonCore::GluonObjectFactory::instance()->wrapObject( QString( "GluonEngine::TextureAsset*" ), 0 ) );
    return uniforms;
}

#include "material.moc"

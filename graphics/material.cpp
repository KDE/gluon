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

#include <GL/gl.h>
#include <GL/glext.h>

REGISTER_OBJECTTYPE(GluonGraphics, Material)

using namespace GluonGraphics;

class Material::MaterialPrivate
{
    public:
        MaterialPrivate() { vertShader = 0; fragShader = 0; glProgram = 0; }

        QHash<QString, Technique*> techniques;

        uint vertShader;
        uint fragShader;
        uint glProgram;

        QHash<QString, MaterialInstance*> instances;
};

Material::Material(QObject* parent)
    : GluonObject(parent),
      d(new MaterialPrivate)
{
    createInstance("default");
}

Material::~Material()
{
    delete d;
}

bool Material::load( const QUrl& url )
{
    //Todo: Implement
    return true;
}

void Material::build( const QString& name )
{
    if(d->glProgram)
         return;

    const char* vertShaderSource = "\
uniform mat4 modelViewProj;\
\
attribute vec3 vertex;\
attribute vec4 color;\
attribute vec2 uv0;\
\
varying vec4 out_color;\
varying vec2 out_uv0;\
\
void main()\
{\
    gl_Position = vec4(vertex, 1.0f) * modelViewProj;\
    out_color = color;\
    out_uv0 = uv0;\
}\
";

    const char* fragShaderSource = "\
uniform sampler2D texture0;\
uniform vec4 materialColor;\
\
varying vec4 out_color;\
varying vec2 out_uv0;\
\
void main()\
{\
    vec4 texColor = texture2D(texture0, out_uv0);\
    vec4 color = out_color * materialColor * texColor;\
    color = vec4(color.r, color.g, color.b, texColor.a * materialColor.a);\
    if(color.a <= 0.0)\
        discard;\
    gl_FragColor = color;\
}\
";

    d->vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(d->vertShader, 1, &vertShaderSource, NULL);
    glCompileShader(d->vertShader);

    d->fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(d->fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(d->fragShader);

    d->glProgram = glCreateProgram();
    glAttachShader(d->glProgram, d->vertShader);
    glAttachShader(d->glProgram, d->fragShader);
    glLinkProgram(d->glProgram);
}

Technique*
Material::technique(const QString& name) const
{

}

void
Material::addTechnique(Technique* technique)
{

}

void
Material::removeTechnique(const QString& name)
{

}

void
Material::setDefaultTechnique(const QString& name)
{

}

uint
Material::glProgram()
{
    if(!d->glProgram)
        build();

    return d->glProgram;
}

MaterialInstance*
Material::createInstance(const QString& name)
{
    MaterialInstance* instance;
    if(!d->instances.contains(name))
    {
        instance = new MaterialInstance(this);
        instance->setMaterial(this);
        d->instances.insert(name, instance);
    }
    else
    {
        instance = d->instances.value(name);
    }
    return instance;
}

MaterialInstance*
Material::instance( const QString& name )
{
    if(d->instances.contains(name))
        return d->instances.value(name);

    return 0;
}

QHash< QString, QVariant >
Material::uniformList()
{
    QHash<QString, QVariant> uniforms;
    uniforms.insert("materialColor", Qt::white);
    uniforms.insert("texture0", "default");
    return uniforms;
}

#include "material.moc"

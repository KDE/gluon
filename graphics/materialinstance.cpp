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

#include "materialinstance.h"
#include "material.h"

#include <GL/gl.h>
#include <GL/glext.h>
#include "math.h"
#include "engine.h"
#include "camera.h"
#include "frustum.h"

#include <QtCore/QVariant>
#include <QtGui/QVector2D>
#include <QtGui/QColor>

REGISTER_OBJECTTYPE(GluonGraphics, MaterialInstance)

using namespace GluonGraphics;

class MaterialInstance::MaterialInstancePrivate
{
    public:
        MaterialInstancePrivate() { bound = false; }

        Material * material;

        QHash<QString, int> uniformLocations;
        QHash<QString, int> attributeLocations;

        QHash<QString, QVariant> parameterValues;

        bool bound;
};

MaterialInstance::MaterialInstance(QObject* parent)
    : GluonObject(parent),
      d(new MaterialInstancePrivate)
{

}

MaterialInstance::~MaterialInstance()
{
    delete d;
}

void
MaterialInstance::bind()
{
    glUseProgram(d->material->glProgram());
    d->bound = true;

    for(QHash<QString, QVariant>::iterator itr = d->parameterValues.begin(); itr != d->parameterValues.end(); ++itr)
    {
        setGLUniform(itr.key(), itr.value());
    }
}

void
MaterialInstance::release()
{
    glUseProgram(0);
    d->bound = false;
}

Material*
MaterialInstance::material()
{
    return d->material;
}

void
MaterialInstance::setMaterial( Material* material )
{
    d->material = material;
}

int MaterialInstance::attributeLocation( const QString& attrib )
{
    if(d->attributeLocations.contains(attrib))
        return d->attributeLocations.value(attrib);

    int loc = glGetAttribLocation(d->material->glProgram(), attrib.toUtf8().constData());
    if(loc != -1)
    {
        d->attributeLocations.insert(attrib, loc);
    }

    return loc;
}

int MaterialInstance::uniformLocation( const QString& name)
{
    if(d->uniformLocations.contains(name))
        return d->uniformLocations.value(name);

    int loc = glGetUniformLocation(d->material->glProgram(), name.toUtf8().constData());
    if(loc != -1)
    {
        d->uniformLocations.insert(name, loc);
    }

    return loc;
}

void MaterialInstance::setUniform( const QString& name, const QVariant& value )
{
    if(!d->bound)
    {
        d->parameterValues.insert(name, value);
    }
    else
    {
        setGLUniform(name, value);
    }
}

void
MaterialInstance::setModelViewProjectionMatrix( QMatrix4x4 mvp )
{
    int loc = uniformLocation("modelViewProj");

    float glMatrix[16];
    Math::qmatrixToGLMatrix(mvp, glMatrix);
    glUniformMatrix4fv(loc, 1, false, glMatrix);
}

void
MaterialInstance::setGLUniform( const QString& name, const QVariant& value )
{
    switch(value.type())
    {
        case QVariant::Int:
            glUniform1i( uniformLocation(name), value.toInt());
            break;
        case QVariant::Double:
            glUniform1f( uniformLocation(name), value.toDouble());
            break;
        case QVariant::Color:
        {
            QColor color = value.value<QColor>();
            glUniform4f( uniformLocation(name), color.red() / 255.f, color.green() / 255.f, color.blue() / 255.f, color.alpha() / 255.f);
            break;
        }
        case QVariant::Vector2D:
        {
            QVector2D vector = value.value<QVector2D>();
            glUniform2f( uniformLocation(name), vector.x(), vector.y());
            break;
        }
        case QVariant::Vector3D:
        {
            QVector3D vector = value.value<QVector3D>();
            glUniform3f( uniformLocation(name), vector.x(), vector.y(), vector.z());
            break;
        }
        case QVariant::Vector4D:
        {
            QVector4D vector = value.value<QVector4D>();
            glUniform4f( uniformLocation(name), vector.x(), vector.y(), vector.z(), vector.w());
            break;
        }
    }
    int error = glGetError();
    if(error != GL_NO_ERROR)
        debug(QString("An OpenGL error has occured. GL Error code is: %1").arg(error));
}

#include "materialinstance.moc"

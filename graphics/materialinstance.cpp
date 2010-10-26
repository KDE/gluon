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

#include <QtCore/QVariant>
#include <QtGui/QVector2D>
#include <QtGui/QColor>

#include "math.h"
#include "engine.h"
#include "texture.h"
#include "glheaders.h"

REGISTER_OBJECTTYPE(GluonGraphics, MaterialInstance)

using namespace GluonGraphics;

class MaterialInstance::MaterialInstancePrivate
{
    public:
        MaterialInstancePrivate() { bound = false; }

        Material * material;

        QHash<QString, int> uniformLocations;
        QHash<QString, int> attributeLocations;

        QHash<QString, QVariant> uniformValues;

        QHash<uint, Texture*> textures;

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
    if(!d->material)
        return;

    glUseProgram(d->material->glProgram());
    d->bound = true;

    QList<QByteArray> properties = dynamicPropertyNames();
    foreach(QByteArray prop, properties)
    {
        setGLUniform(prop, property(prop));
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

void
MaterialInstance::setModelViewProjectionMatrix( QMatrix4x4 mvp )
{
    int loc = uniformLocation("modelViewProj");

    float glMatrix[16];
    Math::qmatrixToGLMatrix(mvp, glMatrix);
    glUniformMatrix4fv(loc, 1, false, glMatrix);
}

void
MaterialInstance::setPropertiesFromMaterial()
{
    QHash<QString, QVariant> uniforms = d->material->uniformList();
    for( QHash<QString, QVariant>::iterator pitr = uniforms.begin(); pitr != uniforms.end(); ++pitr )
    {
        setProperty(pitr.key().toUtf8(), pitr.value());
    }
}

void
MaterialInstance::setGLUniform( const QString& name, const QVariant& value )
{
    switch(value.type())
    {
        case QVariant::UInt:
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
        case QVariant::String:
        {
            if(name.contains("texture"))
            {
                GluonGraphics::Texture* texture = GluonGraphics::Engine::instance()->texture(value.toString());
                bindTexture(name, texture);
            }
            break;
        }
        case QVariant::UserType:
        {
            GluonCore::GluonObject* obj = GluonCore::GluonObjectFactory::instance()->wrappedObject(value);
            if(obj && name.contains("texture"))
            {
                GluonGraphics::Texture* texture = GluonGraphics::Engine::instance()->texture(obj->name());

                bindTexture(name, texture);
            }
            break;
        }
        default:
        break;
    }
}

void
MaterialInstance::bindTexture( const QString& name, Texture* tex )
{
    if(!tex)
        return;

    QString uniName = name;
    int id = uniName.replace("texture", "").toInt();

    glActiveTexture(GL_TEXTURE0 + id);
    glBindTexture(GL_TEXTURE_2D, tex->glTexture());
    glUniform1i( uniformLocation(name), id);
}

#include "materialinstance.moc"

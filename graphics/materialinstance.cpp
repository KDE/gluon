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
#include <gluon/graphics/engine.h>
#include "camera.h"
#include "frustum.h"

REGISTER_OBJECTTYPE(GluonGraphics, MaterialInstance)

using namespace GluonGraphics;

class MaterialInstance::MaterialInstancePrivate
{
    public:
        Material * material;

        QHash<QString, int> parameterLocations;
        QHash<QString, int> attributeLocations;
};

MaterialInstance::MaterialInstance(QObject* parent)
    : GluonObject(parent),
      d(new MaterialInstancePrivate)
{

}

MaterialInstance::MaterialInstance( Material* instanceOf )
    : GluonObject( instanceOf ),
      d(new MaterialInstancePrivate)
{
    d->material = instanceOf;
}

MaterialInstance::~MaterialInstance()
{
    delete d;
}

void
MaterialInstance::bind()
{
    glUseProgram(d->material->glProgram());
}

void
MaterialInstance::release()
{
    glUseProgram(0);
}

Material*
MaterialInstance::instanceOf()
{
    return d->material;
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

int MaterialInstance::parameterLocation( const QString& param)
{
    if(d->parameterLocations.contains(param))
        return d->parameterLocations.value(param);

    int loc = glGetUniformLocation(d->material->glProgram(), param.toUtf8().constData());
    if(loc != -1)
    {
        d->parameterLocations.insert(param, loc);
    }

    return loc;
}

void MaterialInstance::setParameter( const QString& param, const QVariant& value )
{
    int loc = parameterLocation(param);

    int size;
    GLenum type;
    glGetActiveUniform(d->material->glProgram(), loc, 0, NULL, &size, &type, NULL);

}

void
MaterialInstance::setModelViewProjectionMatrix( QMatrix4x4 mvp )
{
    int loc = parameterLocation("modelViewProj");

    float glMatrix[16];
    Math::qmatrixToGLMatrix(mvp, glMatrix);
    glUniformMatrix4fv(loc, 1, false, glMatrix);
}


#include "materialinstance.moc"

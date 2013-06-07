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
#include "shader.h"

REGISTER_OBJECTTYPE( GluonGraphics, MaterialInstance )

using namespace GluonGraphics;

class MaterialInstance::Private
{
    public:
        Private() : bound( false ) { }

        Material* material;
        //Shader* shader;

        bool bound;
};

MaterialInstance::MaterialInstance( QObject* parent )
    : GluonObject( parent ), d( new Private )
{
}

MaterialInstance::~MaterialInstance()
{
    delete d;
}

bool
MaterialInstance::bind()
{
    Shader* shader = d->material->shader();
    if( !shader )
        return false;

    QList< QByteArray > dynamicProperties = dynamicPropertyNames();
    foreach( const QByteArray& propertyName, dynamicProperties )
    {
        QVariant prop = property( propertyName );
        GluonCore::GluonObject* obj = GluonCore::GluonObjectFactory::instance()->wrappedObject( prop );
        if( obj )
        {
            QVariant tex = obj->property( "texture" );
            if( tex.isValid() )
            {
                shader->setUniform( propertyName, tex );
                continue;
            }
        }

        shader->setUniform( propertyName, prop );
    }

    return shader->bind();
}

void
MaterialInstance::release()
{
    shader()->release();
    d->bound = false;
}

Material*
MaterialInstance::material() const
{
    return d->material;
}

void MaterialInstance::setMaterial( Material* mat )
{
    d->material = mat;

}

Shader* MaterialInstance::shader() const
{
    return d->material->shader();
}

void MaterialInstance::setShader( Shader* shader )
{
    //d->shader = shader;
}

 

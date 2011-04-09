/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "prefabinstance.h"
#include "component.h"
#include <QMetaProperty>

REGISTER_OBJECTTYPE( GluonEngine, PrefabInstance )

using namespace GluonEngine;

class PrefabInstance::Private
{
public:
    Private()
        : prefabLink(0)
    {
    }

    Prefab* prefabLink;
};

PrefabInstance::PrefabInstance(QObject* parent)
    : d( new Private )
{

}

PrefabInstance::PrefabInstance(const PrefabInstance& other)
    : d( other.d )
{

}

PrefabInstance::~PrefabInstance()
{
    if(d->prefabLink)
        d->prefabLink->removeInstance(this);

    delete(d);
}

Prefab* PrefabInstance::prefabLink() const
{
    return d->prefabLink;
}

void PrefabInstance::setPrefabLink(Prefab* newPrefab)
{
    // First, set up the new prefab linkage
    if(d->prefabLink)
        d->prefabLink->removeInstance(this);
    d->prefabLink = newPrefab;
    if(d->prefabLink)
    {
        d->prefabLink->addInstance(this);

        // Then (if the new prefab is valid, and we are not loading the containing scene from disk)
        // remove the old children, and clone from the new prefab
        if(isInitialized())
        {
            // Clear all children out
            QObjectList childObjects = children();
            foreach(QObject* child, childObjects)
            {
                delete(child);
            }
            // Clear out all the existing dynamic properties (to ensure we're actually clean)
            QList<QByteArray> propertyNames = dynamicPropertyNames();
            foreach( const QByteArray & propName, propertyNames )
            {
                setProperty(propName, QVariant());
            }

            // Clone the property values from the gameObject in the prefab
            GameObject* gobj = d->prefabLink->gameObject();
            propertyNames = gobj->dynamicPropertyNames();
            foreach( const QByteArray & propName, propertyNames )
            {
                setProperty(propName, gobj->property(propName));
            }

            const QMetaObject* metaobject = gobj->metaObject();
            int count = metaobject->propertyCount();
            for( int i = 0; i < count; ++i )
            {
                QMetaProperty metaproperty = metaobject->property( i );
                const QString theName( metaproperty.name() );
                if( theName == "objectName" || !metaproperty.isWritable() )
                    continue;
                setProperty( theName.toUtf8(), gobj->property( theName.toUtf8() ) );
            }

            // Clone all the GameObject children
            const int childCount = gobj->childCount();
            if(childCount > 0)
            {
                for(int i = 0; i < childCount; ++i)
                {
                    // GameObject* childGobj = gobj->childGameObject(i);
                    // Clone this GameObject as a PrefabInstanceChild...
                }
            }

            // Clone all the Components
            foreach(Component* cmp, gobj->components())
            {
                cmp->clone(this);
            }
        }
    }
}

#include "prefabinstance.moc"

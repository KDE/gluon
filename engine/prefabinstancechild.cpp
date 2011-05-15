/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "prefabinstancechild.h"

#include "prefabinstance.h"
#include <QMetaProperty>
#include "component.h"

REGISTER_OBJECTTYPE( GluonEngine, PrefabInstanceChild )

using namespace GluonEngine;

class PrefabInstanceChild::Private
{
};

PrefabInstanceChild::PrefabInstanceChild( QObject* parent )
{

}

PrefabInstanceChild::PrefabInstanceChild( const PrefabInstanceChild& other )
{

}

PrefabInstanceChild::~PrefabInstanceChild()
{

}

void PrefabInstanceChild::cloneFromGameObject(const GluonEngine::GameObject* gameObject)
{

    // Clear out all the existing dynamic properties (to ensure we're actually clean)
    QList<QByteArray> propertyNames = dynamicPropertyNames();
    foreach( const QByteArray & propName, propertyNames )
    {
        setProperty( propName, QVariant() );
    }
    // Clone the property values from the passed GameObject
    propertyNames = gameObject->dynamicPropertyNames();
    foreach( const QByteArray & propName, propertyNames )
    {
        setProperty( propName, gameObject->property( propName ) );
    }

    const QMetaObject* metaobject = gameObject->metaObject();
    int count = metaobject->propertyCount();
    for( int i = 0; i < count; ++i )
    {
        QMetaProperty metaproperty = metaobject->property( i );
        const QString theName( metaproperty.name() );
        if( theName == "objectName" || !metaproperty.isWritable() )
            continue;
        setProperty( theName.toUtf8(), gameObject->property( theName.toUtf8() ) );
    }
    
    // Clone all the GameObject children
    const int childCount = gameObject->childCount();
    if( childCount > 0 )
    {
        for( int i = 0; i < childCount; ++i )
        {
            GameObject* childGobj = gameObject->childGameObject(i);
            // Clone this GameObject as a PrefabInstanceChild...
            PrefabInstanceChild* newChild = new PrefabInstanceChild(this);
            newChild->cloneFromGameObject(childGobj);
        }
    }

    // Clone all the Components
    foreach( Component* cmp, gameObject->components() )
    {
        cmp->clone( this );
    }
}

PrefabInstance* PrefabInstanceChild::parentInstance()
{
    GameObject* theParent = this->parentGameObject();

    while(theParent != 0 && !qobject_cast< GluonEngine::PrefabInstance* >(theParent))
        theParent = theParent->parentGameObject();

    return qobject_cast< GluonEngine::PrefabInstance* >(theParent);
}

#include "prefabinstancechild.moc"

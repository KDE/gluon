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
public:
    Private(PrefabInstanceChild* qo = 0) : q(qo), linkedGameObject(0) {};
    Private(const Private& other) : q(other.q), linkedGameObject(other.linkedGameObject) {};
    ~Private() {};

    PrefabInstanceChild* q;
    GameObject* linkedGameObject;
};

PrefabInstanceChild::PrefabInstanceChild( QObject* parent )
    : GameObject(parent)
    , d( new Private(this) )
{
}

PrefabInstanceChild::PrefabInstanceChild( const PrefabInstanceChild& other )
    : d( new Private() )
{
    *d = *other.d;
}

PrefabInstanceChild::~PrefabInstanceChild()
{

}

void PrefabInstanceChild::cloneFromGameObject(GluonEngine::GameObject* gameObject)
{
    d->linkedGameObject = gameObject;
    Prefab::cloneObjectProperties(gameObject, this);

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
        Prefab::cloneObjectProperties( cmp, cmp->clone( this ) );
    }
}

PrefabInstance* PrefabInstanceChild::parentInstance()
{
    GameObject* theParent = this->parentGameObject();

    while(theParent != 0 && !qobject_cast< GluonEngine::PrefabInstance* >(theParent))
        theParent = theParent->parentGameObject();

    return qobject_cast< GluonEngine::PrefabInstance* >(theParent);
}

void PrefabInstanceChild::resetProperties()
{
    Prefab::cloneObjectProperties(d->linkedGameObject, this);

    QList<QObject*> childObjects = d->linkedGameObject->children();
    if( childObjects.count() > 0 )
    {
        for( int i = 0; i < childObjects.count(); ++i )
        {
            if( qobject_cast<PrefabInstanceChild*>(child(i)) )
            {
                qobject_cast<PrefabInstanceChild*>( child(i) )->resetProperties();
            }
            else if( qobject_cast<Component*>(child(i)) )
            {
                Prefab::cloneObjectProperties( d->linkedGameObject->child(i), child(i) );
            }
        }
    }
}

void PrefabInstanceChild::setName(const QString& newName)
{
    Q_UNUSED(newName);
}

void PrefabInstanceChild::addChild(GluonCore::GluonObject* child)
{
    connect(child, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    GluonEngine::GameObject::addChild(child);
}

void PrefabInstanceChild::addChildAt(GluonCore::GluonObject* child, int position)
{
    connect(child, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    GluonCore::GluonObject::addChildAt(child, position);
}

bool PrefabInstanceChild::removeChild(GluonCore::GluonObject* child)
{
    disconnect(child, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    return GluonEngine::GameObject::removeChild(child);
}

void PrefabInstanceChild::addComponent(Component* addThis)
{
    connect(addThis, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    GluonEngine::GameObject::addComponent(addThis);
}

bool PrefabInstanceChild::removeComponent(Component* removeThis)
{
    connect(removeThis, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    return GluonEngine::GameObject::removeComponent(removeThis);
}

void PrefabInstanceChild::childNameChanged(const QString& oldName, const QString& newName)
{
    // This ensures that children (in particular this means Components) don't get renamed in instances
    GluonCore::GluonObject* from = qobject_cast<GluonCore::GluonObject*>( sender() );
    if(from && oldName != newName)
        from->setName(oldName);
}

#include "prefabinstancechild.moc"

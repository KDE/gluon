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
#include "component.h"

REGISTER_OBJECTTYPE( GluonEngine, PrefabInstanceChild )

using namespace GluonEngine;

class PrefabInstanceChild::Private
{
public:
    Private(PrefabInstanceChild* qo = 0)
        : q( qo )
        , linkedGameObject( 0 )
        , instantiationCompleted( false )
    {};
    Private(const Private& other)
        : q( other.q )
        , linkedGameObject( other.linkedGameObject )
        , instantiationCompleted( other.instantiationCompleted )
    {};
    ~Private() {};

    PrefabInstanceChild* q;
    GameObject* linkedGameObject;
    bool instantiationCompleted;
};

PrefabInstanceChild::PrefabInstanceChild( QObject* parent )
    : GameObject(parent)
    , d( new Private(this) )
{
}

PrefabInstanceChild::~PrefabInstanceChild()
{
    delete d;
}

void PrefabInstanceChild::cloneFromGameObject(GluonEngine::GameObject* gameObject)
{
    DEBUG_FUNC_NAME
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
            PrefabInstanceChild* newChild = new PrefabInstanceChild();
            addChild(newChild);
            newChild->cloneFromGameObject(childGobj);
        }
    }

    // Clone all the Components
    foreach( Component* cmp, gameObject->components() )
    {
        cmp->clone(this);
        //Prefab::cloneObjectProperties( cmp, cmpClone );
        DEBUG_TEXT2("Completed copy of %1", cmp->name());
    }
    d->instantiationCompleted = true;
    DEBUG_TEXT2("Completed copy of %1", name());
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

void PrefabInstanceChild::addChild(GameObject* child)
{
    connect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    GluonEngine::GameObject::addChild(child);
}

void PrefabInstanceChild::addChild(GluonCore::GluonObject* child)
{
    connect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    GluonEngine::GameObject::addChild(child);
}

void PrefabInstanceChild::addChildAt(GluonCore::GluonObject* child, int position)
{
    connect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    GluonCore::GluonObject::addChildAt(child, position);
}

bool PrefabInstanceChild::removeChild(GameObject* child)
{
    disconnect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    return GluonEngine::GameObject::removeChild(child);
}

bool PrefabInstanceChild::removeChild(GluonCore::GluonObject* child)
{
    disconnect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    return GluonEngine::GameObject::removeChild(child);
}

void PrefabInstanceChild::addComponent(Component* addThis)
{
    connect(addThis, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    GluonEngine::GameObject::addComponent(addThis);
}

bool PrefabInstanceChild::removeComponent(Component* removeThis)
{
    connect(removeThis, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    return GluonEngine::GameObject::removeComponent(removeThis);
}

void PrefabInstanceChild::childNameChanged(const QString& oldName, const QString& newName)
{
    if(d->instantiationCompleted == false)
        return;
    if(oldName == newName)
        return;
    // This ensures that children (in particular this means Components) don't get renamed in instances
    GluonCore::GluonObject* from = qobject_cast<GluonCore::GluonObject*>( sender() );
    if(from)
        from->setName(oldName);
}

#include "prefabinstancechild.moc"

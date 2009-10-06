/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "gameobject.h"
#include "gameobjectprivate.h"
#include "component.h"

using namespace Gluon;

GameObject::GameObject(QObject * parent)
    : GluonObject(parent)
{
    d = new GameObjectPrivate;
}

GameObject::GameObject(const GameObject &other, QObject * parent)
    : GluonObject(parent)
    , d(other.d)
{
}

GameObject::~GameObject()
{
}

GameObject *
GameObject::instantiate()
{
    return new GameObject(this);
}

void
GameObject::Start()
{
    foreach(Component * component, d->components)
        component->Start();
    
    foreach(GameObject * child, d->children)
        child->Start();
}

void
GameObject::Update(int elapsedMilliseconds)
{
    foreach(Component * component, d->components)
        component->Update(elapsedMilliseconds);
    
    foreach(GameObject * child, d->children)
        child->Update(elapsedMilliseconds);
}

void
GameObject::Draw(int timeLapse)
{
    foreach(Component * component, d->components)
        component->Draw(timeLapse);
    
    foreach(GameObject * child, d->children)
        child->Draw(timeLapse);
}

void
GameObject::RunCommand(QString functionName)
{
#warning TODO: Implement - QMetaObject::invokeMethod does lots of magic, and we really ought to support it all... postponing implementation for a little while until the rest is complete
}

void
GameObject::RunCommandInChildren(QString functionName)
{
    foreach(GameObject * child, d->children)
        child->RunCommand(functionName);
}

// ----------------------------------------------------------------------------
// Component management

Component *
GameObject::findComponent(QString name)
{
    Component * found = 0;
    foreach(Component * component, d->components)
    {
        if(component->name() == name)
        {
            found = component;
            break;
        }
    }
    return found;
}

Component *
GameObject::findComponentByType(QString typeName)
{
    Component * found = 0;
    const QMetaObject * metaObject;
    foreach(Component * component, d->components)
    {
        metaObject = component->metaObject();
        if(metaObject)
        {
            if(metaObject->className() == typeName)
            {
                found = component;
                break;
            }
        }
    }
    return found;
}

Component *
GameObject::findComponentInChildren(QString name)
{
    Component * found = 0;
    foreach(GameObject * child, d->children)
    {
        found = child->findComponent(name);
        if(found)
            break;
        found = child->findComponentInChildren(name);
        if(found)
            break;
    }
    return found;
}

Component *
GameObject::findComponentInChildrenByType(QString typeName)
{
    Component * found = 0;
    QMetaObject * metaObject;
    foreach(GameObject * child, d->children)
    {
        found = child->findComponentByType(typeName);
        if(found)
            break;
        found = child->findComponentInChildrenByType(typeName);
        if(found)
            break;
    }
    return found;
}

QList<Component *>
GameObject::findComponentsInChildren(QString name)
{
    QList<Component *> found;
    Component * tempFound;
    foreach(GameObject * child, d->children)
    {
        tempFound = child->findComponent(name);
        if(tempFound)
            found.append(tempFound);
        found.append(child->findComponentInChildren(name));
    }
    return found;
}

QList<Component *>
GameObject::findComponentsInChildrenByType(QString typeName)
{
    QList<Component *> found;
    Component * tempFound;
    foreach(GameObject * child, d->children)
    {
        tempFound = child->findComponentByType(typeName);
        if(tempFound)
            found.append(tempFound);
        found.append(child->findComponentsInChildrenByType(typeName));
    }
    return found;
}

void
GameObject::addComponent(Component * addThis)
{
    d->components.append(addThis);
}

bool
GameObject::removeComponent(Component * removeThis)
{
    return d->components.removeOne(removeThis);
}

// ----------------------------------------------------------------
// GameObject tree management

GameObject *
GameObject::child(int index)
{
    return d->children.at(index);
}

GameObject *
GameObject::child(QString name)
{
    GameObject * found = 0;
    foreach(GameObject * child, d->children)
    {
        if(child->name() == name)
        {
            found = child;
            break;
        }
    }
    return found;
}

void
GameObject::addChild(GameObject * addThis)
{
    d->children.append(addThis);
}

bool
GameObject::removeChild(GameObject * removeThis)
{
    return d->children.removeOne(removeThis);
}

void
GameObject::setParentGameObject(GameObject * newParent)
{
    // Clean up... We shouldn't be a child of more than one GameObject, or things will BLOW UP
    if(d->parentGameObject)
        d->parentGameObject->removeChild(this);

    // We could potentially be setting ourselves as a top level GameObject... Don't die!
    if(newParent)
        newParent->addChild(this);
    
    d->parentGameObject = newParent;
}

GameObject *
GameObject::parentGameObject()
{
    return d->parentGameObject;
}

// ----------------------------------------------------------------------------
// Property getter-setters

void
GameObject::setDescription(QString newDescription)
{
    d->description = newDescription;
}

QString
GameObject::description() const
{
    return d->description;
}

void
GameObject::setPosition(Eigen::Vector3d newPosition)
{
    d->position = newPosition;
}

Eigen::Vector3d
GameObject::position() const
{
    return d->position;
}

void
GameObject::setScale(Eigen::Vector3d newScale)
{
    d->scale = newScale;
}

Eigen::Vector3d
GameObject::scale() const
{
    return d->scale;
}

void
GameObject::setRotationAxis(Eigen::Vector3d newRotationAxis)
{
    d->rotationAxis = newRotationAxis;
}

Eigen::Vector3d
GameObject::rotationAxis() const
{
    return d->rotationAxis;
}

void
GameObject::setRotation(float newRotation)
{
    d->rotation = newRotation;
}

float
GameObject::rotation() const
{
    return d->rotation;
}
#include "gameobject.moc"

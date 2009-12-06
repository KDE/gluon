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
#include "debughelper.h"

REGISTER_OBJECTTYPE(Gluon,GameObject)

using namespace Gluon;
using namespace Eigen;

GameObject::GameObject(QObject * parent)
    : GluonObject(parent)
{
    d = new GameObjectPrivate;
    updateTransform();
}

GameObject::GameObject(const GameObject &other, QObject * parent)
    : GluonObject(parent)
    , d(other.d)
{
    updateTransform();
}

GameObject::~GameObject()
{
}


GluonObject* GameObject::instantiate()
{
    return new GameObject(this);
}

void
GameObject::sanitize()
{
    if(this->parent())
    {
        if(this->parent()->metaObject())
        {
            if(QString::compare(this->parent()->metaObject()->className(), "GameObject"))
            {
                GameObject * theParent = qobject_cast<GameObject*>(this->parent());
                if(theParent)
                {
                    theParent->addChild(this);
                }
            }
        }
    }
    GluonObject::sanitize();
}

void
GameObject::start()
{
    foreach(Component * component, d->components)
        if(component->enabled())
            component->start();

    foreach(GameObject * child, d->children)
        child->start();
}

void
GameObject::update(int elapsedMilliseconds)
{
    //DEBUG_FUNC_NAME
    //DEBUG_TEXT(QString("Updating GameObject %2 with %1 components").arg(d->components.count()).arg(this->fullyQualifiedName()))
    foreach(Component * component, d->components)
        if(component->enabled())
            component->update(elapsedMilliseconds);

    //DEBUG_TEXT(QString("Updating %1 children").arg(d->children.count()))
    foreach(GameObject * child, d->children)
        child->update(elapsedMilliseconds);
}

void
GameObject::draw(int timeLapse)
{
    foreach(Component * component, d->components)
        if(component->enabled())
            component->draw(timeLapse);

    foreach(GameObject * child, d->children)
        child->draw(timeLapse);
}

void
GameObject::runCommand(const QString &functionName)
{
#warning TODO: Implement - QMetaObject::invokeMethod does lots of magic, and we really ought to support it all... postponing implementation for a little while until the rest is complete
}

void
GameObject::runCommandInChildren(const QString &functionName)
{
    foreach(GameObject * child, d->children)
        child->runCommand(functionName);
}

// ----------------------------------------------------------------------------
// Component management

Component *
GameObject::findComponent(const QString &name) const
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
GameObject::findComponentByType(const QString &typeName) const
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
GameObject::findComponentInChildren(const QString &name) const
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
GameObject::findComponentInChildrenByType(const QString &typeName) const
{
    Component * found = 0;
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
GameObject::findComponentsInChildren(const QString &name) const
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
GameObject::findComponentsInChildrenByType(const QString &typeName) const
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
    if(!d->components.contains(addThis))
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
GameObject::childGameObject(int index) const
{
    return d->children.at(index);
}

GameObject *
GameObject::childGameObject(const QString &name) const
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

void GameObject::addChild(GluonObject* child)
{
    Gluon::GluonObject::addChild(child);
}

void
GameObject::addChild(GameObject * addThis)
{
    if(!d->children.contains(addThis))
    {
        d->children.append(addThis);
        addThis->d->parentGameObject = this;
    }
}

bool
GameObject::removeChild(GameObject * removeThis)
{
    removeThis->d->parentGameObject = 0;
    return d->children.removeOne(removeThis);
}

bool GameObject::removeChild(GluonObject* child)
{
    return GluonObject::removeChild(child);
}

int
GameObject::childCount() const
{
    return d->children.count();
}

int
GameObject::childIndex(GameObject* child) const
{
    return d->children.indexOf(child);
}

void
GameObject::setParentGameObject(GameObject * newParent)
{
    //Do nothing if the new parent is the same as the old one.
    if(d->parentGameObject == newParent) return;

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
GameObject::setDescription(const QString &newDescription)
{
    d->description = newDescription;
}

QString
GameObject::description() const
{
    return d->description;
}

void
GameObject::setPosition(Vector3f newPosition)
{
    d->position = newPosition;
   
    Vector3f parentPosition(0,0,0);
    if(parentGameObject())
        parentPosition = parentGameObject()->positionGlobal();
    d->positionGlobal = parentPosition + newPosition;
    
    updateTransform();
}

Vector3f
GameObject::position() const
{
    return d->position;
}

void
GameObject::setScale(Vector3f newScale)
{
    d->scale = newScale;
    
    Vector3f parentScale(0,0,0);
    if(parentGameObject())
        parentScale = parentGameObject()->scale();
    d->scaleGlobal = parentScale + newScale;
    
    updateTransform();
}

Vector3f
GameObject::scale() const
{
    return d->scale;
}

void
GameObject::setRotationAxis(Vector3f newRotationAxis)
{
    d->rotationAxis = newRotationAxis;
    
    Vector3f parentRotationAxis(0,0,0);
    if(parentGameObject())
        parentRotationAxis = parentGameObject()->rotationAxis();
    d->rotationAxisGlobal = parentRotationAxis + newRotationAxis;
    
    updateTransform();
}

Vector3f
GameObject::rotationAxis() const
{
    return d->rotationAxis;
}

void
GameObject::setRotation(float newRotation)
{
    d->rotation = newRotation;
    
    float parentRotation = 0;
    if(parentGameObject())
        parentRotation = parentGameObject()->rotation();
    d->rotationGlobal = parentRotation + newRotation;
    
    updateTransform();
}

float
GameObject::rotation() const
{
    return d->rotation;
}

Vector3f
GameObject::positionGlobal() const
{
    return d->positionGlobal;
}

void
GameObject::setPositionGlobal(Vector3f newPositionGlobal)
{
    d->positionGlobal = newPositionGlobal;
    
    Vector3f parentPosition(0,0,0);
    if(parentGameObject())
        parentPosition = parentGameObject()->positionGlobal();
    d->position = newPositionGlobal - parentPosition;
    
    updateTransform();
}

Vector3f
GameObject::scaleGlobal() const
{
    return d->scaleGlobal;
}

void
GameObject::setScaleGlobal(Vector3f newScaleGlobal)
{
    d->scaleGlobal = newScaleGlobal;
    
    Vector3f parentScaleGlobal(0,0,0);
    if(parentGameObject())
        parentScaleGlobal = parentGameObject()->scaleGlobal();
    d->scale = newScaleGlobal - parentScaleGlobal;
    
    updateTransform();
}

Vector3f
GameObject::rotationAxisGlobal() const
{
    return d->rotationAxisGlobal;
}

void
GameObject::setRotationAxisGlobal(Vector3f newRotationAxisGlobal)
{
    d->rotationAxisGlobal = newRotationAxisGlobal;
    
    Vector3f parentRotationAxisGlobal(0,0,0);
    if(parentGameObject())
        parentRotationAxisGlobal = parentGameObject()->rotationAxisGlobal();
    d->rotationAxis = newRotationAxisGlobal - parentRotationAxisGlobal;
    
    updateTransform();
}

float
GameObject::rotationGlobal() const
{
    return d->rotationGlobal;
}

void
GameObject::setRotationGlobal(float newRotationGlobal)
{
    d->rotationGlobal = newRotationGlobal;
    
    float parentRotationGlobal = 0;
    if(parentGameObject())
        parentRotationGlobal = parentGameObject()->rotationGlobal();
    d->rotationGlobal = newRotationGlobal - parentRotationGlobal;
    
    updateTransform();
}

void
GameObject::updateTransform()
{
    // Reset the transform matrix to the new values of position, scale and rotation
    d->transformMatrix;
    
    if(parentGameObject())
        d->transformMatrix = d->transformMatrix * parentGameObject()->transform();
    
    // Finally, update the child objects' position
    foreach(QObject *child, children())
    {
        GameObject *theChild = qobject_cast<GameObject*>(child);
        if(theChild)
        {
            theChild->updateTransformFromParent(d->transformMatrix);
        }
    }
}

void
GameObject::updateTransformFromParent(Eigen::Transform<float, 3> parentTransform)
{
    // Find new values according to change between old and new transformMatrix
    parentTransform;
    // Set the new values directly (without passing set*), it's expensive enough already
    
    // Finally, update the child objects' position
    foreach(QObject *child, children())
    {
        GameObject *theChild = qobject_cast<GameObject*>(child);
        if(theChild)
            theChild->updateTransformFromParent(d->transformMatrix);
    }
}

Transform<float, 3>
GameObject::transform() const
{
    return d->transformMatrix;
}

#include "gameobject.moc"

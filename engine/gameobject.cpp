/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "gameobject.h"
#include "gameobjectprivate.h"
#include "component.h"
#include "core/debughelper.h"
#include "game.h"

REGISTER_OBJECTTYPE(GluonEngine, GameObject)

using namespace GluonEngine;

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

void
GameObject::sanitize()
{
    if (this->parent())
    {
        if (this->parent()->metaObject())
        {
            if (QString::compare(this->parent()->metaObject()->className(), "GameObject"))
            {
                GameObject * theParent = qobject_cast<GameObject*>(this->parent());
                if (theParent)
                {
                    theParent->addChild(this);
                }
            }
        }
    }
    GluonObject::sanitize();
}

void 
GameObject::initialize()
{
    const int componentCount = d->components.count();
    int i = 0;
    for(i; i < componentCount; ++i)
        if (d->components.at(i)->enabled())
            d->components.at(i)->initialize();

    const int childCount = d->children.count();
    for(i = 0; i < childCount; ++i)
        d->children.at(i)->initialize();
}

void
GameObject::start()
{
    const int componentCount = d->components.count();
    int i = 0;
    for(i; i < componentCount; ++i)
        if (d->components.at(i)->enabled())
            d->components.at(i)->start();

    const int childCount = d->children.count();
    for(i = 0; i < childCount; ++i)
        d->children.at(i)->start();
}

void
GameObject::update(int elapsedMilliseconds)
{
    if(!d->enabled)
        return;
    
    //Remove all objects that were marked to destroy last update
    const int deleteCount = d->objectsToDelete.count();
    int i = 0;

    for(i = 0; i < deleteCount; ++i)
    {
        GameObject* obj = d->objectsToDelete.at(i);
        removeChild(obj);
        obj->stop();
        obj->cleanup();
        delete obj;        
    }
    
    d->objectsToDelete.clear();
    
    //Update all components
    const int componentCount = d->components.count();
    for(i = 0; i < componentCount; ++i)
        if (d->components.at(i)->enabled())
            d->components.at(i)->update(elapsedMilliseconds);

    //Update all children
    const int childCount = d->children.count();
    for(i = 0; i < childCount; ++i)
        d->children.at(i)->update(elapsedMilliseconds);
}

void
GameObject::draw(int timeLapse)
{
    if(!d->enabled)
        return;
    
    const int componentCount = d->components.count();
    int i = 0;
    for(; i < componentCount; ++i)
        if (d->components.at(i)->enabled())
            d->components.at(i)->draw(timeLapse);

    const int childCount = d->children.count();
    for(i = 0; i < childCount; ++i)
        d->children.at(i)->draw(timeLapse);
}

void GameObject::stop()
{
    const int componentCount = d->components.count();
    int i = 0;
    for(i; i < componentCount; ++i)
        if (d->components.at(i)->enabled())
            d->components.at(i)->stop();

    const int childCount = d->children.count();
    for(i = 0; i < childCount; ++i)
        d->children.at(i)->stop();
}

void 
GameObject::cleanup()
{
    const int componentCount = d->components.count();
    int i = 0;
    for(i; i < componentCount; ++i)
        if (d->components.at(i)->enabled())
            d->components.at(i)->cleanup();

    const int childCount = d->children.count();
    for(i = 0; i < childCount; ++i)
        d->children.at(i)->cleanup();
}

void GameObject::destroy()
{
    parentGameObject()->removeLater(this);
}

void GameObject::removeLater(GameObject *remove)
{
    d->objectsToDelete.append(remove);
}

void
GameObject::runCommand(const QString &functionName)
{
    #ifdef __GNUC__
    #warning TODO: Implement - QMetaObject::invokeMethod does lots of magic, and we really ought to support it all... postponing implementation for a little while until the rest is complete
    #endif
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
        if (component->name() == name)
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
        if (metaObject)
        {
            if (metaObject->className() == typeName)
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
        if (found)
            break;
        found = child->findComponentInChildren(name);
        if (found)
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
        if (found)
            break;
        found = child->findComponentInChildrenByType(typeName);
        if (found)
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
        if (tempFound)
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
        if (tempFound)
            found.append(tempFound);
        found.append(child->findComponentsInChildrenByType(typeName));
    }
    return found;
}

void
GameObject::addComponent(Component * addThis)
{
    if (addThis)
    {
        if (!d->components.contains(addThis))
        {
            d->components.append(addThis);
            addThis->setParent(this);
            addThis->setGameObject(this);
            addThis->setName(addThis->name());
        }
    }
    else
    {
        DEBUG_BLOCK
        DEBUG_TEXT("Attempting to add a null component");
    }
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
        if (child->name() == name)
        {
            found = child;
            break;
        }
    }
    return found;
}

void GameObject::addChild(GluonObject* child)
{
    if(qobject_cast<GameObject*>(child))
        addChild(qobject_cast<GameObject*>(child));
    else
        GluonCore::GluonObject::addChild(child);
}

void
GameObject::addChild(GameObject * addThis)
{
    if (!addThis)
    {
        DEBUG_BLOCK
        DEBUG_TEXT(QString("Fail-add! you're trying to add a NULL GameObject"));
    }
    else if (!d->children.contains(addThis))
    {
        d->children.append(addThis);

        if (addThis->d->parentGameObject)
            addThis->d->parentGameObject->removeChild(addThis);

        addThis->d->parentGameObject = this;
        GluonCore::GluonObject::addChild(addThis);
    }
}

void
GameObject::addChildAt(GameObject * addThis, int index)
{
    if (!addThis || index >= d->children.count())
    {
        DEBUG_BLOCK
        DEBUG_TEXT(QString("Fail-add! you're trying to add a NULL GameObject or specified an index that is out of range."));
    }
    else if (!d->children.contains(addThis))
    {
        d->children.insert(index, addThis);

        if (addThis->d->parentGameObject)
            addThis->d->parentGameObject->removeChild(addThis);

        addThis->d->parentGameObject = this;
        GluonCore::GluonObject::addChild(addThis);
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
    if (d->parentGameObject == newParent)
        return;

    // Clean up... We shouldn't be a child of more than one GameObject, or things will BLOW UP
    if (d->parentGameObject)
        d->parentGameObject->removeChild(this);

    // We could potentially be setting ourselves as a top level GameObject... Don't die!
    if (newParent)
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

bool
GameObject::enabled() const
{
    return d->enabled;
}

void
GameObject::setEnabled(bool newEnabled)
{
    d->enabled = newEnabled;
}

//// Translation ////

QVector3D
GameObject::position() const
{
    return d->position;
}

QVector3D
GameObject::worldPosition() const
{
    return d->worldPosition;
}

void
GameObject::setPosition(const QVector3D& newPosition)
{
    d->position = newPosition;

    d->transformInvalidated = true;
    updateTransform();
}

void GameObject::setPosition(float x, float y, float z)
{
    setPosition(QVector3D(x, y, z));
}

void
GameObject::translate(const QVector3D& translation, GameObject::TransformSpace ts)
{
    if(ts == TS_LOCAL)
    {
        QVector3D trans = d->orientation.rotatedVector(translation);
        trans = trans * d->scale;
        setPosition(position() + trans);
    }
    else
    {
        #ifdef __GNUC__
        #warning This probably needs fixing to account for world scale/orientation
        #endif
        QVector3D trans = d->worldOrientation.rotatedVector(translation);
        trans = trans * d->worldScale;
        setPosition(position() + trans);
    }
}

void
GameObject::translate(float x, float y, float z, GameObject::TransformSpace ts)
{
    translate(QVector3D(x, y, z), ts);
}

//// Scaling ////

QVector3D
GameObject::scale() const
{
    return d->scale;
}

QVector3D
GameObject::worldScale() const
{
    return d->worldScale;
}

void
GameObject::setScale(const QVector3D& newScale)
{
    d->scale = newScale;

    d->transformInvalidated = true;
    updateTransform();
}

void GameObject::setScale(float x, float y, float z)
{
    setScale(QVector3D(x, y, z));
}

void GameObject::scaleRelative(QVector3D scaling, GameObject::TransformSpace ts)
{
    if(ts == TS_LOCAL)
    {
        setScale(scale() + scaling);
    }
    else
    {
        setScale((worldScale() + scaling) - scale());
    }
}

void GameObject::scaleRelative(float x, float y, float z, GameObject::TransformSpace ts)
{
    scaleRelative(QVector3D(x, y, z), ts);
}

//// Orientation ////

QQuaternion GameObject::orientation() const
{
    return d->orientation;
}

QQuaternion
GameObject::worldOrientation() const
{
    return d->worldOrientation;
}

void GameObject::setOrientation(const QQuaternion& newOrientation)
{
    d->orientation = newOrientation;

    d->transformInvalidated = true;
    updateTransform();
}

void GameObject::orient(QQuaternion rotation, GameObject::TransformSpace ts)
{
    if(ts == TS_LOCAL)
    {
        setOrientation(orientation() * rotation);
    }
    else
    {
        //setOrientation((worldOrientation() * rotation) / orientation());
    }
}

void GameObject::rotate(float angle, const QVector3D& axis, GameObject::TransformSpace ts)
{
    QQuaternion orientation = QQuaternion::fromAxisAndAngle(axis, angle);
    orient(orientation, ts);
}

void GameObject::updateTransform()

{
    if (!d->transformInvalidated) return;

    GameObject* parent = parentGameObject();

    if (parent)
    {
        //Calculate the new world position
        d->worldPosition = parent->worldPosition() + parent->worldOrientation().rotatedVector(parent->worldScale() * d->position);
        d->worldOrientation = parent->worldOrientation() * d->orientation;
        d->worldScale = parent->worldScale() * d->scale;
    }
    else
    {
        //Apparently we do not have a parent, just set our local position to world then
        d->worldPosition = d->position;
        d->worldOrientation = d->orientation;
        d->worldScale = d->scale;
    }

    //Calculate the new transform matrix
    d->transform.setToIdentity();
    d->transform.translate(d->worldPosition);
    d->transform.rotate(d->worldOrientation);
    d->transform.scale(d->worldScale);

    // Finally, update the child objects' position
    foreach(GameObject *child, d->children)
    {
        child->invalidateTransform();
        child->updateTransform();
    }

    d->transformInvalidated = false;
}

void GameObject::invalidateTransform()
{
    d->transformInvalidated = true;
}

QMatrix4x4
GameObject::transform() const
{
    return d->transform;
}

void
GameObject::postCloneSanitize()
{
    foreach(QObject* child, children())
    {
        if(qobject_cast<Component*>(child))
        {
            Component* comp = qobject_cast<Component*>(child);
            d->components.append(comp);
            comp->setParent(this);
            comp->setGameObject(this);
        }
    }

    if(Game::instance()->isRunning())
    {
        initialize();
        start();
    }
    
    GluonCore::GluonObject::postCloneSanitize();
}

#include "gameobject.moc"

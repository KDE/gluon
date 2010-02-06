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
#include "core/debughelper.h"

REGISTER_OBJECTTYPE(GluonEngine,GameObject)

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


GluonCore::GluonObject* GameObject::instantiate()
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
    foreach(Component * component, d->components)
        if(component->enabled()) {
            component->update(elapsedMilliseconds);
        }

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
    DEBUG_FUNC_NAME
    if(addThis)
    {
        DEBUG_TEXT(QString("Adding %2 to %1").arg(name()).arg(addThis->metaObject()->className()));
        if(!d->components.contains(addThis))
        {
            d->components.append(addThis);
            addThis->setParent(this);
            addThis->setGameObject(this);
        }
    }
    else
    {
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
    GluonCore::GluonObject::addChild(child);
}

void
GameObject::addChild(GameObject * addThis)
{
    DEBUG_FUNC_NAME
    if(!addThis)
    {
        DEBUG_TEXT(QString("Fail-add! you're trying to add a NULL GameObject"));
    }
    else if(!d->children.contains(addThis))
    {
        d->children.append(addThis);

        if(addThis->d->parentGameObject)
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
GameObject::setPosition(const Eigen::Vector3f& newPosition)
{
    d->position = newPosition;

    d->transformInvalidated = true;
    updateTransform();
}

void GameObject::setPosition(float x, float y, float z)
{
    setPosition(Eigen::Vector3f(x, y, z));
}

Eigen::Vector3f
GameObject::position() const
{
    return d->position;
}

Eigen::Vector3f
GameObject::worldPosition() const
{
    return d->worldPosition;
}

void
GameObject::setScale(const Eigen::Vector3f& newScale)
{
    d->scale = newScale;

    d->transformInvalidated = true;
    updateTransform();
}

void GameObject::setScale(float x, float y, float z)
{
    setScale(Eigen::Vector3f(x, y, z));
}

Eigen::Vector3f
GameObject::scale() const
{
    return d->scale;
}

Eigen::Vector3f
GameObject::worldScale() const
{
    return d->worldScale;
}


void GameObject::setOrientation(const Eigen::Quaternionf& newOrientation)
{
    d->orientation = newOrientation;

    d->transformInvalidated = true;
    updateTransform();
}

void GameObject::setOrientation(float pitch, float yaw, float roll)
{
    //Eigen::Quaternionf pitchQuat(Eigen::AngleAxisf(pitch, Eigen::Vector3f::UnitX()));
    Eigen::Quaternionf pitchQuat(Eigen::ei_sin(pitch/2), 0, 0, Eigen::ei_cos(pitch/2));
    //Eigen::Quaternionf yawQuat(Eigen::AngleAxisf(yaw, Eigen::Vector3f::UnitY()));
    Eigen::Quaternionf yawQuat(0, Eigen::ei_sin(yaw/2), 0, Eigen::ei_cos(yaw/2));
    //Eigen::Quaternionf rollQuat(Eigen::AngleAxisf(roll, Eigen::Vector3f::UnitZ()));
    Eigen::Quaternionf rollQuat(0, 0, Eigen::ei_sin(roll/2), Eigen::ei_cos(roll/2));

    d->orientation = pitchQuat * yawQuat * rollQuat;

    d->transformInvalidated = true;
    updateTransform();
}

Eigen::Quaternionf GameObject::orientation() const
{
    return d->orientation;
}

Eigen::Quaternionf
GameObject::worldOrientation() const
{
    return d->worldOrientation;
}


void GameObject::setPitch(float pitch)
{
    setOrientation(pitch, yaw(), roll());
}

float GameObject::pitch() const
{
    float x = d->orientation.x();
    float y = d->orientation.y();
    float z = d->orientation.z();
    float w = d->orientation.w();

    return Eigen::ei_atan2(2*(y*z + w*x), w*w - x*x - y*y + z*z);
}

void GameObject::setYaw(float yaw)
{
    setOrientation(pitch(), yaw, roll());
}

float GameObject::yaw() const
{
    float x = d->orientation.x();
    float y = d->orientation.y();
    float z = d->orientation.z();
    float w = d->orientation.w();

    return asin(-2*(x*z + w*y));
}

void GameObject::setRoll(float roll)
{
    setOrientation(pitch(), yaw(), roll);
}

float GameObject::roll() const
{
    float x = d->orientation.x();
    float y = d->orientation.y();
    float z = d->orientation.z();
    float w = d->orientation.w();

    return Eigen::ei_atan2(2*(x*y + w*z), w*w + x*x - y*y - z*z);
}

void
GameObject::updateTransform()
{
    if(!d->transformInvalidated) return;

    GameObject* parent = parentGameObject();

    if(parent)
    {
        //Calculate the new world position
        //d->worldPosition = parent->worldPosition() + (parent->worldOrientation() * (parent->worldScale().cwise() * Eigen::Translation3f(d->position)));
        d->worldPosition = parent->worldPosition() + parent->worldOrientation() * (parent->worldScale().cwise() * d->position);
        d->worldOrientation = parent->worldOrientation() * d->orientation;
        d->worldScale = parent->worldScale().cwise() * d->scale;
    }
    else
    {
        //Apparently we do not have a parent, just set our local position to world then
        d->worldPosition = d->position;
        d->worldOrientation = d->orientation;
        d->worldScale = d->scale;
    }

    d->transform.translate(d->worldPosition).rotate(d->worldOrientation).scale(d->worldScale);

    // Finally, update the child objects' position
    foreach(QObject *child, children())
    {
        GameObject *theChild = qobject_cast<GameObject*>(child);
        if(theChild)
        {
            theChild->invalidateTransform();
            theChild->updateTransform();
        }
    }

    d->transformInvalidated = false;
}

void GameObject::invalidateTransform()
{
    d->transformInvalidated = true;
}

Eigen::Transform3f
GameObject::transform() const
{
    return d->transform;
}

#include "gameobject.moc"

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


#include "prefabprivate.h"

#include "engine/gameobject.h"
#include "prefabinstance.h"
#include "prefabinstancechild.h"

using namespace GluonEngine;

PrefabPrivate::PrefabPrivate()
    : gameObject( 0 )
    , preCacheSize( 0 )
    , additionalCacheSize( 0 )
{
}

PrefabPrivate::PrefabPrivate( const PrefabPrivate& other )
    : instances( other.instances )
    , gameObject( other.gameObject )
    , preCacheSize( 0 )
    , additionalCacheSize( 0 )
{
}

PrefabPrivate::~PrefabPrivate()
{
    delete( gameObject );
}

void PrefabPrivate::updateChildrenFromOther(GluonCore::GluonObject* updateThis, const GluonCore::GluonObject* updateFrom)
{
    // Firstly, we have to ensure the children are in the right place (otherwise the next bit might
    // not function correctly)
    moveChildrenIntoPlace(updateThis, updateFrom);
    removeAndAddChildren(updateThis, updateFrom);

}

void PrefabPrivate::moveChildrenIntoPlace(GluonCore::GluonObject* updateThis, const GluonCore::GluonObject* updateFrom)
{
    // Go through all children recursively on "updateFrom" and...
    foreach(QObject* child, updateFrom->children())
    {
        GluonCore::GluonObject* childObject = qobject_cast<GluonCore::GluonObject*>(child);
        if(!childObject)
            continue;
        
        // operate on a local list of children, so as to easily allow for the removal of children
        // in the end
        QObjectList otherChildList = updateThis->children();
        
        foreach(QObject* otherChild, otherChildList)
        {
            GluonCore::GluonObject* otherChildObject = qobject_cast<GluonCore::GluonObject*>(otherChild);
            if(!otherChildObject)
                continue;
            
            // recurse...
            moveChildrenIntoPlace(otherChildObject, childObject);
            otherChildList.removeOne(otherChild);
        }
        
        // If there are children left in the list...
        foreach(QObject* otherChild, otherChildList)
        {
            otherChild->deleteLater();
        }
    }
}

void PrefabPrivate::removeAndAddChildren(GluonCore::GluonObject* updateThis, const GluonCore::GluonObject* updateFrom)
{
    // Go through all children on "updateThis" and remove all objects which no longer
    // exist on updateFrom
    foreach(QObject* child, updateThis->children())
    {
        GluonCore::GluonObject* childObject = qobject_cast<GluonCore::GluonObject*>(child);
        if(!childObject)
            continue;

        // Check if the child in the item we're updating still exists in the item we're updating from
        QString qualifiedName = childObject->qualifiedName(gameObject);
        GluonCore::GluonObject* otherChild = updateFrom->findItemByName(qualifiedName);
        if(!otherChild)
        {
            // If we've not found the child, that means it was deleted, and we should remove it
            // from here as well
            updateThis->removeChild(childObject);
            childObject->deleteLater();

            // Remove object with same name on all linked instances
            foreach(PrefabInstance* linkedInstance, instances)
            {
                GluonCore::GluonObject* linkedChild = linkedInstance->findItemByName(qualifiedName);
                if(linkedChild)
                {
                    GluonCore::GluonObject* linkedParent = qobject_cast< GluonCore::GluonObject* >(linkedChild->parent());
                    linkedParent->removeChild(linkedChild);
                    linkedChild->deleteLater();
                }
            }
        }
    }

    // Go through all children on "updateFrom" and add all new objects to updateThis
    foreach(QObject* child, updateFrom->children())
    {
        GluonCore::GluonObject* childObject = qobject_cast<GluonCore::GluonObject*>(child);
        if(!childObject)
            continue;
        
        // Check if the child in the item we're updating from exists in the item we're updating
        GluonCore::GluonObject* otherChild = updateThis->findItemByName(childObject->name());
        if(!otherChild)
        {
            // Clone the new child... 
            QString qualifiedName = otherChild->qualifiedName(gameObject);
            GluonCore::GluonObject* clone = otherChild->clone(updateThis);
            
            // - add object in same position on all linked instances
            foreach(PrefabInstance* linkedInstance, instances)
            {
                if(qobject_cast<GameObject*>(clone))
                {
                    // If new object is a GameObject, we need to add it as a PrefabInstanceChild...
                    PrefabInstanceChild* newChildInstance = new PrefabInstanceChild();
                    linkedInstance->addChild(newChildInstance);
                    // Clone the tree from the cloned GameObject
                    newChildInstance->cloneFromGameObject(qobject_cast<GameObject*>(clone));
                }
                else
                {
                    // Otherwise, just clone it verbatim
                    GluonCore::GluonObject* newInstanceChild = clone->clone(linkedInstance);
                    // Reclone properties
                    Prefab::cloneObjectProperties(newInstanceChild, clone);
                }
            }
        }
    }
    
    // Finally. go through all children on "updateFrom" and...
    foreach(QObject* child, updateFrom->children())
    {
        GluonCore::GluonObject* childObject = qobject_cast<GluonCore::GluonObject*>(child);
        if(!childObject)
            continue;
        //...recurse
        GluonCore::GluonObject* otherChildObject = updateThis->findItemByName(childObject->name());
        if(otherChildObject)
            removeAndAddChildren(otherChildObject, childObject);
    }
}

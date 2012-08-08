/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Vinay S Rao <sr.vinay@gmail.com>
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

#ifndef GLUON_ENGINE_SCENEGRAPHOBJECTPRIVATE_H
#define GLUON_ENGINE_SCENEGRAPHOBJECTPRIVATE_H

#include <QList>
#include <QString>

namespace GluonEngine
{
    class SceneGraphObject;
    class GameObject;
    class SceneGraphObjectPrivate
    {
        public:
            SceneGraphObjectPrivate( SceneGraphObject* o );
            ~SceneGraphObjectPrivate();

            SceneGraphObject* parent;
            QString groupname;
            bool grouphead;
            GluonEngine::GameObject* gameobject;
            QList<SceneGraphObject*> children;
            SceneGraphObject* refobject;
            GluonEngine::GameObject* modifiedgameobject;
            SceneGraphObject* o;
    };
}

#endif 

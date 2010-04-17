/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <>
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

#ifndef GLUON_ENGINE_SCENE_H
#define GLUON_ENGINE_SCENE_H

#include "asset.h"
#include "savable.h"

namespace GluonEngine
{
    class GameObject;
    class ScenePrivate;

    class GLUON_ENGINE_EXPORT Scene : public Asset, public GluonEngine::Savable
    {
            Q_OBJECT
            GLUON_OBJECT(GluonEngine::Scene);

        public:
            Scene(QObject * parent = 0);
            ~Scene();

            virtual void setFile(const QUrl &newFile);
            virtual void setName(const QString& newName);
            virtual void resetScene();

            virtual QString contentsToGDL();

            GameObject* sceneContents();

        private:
            ScenePrivate* d;
    };
}

Q_DECLARE_METATYPE(GluonEngine::Scene)
Q_DECLARE_METATYPE(GluonEngine::Scene*)

#endif // GLUON_ENGINE_SCENE_H

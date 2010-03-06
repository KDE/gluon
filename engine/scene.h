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

            virtual QString contentsToGDL();

            virtual void startAll();
            virtual void updateAll(int elapsedMilliseconds);
            virtual void drawAll(int timeLapse = 0);
            virtual void stopAll();

            GameObject* sceneContents();

        private:
            ScenePrivate* d;
    };
}

#endif // GLUON_ENGINE_SCENE_H

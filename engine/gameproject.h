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

#ifndef GLUON_ENGINE_GAMEPROJECT_H
#define GLUON_ENGINE_GAMEPROJECT_H

#include "gluon_engine_export.h"
#include <core/gluonobject.h>

#include <QtCore/QSharedData>
#include <QtCore/QUrl>

namespace GluonEngine
{
    class Scene;
    class GameProjectPrivate;

    /**
     * The GameProject class describes and contains a complete game project,
     * and all the meta information that goes with it, making it into a
     * complete game (minus engine, which is Gluon::Game and all the
     * Gluon::Component subclasses).
     *
     * The project's children (all assets, gameobjects and prefabs in the
     * project) are all found in the QObject hierarchy - they are simply
     * anchored by the QObject parent/child system
     */
    class GLUON_ENGINE_EXPORT GameProject : public GluonCore::GluonObject
    {
            Q_OBJECT;
            GLUON_OBJECT(GluonCore::GameProject);

            Q_PROPERTY(QString description READ description WRITE setDescription)
            Q_PROPERTY(QUrl homepage READ homepage WRITE setHomepage)
            Q_PROPERTY(QList<QUrl> mediaInfo READ mediaInfo WRITE setMediaInfo)

            Q_PROPERTY(QUrl filename READ filename WRITE setFilename)

            // Namespaced types do not work in Q_PROPERTY - workaround in constructor, getter and setter
            //Q_PROPERTY(Gluon::Scene* entryPoint READ entryPoint WRITE setEntryPoint)

        public:
            GameProject(QObject * parent = 0);
            GameProject(const GameProject &other, QObject * parent = 0);
            ~GameProject();

            GluonObject * findItemByName(QString qualifiedName);

            bool saveToFile() const;
            bool loadFromFile();
            bool loadFromFile(QUrl filename);

            /******************************************************************
             * Property Getter-setters
             *****************************************************************/
            QString description() const;
            void setDescription(QString newDescription);

            QUrl homepage() const;
            void setHomepage(QUrl newHomepage);

            QList<QUrl> mediaInfo() const;
            void setMediaInfo(QList<QUrl> newMediaInfo);

            QUrl filename() const;
            void setFilename(QUrl newFilename);

            Scene *entryPoint() const;
            void setEntryPoint(Scene *newEntryPoint);

        private:
            QSharedDataPointer<GameProjectPrivate> d;
    };

}

#endif  // GLUON_ENGINE_GAMEPROJECT_H

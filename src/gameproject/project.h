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

#ifndef GLUON_PROJECT_H
#define GLUON_PROJECT_H

#include <QObject>
#include <QSharedData>
#include <QUrl>

namespace Gluon
{
    class ProjectPrivate;
    class GameObject;
    class Asset;
    class Prefab;
    
    class Project : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QUrl file READ file WRITE setFile)
        Q_PROPERTY(QList<GameObject *> levels READ levels WRITE setLevels)
        Q_PROPERTY(QList<Asset *> assets READ assets WRITE setAssets)
        Q_PROPERTY(QList<Prefab *> prefabs READ prefabs WRITE setPrefabs)
        
        public:
            Project(QObject * parent = 0);
            Project(const Project &other, QObject * parent = 0);
            ~Project();
            
            void setFile(QUrl newFile);
            QUrl file() const;
            
            void setLevels(QList<GameObject *> newLevels);
            QList<GameObject *> levels() const;
            
            void setAssets(QList<Asset *> newAssets);
            QList<Asset *> assets() const;
            
            void setPrefabs(QList<Prefab *> newPrefabs);
            QList<Prefab *> prefabs() const;
        private:
            QSharedDataPointer<ProjectPrivate> d;
    };
}

#endif				// GLUON_PROJECT_H

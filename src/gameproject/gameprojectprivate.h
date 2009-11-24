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

#ifndef GLUON_GAMEPROJECTPRIVATE_H
#define GLUON_GAMEPROJECTPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QUrl>

namespace Gluon
{
    class GluonObject;
    class GameObject;
    
    class GameProjectPrivate : public QSharedData
    {
        public:
            GameProjectPrivate();
            GameProjectPrivate(const GameProjectPrivate &other);
            ~GameProjectPrivate();
            
            QString description;
            QUrl homepage;
            QList<QUrl> mediaInfo;
            QUrl filename;
            GameObject* entryPoint;
            
            GluonObject * findItemByNameInObject(QStringList qualifiedName, GluonObject * parentObject);
    };
}

#endif // GLUON_GAMEPROJECTPRIVATE_H

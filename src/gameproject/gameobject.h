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

#ifndef GLUON_GAMEOBJECT_H
#define GLUON_GAMEOBJECT_H

#include <QtCore/QObject>
#include <QSharedData>

namespace Gluon
{
    class GameObjectPrivate;
    
    class GameObject : public QObject
    {
        Q_OBJECT
        
        public:
            GameObject(QObject * parent = 0);
            GameObject(const GameObject &other, QObject * parent = 0);
            ~GameObject();
            
        private:
            QSharedDataPointer<GameObjectPrivate> d;
    };

}

#endif				// GLUON_GAMEOBJECT_H

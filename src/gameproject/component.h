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

#ifndef GLUON_COMPONENT_H
#define GLUON_COMPONENT_H

#include "gluonobject.h"
#include <QSharedData>

namespace Gluon
{
    class GameObject;
    class ComponentPrivate;
    
    class Component : public GluonObject
    {
        Q_OBJECT
        Q_PROPERTY(QString description READ description WRITE setDescription)
        Q_PROPERTY(bool enabled READ enabled WRITE setEnabled)
        
        public:
            Component(QObject * parent = 0);
            Component(const Component &other, QObject * parent = 0);
            ~Component();
            
            virtual void Start() {};
            virtual void Update(int elapsedMilliseconds) = 0;
            virtual void Draw(int timeLapse = 0) {};
            
            void setDescription(const QString &newDescription);
            QString description() const;
            
            void setEnabled(bool newEnabled);
            bool enabled() const;
            
            // Yes, this is deliberately not a Q_PROPERTY - it is not supposed to be exposed in the editor other than through drag'n'drop
            GameObject * gameObject();
            void setGameObject(GameObject * newGameObject);
        private:
            QSharedDataPointer<ComponentPrivate> d;
    };
}

#endif				// GLUON_COMPONENT_H

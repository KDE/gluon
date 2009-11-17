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

#ifndef GLUON_GLUONOBJECT_H
#define GLUON_GLUONOBJECT_H

#include <QtCore/QObject>
#include <QtCore/QSharedData>
#include "gluonobjectfactory.h"
#include "gluon_export.h"

namespace Gluon
{
    class GameProject;
    class GluonObjectPrivate;

    class GLUON_EXPORT GluonObject : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName)
        // There is deliberately no gameProject property
        
        public:
            GluonObject(QObject * parent = 0);
            GluonObject(const QString& name, QObject *parent = 0);
            virtual ~GluonObject();

            /**
             * This function returns a new instance of this GluonObject.
             * If you subclass GluonObject, make sure to implement this function!
             * Otherwise you will end up with wrongly instanced objects all
             * over your games
             */
            virtual GluonObject * instantiate();

            QString name() const;
            void setName(const QString &newName);

            /**
             * Use this to access functions on the GameProject instance associated
             * with this GluonObject.
             * 
             * @return The instance of GameProject this GluonObject is associated with
             * @see GameProject GameProject::findItemByName
             */
            GameProject * gameProject() const;
            /**
             * Do not use this function unless you are absolutely sure what you
             * are doing!
             * 
             * @param newGameProject The GameProject instance this GluonObject can be found underneath
             */
            void setGameProject(GameProject * newGameProject);
            
            virtual QString toGDL(int indentLevel = 0) const;
            virtual QString propertiesToGDL(int indentLevel = 0) const;
            
            virtual void setPropertyFromString(const QString &propertyName, const QString &propertyValue);
            virtual QString getStringFromProperty(const QString& propertyName, const QString& indentChars) const;
            
            virtual void sanitize();

            /**
            * QObject hierarchy helper functions.
            */
            virtual void addChild(GluonObject *child);
            virtual bool removeChild(GluonObject *child);
            virtual GluonObject * child(int index) const;
            virtual GluonObject * child(const QString& name) const;

        private:
            QSharedDataPointer<GluonObjectPrivate> d;
    };
}


#endif				// GLUON_GLUONOBJECT_H

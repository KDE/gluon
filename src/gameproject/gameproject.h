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

#ifndef GLUON_GAMEPROJECT_H
#define GLUON_GAMEPROJECT_H

#include "gluonobject.h"
#include "gameobject.h"

#include <QtCore/QSharedData>
#include <QUrl>

namespace Gluon
{
    class GameProjectPrivate;
    
    class GameProject : public GluonObject
    {
        Q_OBJECT;
        
        Q_PROPERTY(QString description READ description WRITE setDescription)
        Q_PROPERTY(QUrl homepage READ homepage WRITE setHomepage)
        Q_PROPERTY(QList<QUrl> mediaInfo READ mediaInfo WRITE setMediaInfo)
        
        Q_PROPERTY(QUrl filename READ filename WRITE setFilename)
        
        Q_PROPERTY(GameObject* entryPoint READ entryPoint WRITE setEntryPoint)
        
        public:
            GameProject(QObject * parent = 0);
            GameProject(const GameProject &other, QObject * parent = 0);
            ~GameProject();

            GluonObject * findItemByName(QString qualifiedName);
            
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
            
            GameObject * entryPoint() const;
            void setEntryPoint(GameObject * newEntryPoint);
            
        private:
            QSharedDataPointer<GameProjectPrivate> d;
    };

}

#endif				// GLUON_GAMEPROJECT_H

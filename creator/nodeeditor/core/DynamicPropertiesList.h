/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef DYNAMICPROPERTIESLIST_H
#define DYNAMICPROPERTIESLIST_H

#include <QObject>
#include <QList>
#include "graph.h"
#include "edge.h"

#include "gluoncreator_nodeeditor_export.h"

enum DynamicPropertyType
{
    None,
    Unique,
    Multiple,
    Global
};


class DynamicPropertiesList : public QObject
{
        Q_OBJECT
        QMap< Graph*,  QMultiMap <QString, Node* > > _NodesProperties;
        QMap< Graph*,  QMultiMap <QString, Edge* > > _EdgesProperties;
        QMultiMap <QString, Graph*> _GraphProperties;

        static DynamicPropertiesList* self;

        DynamicPropertiesList( QObject* parent = 0 );

    public:

        static DynamicPropertiesList* New();

        void addProperty( QObject* obj, QString name );
        void removeProperty( QObject* obj, QString name );

        /**Return type of property from obj*/
        DynamicPropertyType type( QObject* obj, QString name );
        /**Return textual type of property from obj*/
        QString typeInText( QObject* obj, QString name );

        //   const QStringList properties (QObject * obj);

        void clear( Graph* graph = 0 );

        /** Change property name in all objects from same graph of object.*/
        void changePropertyName( QString name, QString newName, QObject* object );


};

#endif // DINAMICPROPERTIESLIST_H

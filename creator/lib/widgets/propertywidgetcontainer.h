/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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

#ifndef GLUON_CREATOR_PROPERTYWIDGETCONTAINER_H
#define GLUON_CREATOR_PROPERTYWIDGETCONTAINER_H
#include "propertywidgetitem.h"
#include <QtGui/QWidget>
#include <core/gluonobject.h>
#include <QtCore/QString>
#include <QList>
namespace GluonCore
{
    class GluonObject;
}

namespace GluonCreator
{
    class PropertyWidgetItem;
    class PropertyWidgetContainer : public QWidget
    {
            Q_OBJECT
            Q_PROPERTY( bool expanded READ expanded WRITE setExpanded )
            Q_PROPERTY( bool enabled READ enabled WRITE setEnabled )
            Q_PROPERTY( QString title READ title WRITE setTitle )

        public:
            explicit PropertyWidgetContainer( GluonCore::GluonObject* theObject, QWidget* parent = 0, Qt::WindowFlags f = 0 );
            virtual ~PropertyWidgetContainer();
            void setObject( GluonCore::GluonObject* theObject );

            bool expanded() const;
            void setExpanded( const bool& newExpanded );
            Q_SLOT void toggleExpanded();

            bool enabled() const;
            Q_SLOT void setEnabled( const bool& newEnabled );
	    void getItemsListpub();
            QString title() const;
            void setTitle( const QString& newTitle );

            void addDefaultMenuItems();
            void addMenuItem( QAction* menuItem );
            void removeMenuItem( QAction* menuItem );

        Q_SIGNALS:
            void propertyChanged( QObject* object, const QString& property, const QVariant& oldValue, const QVariant& newValue );
	    void propChangedContainer(GluonCore::GluonObject* object, const QString& property, const QVariant& newValue);

        public Q_SLOTS:
            void upTriggered();
            void downTriggered();
            void delTriggered();
	    void onChanged(GluonCore::GluonObject*, const QString& property, const QVariant newValue);
            void addPropertyTriggered();
            void propertyCreated( GluonCore::GluonObject* propertyCreatedOn, QString createdPropertyName );
            void objectDeleted( QObject* obj );

        private:
            class PropertyWidgetContainerPrivate;
            PropertyWidgetContainerPrivate* d;
    };
}

#endif // GLUON_CREATOR_PROPERTYWIDGETCONTAINER_H

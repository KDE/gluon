/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUON_CREATOR_PROPERTYWIDGET_H
#define GLUON_CREATOR_PROPERTYWIDGET_H

#include "lib/gluoncreator_macros.h"

#include <QtGui/QWidget>
#include <QtGui/QScrollArea>

namespace GluonCore
{
    class GluonObject;
}

namespace GluonEngine
{
    class Component;
}

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT PropertyWidget : public QScrollArea
    {
            Q_OBJECT;

        public:
            PropertyWidget( QWidget* parent = 0 );
            virtual ~PropertyWidget();

            GluonCore::GluonObject* object() const;
            void clear();

            void setObject( GluonCore::GluonObject* object );
            void appendObject( GluonCore::GluonObject* obj, bool useColor = false );

        Q_SIGNALS:
            void propertyChanged( QObject* object, const QString& property, const QVariant& oldValue, const QVariant& newValue );

        private:
            class PropertyWidgetPrivate;
            PropertyWidgetPrivate* const d;
    };
}

#endif // GLUON_CREATOR_PROPERTYWIDGET_H

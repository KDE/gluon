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

#ifndef GLUON_CREATOR_MESSAGEDOCK_H
#define GLUON_CREATOR_MESSAGEDOCK_H

#include <core/gluonobject.h>

#include <QtWidgets/QDockWidget>

namespace GluonCore { struct LogData; }

namespace GluonCreator
{
    class MessageDock : public QDockWidget
    {
            Q_OBJECT
        public:
            explicit MessageDock( const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0 );
            ~MessageDock();

        public slots:
            void showDebug( const QString& debugText, const GluonCore::DebugType& debugType );

        private slots:
            void selectAll();
            void copy();
            void clearSelection();

            void newMessage( const GluonCore::LogData& message );

        private:
            class MessageDockPrivate;
            MessageDockPrivate* const d;
    };

}

#endif // GLUON_CREATOR_SCENEDOCKPLUGIN_H

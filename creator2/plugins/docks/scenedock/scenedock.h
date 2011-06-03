/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef GLUON_CREATOR_SCENEDOCK_H
#define GLUON_CREATOR_SCENEDOCK_H

#include <QtCore/QModelIndex>
#include <QtGui/QItemSelection>
#include <QtGui/QDockWidget>

namespace GluonEngine
{
    class Scene;
    class GameObject;
}

namespace GluonCreator
{
    class SceneDock : public QDockWidget
    {
            Q_OBJECT
        public:
            explicit SceneDock( const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0 );
            ~SceneDock();

        public slots:
            void selectionChanged( QItemSelection selected, QItemSelection deselected );
            void sceneChanged( GluonEngine::Scene* );

            void deleteSelection();
            void newGameObjectAction();

        private:
            class SceneDockPrivate;
            SceneDockPrivate* d;
    };
}

#endif // GLUON_CREATOR_SCENEDOCK_H

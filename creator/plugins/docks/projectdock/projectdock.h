/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_CREATOR_PROJECTDOCK_H
#define GLUON_CREATOR_PROJECTDOCK_H

#include <QtCore/QModelIndex>
#include <QtGui/QDockWidget>

class QItemSelection;

namespace GluonEngine
{
    class GameProject;
}

namespace GluonCreator
{

    class ProjectDock : public QDockWidget
    {
            Q_OBJECT
        public:
            explicit ProjectDock( const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0 );
            virtual ~ProjectDock();

        public slots:
            void activated( QModelIndex index );
            void selectionChanged( const QItemSelection& selected, const QItemSelection& deselected );
            void showContextMenuRequested( const QPoint& pos );
            void currentProjectChanged( GluonEngine::GameProject* project );

            void contextMenuHiding();
            void newSubMenuTriggered();
            void newAssetTriggered();
            void deleteActionTriggered();
            void importAssetsTriggered();

        private:
            class ProjectDockPrivate;
            ProjectDockPrivate* const d;
    };

}

#endif // GLUON_CREATOR_PROJECTDOCKPLUGIN_H

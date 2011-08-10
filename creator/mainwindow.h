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

#ifndef GLUON_CREATOR_MAINWINDOW_H
#define GLUON_CREATOR_MAINWINDOW_H

#include "dialogs/projectselectiondialog.h"

#include <KDE/KParts/MainWindow>
#include <KDE/KUrl>

class KRecentFilesAction;
namespace GluonCreator
{
    class Plugin;

    class MainWindow : public KParts::MainWindow
    {
            Q_OBJECT
        public:
            MainWindow( const QString& fileName = "" );
            ~MainWindow();

            virtual bool queryClose();
            virtual void closeEvent( QCloseEvent* event );

        public slots:
            void openProject( KUrl url );
            void openProject( const QString& fileName );
            void saveProject();
            void saveProject( const QString& fileName );
            void saveProjectAs();
            void showPreferences();

            void playGame();
            void pauseGame();
            void stopGame();

            void historyChanged();
            void cleanChanged( bool );

            void addAsset();

            void showNewProjectDialog();
            void showOpenProjectDialog();
            void projectDialogAccepted();

            void initializeGame();

            void partChanged( KParts::Part* part );

        private:
            void setupActions();

            class MainWindowPrivate;
            MainWindowPrivate* const d;
    };
}

#endif // GLUON_CREATOR_MAINWINDOW_H

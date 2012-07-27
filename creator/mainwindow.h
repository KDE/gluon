/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONCREATOR_MAINWINDOW_H
#define GLUONCREATOR_MAINWINDOW_H

#include "introslideshow.h"

#include <KDE/KParts/MainWindow>
#include <QtDeclarative/QDeclarativeView>
#include <KDE/KStandardDirs>
#include <QtDeclarative/QDeclarativeItem>
#include <dialogs/welcomedialog.h>

class KStandardDirs;
class QDeclarativeView;
class KUrl;
class KRecentFilesAction;
namespace GluonCreator
{
    class Plugin;

    class MainWindow : public KParts::MainWindow
    {
            Q_OBJECT
        public:
            explicit MainWindow( const QString& fileName = QString(), QWidget* parent = 0, Qt::WindowFlags flags = 0 );
            ~MainWindow();
            virtual bool queryClose();
            virtual void closeEvent( QCloseEvent* event );
            QDeclarativeView* view;
	    WelcomeDialogPage *w;

        public slots:
            void openProject();
            void openProject( const KUrl& url );
            void openProject( const QString& fileName );
            void saveProject();
            void saveProject( const QString& fileName );
            void saveProjectAs();
            void showPreferences();
            void playGame();
            void pauseGame();
            void stopGame();
	    void loadView();
            void historyChanged();
            void cleanChanged( bool );
            void addAsset();
            void showNewProjectDialog();
            void showOpenProjectDialog();
            void projectDialogAccepted();
            void partChanged( KParts::Part* part );

        private:
            void setupActions();
            class Private;
            Private* const d;
    };
}

#endif // GLUONCREATOR_MAINWINDOW_H

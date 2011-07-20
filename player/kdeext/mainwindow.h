/************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
 *      
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *           
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *                              
 * You should have received a copy of the GNU General Public License along   
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef GLUON KDEEXTPLAYER_MAINWINDOW_H
#define GLUON_KDEEXTPLAYER_MAINWINDOW_H

#include "loginform.h"

#include "gamesoverlay.h"
#include "gamedetailsoverlay.h"

#include <engine/gameproject.h>
#include <graphics/engine.h>
#include <core/gluon_global.h>

#include <KDE/KXmlGuiWindow>
#include <KDE/KApplication>
#include <KDE/KTextEdit>
#include <KDE/KTabWidget>

#include <QtGui/QResizeEvent>
#include <QtGui/QGridLayout>
#include <QtGui/QListView>
#include <QtCore/QModelIndex>

class KRecentFilesAction;

namespace GluonKDEPlayer
{
    /**
     * The main window of the KDE Player frontend
     */
    class MainWindow: public KXmlGuiWindow
    {
            Q_OBJECT

        public:
            explicit MainWindow( const QString& fileName = "" );
            virtual ~MainWindow();

        protected:
            virtual void closeEvent( QCloseEvent* event );
            virtual void resizeEvent( QResizeEvent* event );

        public Q_SLOTS:
            void startGame();
            void pauseGame();
            void stopGame();

            void optionsConfigureKeys();
            void optionsConfigureToolbars();

        private slots:
            void mLogin( );
            void mLogout( );
            void mHome();
            void mDetails();
            void mRegistration();
            void mForgottenPassword();
            void openProject();
            void setProject( const QModelIndex& index );
            void showGames();
            void activated( QModelIndex index );
            void countFrames( int );
            void updateTitle( int msec );

        private:
            void setupActions();

            class MainWindowPrivate;
            MainWindowPrivate* d;

            GamesOverlay* m_gamesOverlay;
            QGridLayout* m_layout;
            QString m_gameFileName;
            GluonEngine::GameProject* m_project;
            KRecentFilesAction* m_recentFiles;

            int m_viewportWidth;
            int m_viewportHeight;
    };
}

#endif // GLUON_KDEEXTPLAYER_MAINWINDOW_H


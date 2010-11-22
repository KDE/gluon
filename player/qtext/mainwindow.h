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

#ifndef GLUONPLAYER_MAINWINDOW_H
#define GLUONPLAYER_MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QAction>
#include <QtGui/QToolBar>
#include <QtGui/QMenuBar>
#include <QtGui/QMessageBox>

class QModelIndex;

namespace GluonPlayer
{
    class MainWindow : public QMainWindow
    {
            Q_OBJECT
        public:
            MainWindow( int argc, char** argv, QWidget* parent = 0, Qt::WindowFlags flags = 0 );
            virtual void closeEvent( QCloseEvent* event );

        public slots:
            void openProject( const QString& fileName = QString() );
            void updateTitle( int msec );
            void activated( QModelIndex index );
            void openClicked( bool );
            void startGame();
            void countFrames( int );

        private slots:
            void mOpenGame();
            void mShowToolBar(bool checked);
            void mShowStatusBar(bool checked);
            void mConfigureToolBar();
            void mConfigureShortcuts();
            void mAbout();

            void mLoginLogout();
            void mHome();
            void mDetails();
            void mRegistration();
            void mForgottenPassword();

        protected:
            void changeEvent(QEvent *e);

        private:
            void setupUi();
            void retranslateUi();

            void createActions();
            void createMenus();
            void createToolBars();
            void createStatusBar();

            QWidget *centralWidget;

            QMenuBar *menuBar;
            QToolBar *mainToolBar;
            QStatusBar *statusBar;

            // File menu related action declarations
            QAction *openGameAct;
            QAction *quitAct;

            // View menu related action declarations
            QAction *showToolBarAct;
            QAction *showStatusBarAct;


            // Community menu related action declarations
            QAction *loginLogoutAct;
            QAction *homeAct;
            QAction *detailsAct;
            QAction *registrationAct;
            QAction *forgottenPasswordAct;


            // Settings menu related action declarations
            QAction *configureShortcutsAct;
            QAction *saveShortcutsAct;
            QAction *configureToolBarAct;


            // Help menu related action declarations
            QAction *aboutAct;
            QAction *aboutQtAct;


            // Menubar entries
            QMenu   *fileMenu;
            QMenu   *viewMenu;
            QMenu   *communityMenu;
            QMenu   *settingsMenu;
            QMenu   *helpMenu;


            class MainWindowPrivate;
            MainWindowPrivate* d;
    };
}

#endif // GLUONPLAYER_MAINWINDOW_H

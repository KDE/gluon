/*****************************************************************************
 * mainwindow.h - QStarDict, a StarDict clone written with using Qt          *
 * Copyright (C) 2007 Alexander Rodin                                        *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License along   *
 * with this program; if not, write to the Free Software Foundation, Inc.,   *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.               *
 *****************************************************************************/

#ifndef GLUONKDEPLAYER_MAINWINDOW_H
#define GLUONKDEPLAYER_MAINWINDOW_H

#include <core/gluon_global.h>

#include <KXmlGuiWindow>
#include <KApplication>
#include <KTextEdit>

#include <QModelIndex>

class KRecentFilesAction;

namespace GluonKDEExtPlayer {
    /**
     * The main window of the KDE Player frontend
     */
    class MainWindow: public KXmlGuiWindow
    {
        Q_OBJECT
        public:
            explicit MainWindow( const QString& fileName = "" );
            virtual ~MainWindow();

        public slots:
            void playGame();
            void pauseGame();
            void stopGame();

            void optionsConfigureKeys();
            void optionsConfigureToolbars();

        private slots:
            void mLoginLogout( bool checked );
            void mHome();
            void mDetails();
            void mRegistration();
            void mForgottenPassword();

        private:
            void setupActions();

            KTextEdit* textArea;
            class MainWindowPrivate;
            MainWindowPrivate* d;

    };
}

#endif // GLUONKDEPLAYER_MAINWINDOW_H


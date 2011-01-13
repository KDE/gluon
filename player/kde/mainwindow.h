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

#include <KMainWindow>

#include <QModelIndex>

class KRecentFilesAction;

namespace GluonPlayer {
    /**
     * The main window of the KDE Player frontend
     */
    class MainWindow: public KMainWindow
    {
        Q_OBJECT
        public:
            explicit MainWindow( const QString& fileName = "" );
            virtual ~MainWindow();

            virtual void closeEvent( QCloseEvent* event );

        public slots:
            void openProject( const QString& fileName = QString() );
            void updateTitle( int msec );
            void activated( QModelIndex index );
            void openClicked( bool );
            void startGame();
            void countFrames( int );

        private:
            class MainWindowPrivate;
            MainWindowPrivate* d;

    };
}

#endif // GLUONKDEPLAYER_MAINWINDOW_H


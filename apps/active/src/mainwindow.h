/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2013 Shantanu Tushar <shantanu@kde.org>
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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <kdeclarative.h>

class QResizeEvent;

class MainWindow : public QMainWindow
{
        Q_OBJECT
    public:
        MainWindow();
        Q_INVOKABLE void playGame( const QString& gameId );

    private Q_SLOTS:
        void startGame();

    private:
        KDeclarative m_kdeclarative;
        void openProject( const QString& projectPath );
        QString m_projectPath;
};

#endif // MAINWINDOW_H

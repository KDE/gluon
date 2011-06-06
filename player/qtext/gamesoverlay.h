/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GAMESOVERLAY_H
#define GAMESOVERLAY_H

#include <QtGui/QIcon>
#include <QtGui/QTabWidget>
#include <QtGui/QGridLayout>
#include <QtCore/QModelIndex>

class GamesView;
class LoginForm;

class GamesOverlay : public QWidget
{
        Q_OBJECT

    public:
        explicit GamesOverlay( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );
        GamesView* gamesView();

    private:
        QTabWidget* m_tabWidget;
        GamesView* m_gamesView;
        LoginForm* m_loginForm;

    signals:
        void gameToPlaySelected( const QModelIndex& index );
        void gameSelected( const QModelIndex& index );
};

#endif // GAMESOVERLAY_H

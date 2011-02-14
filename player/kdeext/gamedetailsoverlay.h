/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef GAMEDETAILSOVERLAY_H
#define GAMEDETAILSOVERLAY_H

#include <KDE/KTabWidget>
#include <KDE/KPushButton>
#include <KDE/KIcon>
#include <KDE/KLocalizedString>

#include <QtGui/QTableView>
#include <QtGui/QListView>

namespace GluonPlayer
{
    class CommentsModel;
    class HighScoresModel;
}

class HighScoresView;
class AchievementsView;
class CommentsView;

class GameDetailsOverlay : public QWidget
{
    Q_OBJECT
    public:
        explicit GameDetailsOverlay( QString gameId, QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );
        virtual ~GameDetailsOverlay();

    private:
        KPushButton* m_backButton;

        KTabWidget* m_tabWidget;
        QTableView* m_highScoresView;
        AchievementsView* m_achievementsView;
        QListView* m_commentsView;

        GluonPlayer::CommentsModel* m_commentsModel;
        GluonPlayer::HighScoresModel* m_highScoresModel;

    signals:
        void back();
};

#endif // GAMEDETAILSOVERLAY_H

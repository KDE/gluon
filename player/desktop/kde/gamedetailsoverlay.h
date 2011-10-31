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

#ifndef GAMEDETAILSOVERLAY_H
#define GAMEDETAILSOVERLAY_H

#include "delegates/commentitemsviewdelegate.h"
#include "lib/models/commentitemsmodel.h"
#include "views/newcommentform.h"

#include <KDE/KTabWidget>
#include <KDE/KPushButton>
#include <KDE/KIcon>
#include <KDE/KLocalizedString>

#include <QtGui/QGridLayout>
#include <QtGui/QTableView>
#include <QtGui/QListView>
#include <QtGui/QSortFilterProxyModel>

namespace GluonEngine
{
    class ProjectMetaData;
}

namespace GluonPlayer
{
    class HighScoresModel;
    class AchievementsModel;
}

class HighScoresView;
class AchievementsView;
class CommentsView;

namespace GluonKDEPlayer
{
    class GameDetailsOverlay : public QWidget
    {
            Q_OBJECT
        public:
            explicit GameDetailsOverlay( GluonEngine::ProjectMetaData* metaData, const QString& userName, QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );
            virtual ~GameDetailsOverlay();

        protected slots:
            void addNewComment( QModelIndex parentIndex, QString title, QString body );
            void cancelNewComment( );
            void showReplyForm( const QModelIndex& index );
            void commentFailed( );

        signals:
            void back();

        private:
            KPushButton* m_backButton;

            KTabWidget* m_tabWidget;
            QTableView* m_highScoresView;
            QTableView* m_achievementsView;
            QListView* m_commentsView;
            CommentItemsViewDelegate* m_commentsDelegate;

            GluonPlayer::CommentItemsModel* m_commentsModel;
            GluonPlayer::HighScoresModel* m_highScoresModel;
            GluonPlayer::AchievementsModel* m_achievementsModel;
            QGridLayout* m_contentLayout;
            NewCommentForm* m_newCommentForm;
            QWidget* m_commentWidget;
    };
}

#endif // GAMEDETAILSOVERLAY_H

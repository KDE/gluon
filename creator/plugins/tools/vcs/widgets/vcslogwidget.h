/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef VCSLOGWIDGET_H
#define VCSLOGWIDGET_H

#include "lib/gluoncreator_macros.h"

#include <KDE/KUrl>
#include <KDE/KColorScheme>
#include <KDE/KSqueezedTextLabel>
#include <KDE/KTextBrowser>

#include <QtGui/QGridLayout>
#include <QtGui/QTableView>
#include <QtGui/QWidget>
#include <QtCore/QModelIndex>

class QPoint;
class QModelIndex;
class KUrl;

namespace KDevelop
{
    class VcsJob;
    class VcsEventModel;
    class VcsItemEventModel;
}

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT VcsLogWidget : public QWidget
    {
        Q_OBJECT
        public:
            VcsLogWidget( const KUrl&, KDevelop::VcsJob*, QWidget *parent = 0 );
            virtual ~VcsLogWidget();

        private slots:
            void diffToPrevious();
            void diffRevisions();
            void jobReceivedResults( KDevelop::VcsJob* job );
            void eventViewCustomContextMenuRequested( const QPoint &point );
            void eventViewClicked( const QModelIndex &index );
            void currentRowChanged( const QModelIndex& start, const QModelIndex& end );

        private:
            KDevelop::VcsItemEventModel* m_detailModel;
            KDevelop::VcsEventModel *m_logModel;
            KDevelop::VcsJob* m_job;
            KUrl m_url;
            QModelIndex m_contextIndex;

            // UI elements
            QGridLayout* m_gridLayout;
            KSqueezedTextLabel* m_label;
            QTableView* m_eventView;
            KSqueezedTextLabel* label2;
            QTableView* m_itemEventView;
            KSqueezedTextLabel* label3;
            KTextBrowser* message;
    };
}

#endif

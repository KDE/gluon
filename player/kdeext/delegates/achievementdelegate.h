/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Felix Rohrbach <fxrh@gmx.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *****************************************************************************/

#ifndef GLUON_ACHIEVEMENTDELEGATE_H
#define GLUON_ACHIEVEMENTDELEGATE_H

#include <QtGui/QStyledItemDelegate>

namespace GluonKDEPlayer
{
    class AchievementDelegate : public QStyledItemDelegate
    {
            Q_OBJECT
        public:
            AchievementDelegate( QObject* parent = 0 );
            virtual ~AchievementDelegate();

            virtual void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
            virtual QSize sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const;
    };
}

#endif // GLUON_ACHIEVEMENTDELEGATE_H

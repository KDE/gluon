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

#include "achievementdelegate.h"

#include "player/lib/models/achievementsmodel.h"

#include <engine/achievementsmanager.h>
#include <engine/projectmetadata.h>

#include <KDebug>
#include <KIcon>

#include <QtGui/QPainter>
#include <QtGui/QStyleOptionProgressBar>
#include <QtGui/QApplication>

using namespace GluonKDEPlayer;

AchievementDelegate::AchievementDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

AchievementDelegate::~AchievementDelegate()
{
}

void AchievementDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    const GluonPlayer::AchievementsModel* model = qobject_cast<const GluonPlayer::AchievementsModel*>(index.model());
    if( !model )
    {
        kDebug() << "Wrong datamodel! Has to be AchievementModel.";
        return;
    }

    painter->save();
    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );

    if( option.state & QStyle::State_Selected )
        painter->setPen( QPen( option.palette.highlightedText().color() ) );
    else
        painter->setPen( QPen( option.palette.text().color() ) );

    // paint the icon
    int imageSize = option.rect.height() - 10;
    QString iconString = model->achievementsManager()->achievementIcon(index.row());
    QIcon icon;
    if( iconString.isEmpty() )
        icon = KIcon("games-achievements");
    else
        icon = QIcon( model->metaData()->projectDir() + "/" + iconString );
    QPixmap image;
    if( !model->achievementsManager()->achievementAchieved(index.row()) )
        image = icon.pixmap(50, QIcon::Disabled);
    else
    {
        if( option.state & QStyle::State_Selected )
            image = icon.pixmap(50, QIcon::Selected);
        else
            image = icon.pixmap(50, QIcon::Normal);
    }
    painter->drawPixmap( option.rect.x() + 5, option.rect.y() + 5, imageSize, imageSize, image );

    int textStartX = option.rect.x() + 5 + imageSize + 10;
    int textRowHeight = (option.rect.height()-5) / 3;
    QString name, description, progressString;
    qlonglong minimumScore, currentScore;
    if( model->achievementsManager()->dependencySatisfied(index.row()) )
    {
        name = model->achievementsManager()->achievementName(index.row());
        description = model->achievementsManager()->description(index.row());
        minimumScore = model->achievementsManager()->minimumScore(index.row());
        currentScore = qMin( minimumScore, model->achievementsManager()->currentScore(index.row()) );
        progressString = QString::number(currentScore) + "/" + QString::number(minimumScore);
    }
    else
    {
        name = "Locked";
        description = "Depends on: " + model->achievementsManager()->dependency(index.row());
        minimumScore = 100;
        currentScore = 0;
        progressString = "0/0";
    }

    // paint the text
    QFont font;
    font.setBold(true);
    painter->save();
    painter->setFont(font);
    painter->drawText( textStartX, option.rect.y(), option.rect.right() - textStartX, textRowHeight,
                       Qt::AlignVCenter, name );
    painter->restore();
    painter->drawText( textStartX, option.rect.y() + textRowHeight, option.rect.right() - textStartX, textRowHeight,
                       Qt::AlignVCenter, description );

    // paint the progress bar
    QStyleOptionProgressBar progressStyleOption;
    progressStyleOption.rect = QRect( textStartX, option.rect.y() + 2*textRowHeight,
                                      option.rect.right() - textStartX, textRowHeight );
    progressStyleOption.minimum = 0;
    progressStyleOption.maximum = 100;
    progressStyleOption.progress = 100*currentScore / minimumScore;
    progressStyleOption.text = progressString;
    progressStyleOption.textVisible = true;

    QApplication::style()->drawControl( QStyle::CE_ProgressBar, &progressStyleOption, painter );
    painter->restore();
}

QSize AchievementDelegate::sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const
{
    return QSize( 300, 60 );
}

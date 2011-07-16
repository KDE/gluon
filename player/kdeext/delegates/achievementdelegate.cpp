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
    const GluonEngine::AchievementsManager* achievementsManager = model->achievementsManager();

    QIcon icon;
    if( !achievementsManager->dependencySatisfied(index.row()) )
    {
        icon = KIcon( "games-achievements-locked" );
    }
    else
    {
        QString iconString = achievementsManager->achievementIcon(index.row());
        if( iconString.isEmpty() )
            icon = KIcon( "games-achievements" );
        else
            icon = QIcon( model->metaData()->projectDir() + '/' + iconString );
    }

    bool disabled = !achievementsManager->achievementAchieved( index.row() );

    QString name, description, progressString;
    qlonglong maxScore, minScore, currentScore;
    bool paintProgressBar;
    if( !achievementsManager->dependencySatisfied(index.row()) )
    {
        name = "Locked";
        int dependency = achievementsManager->dependency(index.row());
        description = "Depends on: ";
        if( dependency == -1 )
            description += "hidden achievement";
        else if( !achievementsManager->dependencySatisfied( dependency ) )
            description += "locked achievement";
        else
            description += achievementsManager->achievementName( dependency );
        paintProgressBar = false;
    }
    else
    {
        name = achievementsManager->achievementName( index.row() );
        description = achievementsManager->description( index.row() );
        if( !achievementsManager->madeProgress( index.row() ) || achievementsManager->achievementAchieved( index.row() ) )
        {
            paintProgressBar = false;
        }
        else
        {
            paintProgressBar = true;
            minScore = achievementsManager->thresholdScore( index.row() );
            maxScore = achievementsManager->minimumScore( index.row() );
            currentScore = qMin( maxScore, achievementsManager->currentScore( index.row() ) );
            progressString = QString("%1 %").arg( 100*(currentScore-minScore)/(maxScore-minScore) );
        }
    }

    bool paintAchievedIcon = achievementsManager->achievementAchieved( index.row() );


    // Paint!
    painter->save();
    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );

    if( option.state & QStyle::State_Selected )
        painter->setPen( QPen( option.palette.highlightedText().color() ) );
    else
        painter->setPen( QPen( option.palette.text().color() ) );

    // paint the icon
    int imageSize = option.rect.height() - 10;
    QPixmap image;
    if( disabled )
        image = icon.pixmap(imageSize, QIcon::Disabled);
    else
    {
        if( option.state & QStyle::State_Selected )
            image = icon.pixmap(imageSize, QIcon::Selected);
        else
            image = icon.pixmap(imageSize, QIcon::Normal);
    }
    painter->drawPixmap( option.rect.x() + 5, option.rect.y() + 5, imageSize, imageSize, image );

    int textStartX = option.rect.x() + 5 + imageSize + 10;
    int textRowHeight = (option.rect.height()-5) / 3;
    int textLength = option.rect.right() - textStartX;
    if( paintAchievedIcon )
        textLength -= (imageSize+5);
    // paint the text
    QFont font;
    font.setBold(true);
    painter->save();
    painter->setFont(font);
    painter->drawText( textStartX, option.rect.y(), textLength, textRowHeight,
                       Qt::AlignVCenter, name );
    painter->restore();
    painter->drawText( textStartX, option.rect.y() + textRowHeight, textLength, textRowHeight,
                       Qt::AlignVCenter, description );

    if( paintProgressBar )
    {
        // paint the progress bar
        QStyleOptionProgressBar progressStyleOption;
        progressStyleOption.rect = QRect( textStartX, option.rect.y() + 2*textRowHeight,
                                          textLength, textRowHeight );
        progressStyleOption.minimum = minScore;
        progressStyleOption.maximum = maxScore;
        progressStyleOption.progress = currentScore;
        progressStyleOption.text = progressString;
        progressStyleOption.textVisible = true;

        QApplication::style()->drawControl( QStyle::CE_ProgressBar, &progressStyleOption, painter );
    }

    if( paintAchievedIcon )
    {
        QPixmap pixmap;
        if( option.state & QStyle::State_Selected )
            pixmap = KIcon( "games-endturn" ).pixmap( imageSize, QIcon::Selected );
        else
            pixmap = KIcon( "games-endturn" ).pixmap( imageSize, QIcon::Normal );
        painter->drawPixmap( textStartX + textLength, option.rect.y() + 5, imageSize, imageSize, pixmap );
    }
    painter->restore();
}

QSize AchievementDelegate::sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const
{
    return QSize( 300, 58 );
}

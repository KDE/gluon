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

#include <KDE/KDebug>
#include <KDE/KIcon>

#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionProgressBar>
#include <QtGui/QApplication>

using namespace GluonKDEPlayer;

AchievementDelegate::AchievementDelegate(QAbstractItemView* itemView, QObject* parent)
    : KWidgetItemDelegate(itemView, parent)
{
}

AchievementDelegate::~AchievementDelegate()
{
}

QList<QWidget*> AchievementDelegate::createItemWidgets() const
{
    QList<QWidget*> list;
    QLabel* imageLabel = new QLabel();
    list << imageLabel;
    QLabel* nameLabel = new QLabel();
    list << nameLabel;
    QLabel* descriptionLabel = new QLabel();
    list << descriptionLabel;
    QProgressBar* progressBar = new QProgressBar();
    list << progressBar;

    return list;
}

void AchievementDelegate::updateItemWidgets( const QList<QWidget*> widgets,
                                             const QStyleOptionViewItem& option,
                                             const QPersistentModelIndex& index ) const
{
    const GluonPlayer::AchievementsModel* model = qobject_cast<const GluonPlayer::AchievementsModel*>(index.model());
    if( !model )
    {
        kDebug() << "Warning - Invalid Model! AchievementModel expected.";
        return;
    }

    bool itemIsEnabled = index.flags().testFlag( Qt::ItemIsEnabled );
    int imageSize = option.rect.height() - 10;
    QLabel* imageLabel = qobject_cast<QLabel*>( widgets.at(0) );
    if( imageLabel )
    {
        QString iconString = model->achievementsManager()->achievementIcon(index.row());
        QIcon icon;
        if( iconString.isEmpty() )
            icon = KIcon("games-achievements");
        else
            icon = QIcon( model->projectDir() + '/' + iconString );

        QPixmap image;
        if( !model->achievementsManager()->achievementAchieved(index.row()) )
        {
            image = icon.pixmap(50, QIcon::Disabled);
        }
        else
        {
            if( option.state & QStyle::State_Selected )
                image = icon.pixmap(50, QIcon::Selected);
            else
                image = icon.pixmap(50, QIcon::Normal);
        }

        imageLabel->move( 5, 5 );
        imageLabel->setPixmap(image);
        imageLabel->resize( imageSize, imageSize );
    }

    int textStartX = option.rect.x() + 5 + imageSize + 10;
    int textRowHeight = (option.rect.height()-5) / 3;
    QString name;
    QString description;
    qlonglong minimumScore;
    qlonglong currentScore;
    if( model->achievementsManager()->dependencySatisfied(index.row()) )
    {
        name = model->achievementsManager()->achievementName(index.row());
        description = model->achievementsManager()->achievementDescription(index.row());
        minimumScore = model->achievementsManager()->minimumScore(index.row());
        currentScore = qMin( minimumScore, model->achievementsManager()->currentScore(index.row()) );
    }
    else
    {
        int depNumber = model->achievementsManager()->dependency( index.row() );
        if( model->achievementsManager()->dependencySatisfied( depNumber ) )
            description = "Depends on " + model->achievementsManager()->achievementName( depNumber );
        else
            description = "";

        name = "Locked";
        minimumScore = 100;
        currentScore = 0;
    }

    QLabel* nameLabel = qobject_cast<QLabel*>( widgets.at(1) );
    if( nameLabel )
    {
        QFont font;
        font.setBold(true);
        nameLabel->setText( name );
        nameLabel->setFont( font );
        nameLabel->setEnabled( itemIsEnabled );
        nameLabel->move( textStartX, 0 );
        nameLabel->resize( option.rect.width() - textStartX, textRowHeight );
    }

    QLabel* descriptionLabel = qobject_cast<QLabel*>( widgets.at(2) );
    if( descriptionLabel )
    {
        descriptionLabel->setText( description );
        descriptionLabel->setEnabled( itemIsEnabled );
        descriptionLabel->move( textStartX, textRowHeight );
        descriptionLabel->resize( option.rect.width() - textStartX, textRowHeight );
    }

    QProgressBar* progressBar = qobject_cast<QProgressBar*>( widgets.at(3) );
    if( progressBar )
    {
        progressBar->setMinimum( 0 );
        progressBar->setMaximum( 100 );
        progressBar->setValue( 100*currentScore/minimumScore );
        progressBar->setVisible( model->achievementsManager()->dependencySatisfied( index.row() )
                                 && model->achievementsManager()->isPastThreshold( index.row() )
                                 && !model->achievementsManager()->achievementAchieved( index.row() ));
        progressBar->move( textStartX, 2 * textRowHeight );
        progressBar->resize( option.rect.width() - textStartX, textRowHeight );
    }
}

void AchievementDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    const GluonPlayer::AchievementsModel* model = qobject_cast<const GluonPlayer::AchievementsModel*>(index.model());
    if( !model )
    {
        kDebug() << "Warning - Invalid Model! AchievementModel expected.";
        return;
    }

    QApplication::style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter );
}

QSize AchievementDelegate::sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const
{
    return QSize( 300, 60 );
}

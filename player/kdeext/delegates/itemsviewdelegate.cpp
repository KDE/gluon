/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "itemsviewdelegate.h"

#include "views/gametextlabel.h"

#include "lib/models/gameitemsmodel.h"

#include <KDE/KDebug>

#include <QtGui/QPainter>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QApplication>
#include <QtGui/QToolButton>

enum { DelegateGameName, DelegateGameDescription, DelegatePlayButton };

static const int PreviewWidth = 96;
static const int PreviewHeight = 72;

using namespace GluonKDEPlayer;

ItemsViewDelegate::ItemsViewDelegate(QAbstractItemView *itemView, QObject * parent)
        : KWidgetItemDelegate(itemView, parent)
        , m_preview( new KIcon( "gluon_creator" ) )
{
}

ItemsViewDelegate::~ItemsViewDelegate()
{
}

bool ItemsViewDelegate::eventFilter(QObject *watched, QEvent *event)
{
   if (event->type() == QEvent::MouseButtonDblClick) {
       return true;
   }

   return KWidgetItemDelegate::eventFilter(watched, event);
}

QList<QWidget*> ItemsViewDelegate::createItemWidgets() const
{
    QList<QWidget*> list;

    GameTextLabel* gameName = new GameTextLabel();
    gameName->setOpenExternalLinks(true);
    // not so nice - work around constness to install the event filter
    ItemsViewDelegate* delegate = const_cast<ItemsViewDelegate*>(this);
    gameName->installEventFilter(delegate);
    list << gameName;
    connect(gameName, SIGNAL(mouseReleased()), SLOT(selectGameClicked()));

    GameTextLabel* gameDescription = new GameTextLabel();
    gameDescription->setOpenExternalLinks(true);
    list << gameDescription;
    connect(gameDescription, SIGNAL(mouseReleased()), SLOT(selectGameClicked()));

    KPushButton* playButton = new KPushButton();
    playButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
    list << playButton;
    setBlockedEventTypes(playButton, QList<QEvent::Type>() << QEvent::MouseButtonPress
                          << QEvent::MouseButtonRelease << QEvent::MouseButtonDblClick);
    connect(playButton, SIGNAL(clicked()), SLOT(slotPlayClicked()));

    return list;
}

void ItemsViewDelegate::updateItemWidgets(const QList<QWidget*> widgets,
        const QStyleOptionViewItem &option,
        const QPersistentModelIndex &index) const
{
    const GluonPlayer::GameItemsModel* model = qobject_cast<const GluonPlayer::GameItemsModel*>(index.model());
    if (!model) {
        kDebug() << "Warning - Invalid Model!";
        return;
    }

    // setup the install button
    int margin = option.fontMetrics.height() / 2;
    int right = option.rect.width();

    const_cast<QSize&>(m_buttonSize) = QSize(32, 32);

    KPushButton* playButton = qobject_cast<KPushButton*>(widgets.at(DelegatePlayButton));
    if (playButton) {
        playButton->setIcon( KIcon( "media-playback-start" ) );
        playButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
        playButton->resize( m_buttonSize );
        playButton->move( right - playButton->width() - margin, option.fontMetrics.height() + playButton->height() * 0.5);
    }

    GameTextLabel* gameName = qobject_cast<GameTextLabel*>(widgets.at(DelegateGameName));
    // gameName->setWordWrap(true);
    if (gameName) {
        gameName->move(margin + m_buttonSize.width() * 3, option.fontMetrics.height());
        gameName->resize(QSize(option.rect.width() - (margin * 4) - m_buttonSize.width() * 4, option.fontMetrics.height() * 2));
        gameName->setText(index.data(GluonPlayer::GameItemsModel::GameNameRole).toString());
    }

    GameTextLabel* gameDescription = qobject_cast<GameTextLabel*>(widgets.at(DelegateGameDescription));
    // gameName->setWordWrap(true);
    if (gameDescription) {
        gameDescription->move(margin + m_buttonSize.width() * 3,  option.fontMetrics.height() * 1 + gameName->size().height());
        gameDescription->resize(QSize(option.rect.width() - (margin * 4) - m_buttonSize.width() * 4, option.fontMetrics.height() * 2));
        gameDescription->setText(index.data(GluonPlayer::GameItemsModel::GameDescriptionRole).toString());
    }

}

// draws the preview
void ItemsViewDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    int margin = option.fontMetrics.height() / 2;

    QStyle *style = QApplication::style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &option, painter, 0);

    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->setPen(QPen(option.palette.highlightedText().color()));
    } else {
        painter->setPen(QPen(option.palette.text().color()));
    }

    const GluonPlayer::GameItemsModel* realmodel = qobject_cast<const GluonPlayer::GameItemsModel*>(index.model());

    // if (realmodel->hasPreviewImages()) {
    int height = option.rect.height();
    QPoint point(option.rect.left() + margin, option.rect.top() + ((height - PreviewHeight) / 2));

    QImage image = KIcon("gluon-cretor").pixmap(32, 32).toImage();
    if (!image.isNull()) {
        point.setX((PreviewWidth - image.width())/2 + 5);
        point.setY(option.rect.top() + ((height - image.height()) / 2));
        painter->drawImage(point, image);

        QPoint framePoint(point.x() - 5, point.y() - 5);
        painter->drawPixmap(framePoint, KIcon("gluon-creator").pixmap(32, 32).scaled(image.width() + 10, image.height() + 10));
    } else {
        QRect rect(point, QSize(PreviewWidth, PreviewHeight));
        painter->drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, i18n("Loading Preview"));
    }
    // }
    painter->restore();
}

QSize ItemsViewDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& /* index */ ) const
{
    QSize size;
    size.setWidth(option.fontMetrics.height() * 4);
    size.setHeight(qMax(option.fontMetrics.height() * 7, PreviewHeight)); // up to 6 lines of text, and two margins
    return size;
}

void ItemsViewDelegate::slotPlayClicked()
{
    QModelIndex index = focusedIndex();
    if (index.isValid()) {
        emit gameToPlaySelected( index );
    }
}

void ItemsViewDelegate::selectGameClicked()
{
    QModelIndex index = focusedIndex();
    if (index.isValid()) {
        emit gameSelected( index );
    }
}

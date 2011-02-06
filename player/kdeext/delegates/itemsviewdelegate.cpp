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

#include "models/gameitemsmodel.h"

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
        , m_itemView( itemView )
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

    KSqueezedTextLabel* gameName = new KSqueezedTextLabel();
    gameName->setOpenExternalLinks(true);
    // not so nice - work around constness to install the event filter
    ItemsViewDelegate* delegate = const_cast<ItemsViewDelegate*>(this);
    gameName->installEventFilter(delegate);
    list << gameName;

    KSqueezedTextLabel* gameDescription = new KSqueezedTextLabel();
    gameDescription->setOpenExternalLinks(true);
    list << gameDescription;

    KPushButton* playButton = new KPushButton();
    playButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
    list << playButton;
    setBlockedEventTypes(playButton, QList<QEvent::Type>() << QEvent::MouseButtonPress
                          << QEvent::MouseButtonRelease << QEvent::MouseButtonDblClick);
    connect(playButton, SIGNAL(clicked()), SLOT(slotDetailsClicked()));

    return list;
}

void ItemsViewDelegate::updateItemWidgets(const QList<QWidget*> widgets,
        const QStyleOptionViewItem &option,
        const QPersistentModelIndex &index) const
{
    const GameItemsModel* model = qobject_cast<const GameItemsModel*>(index.model());
    if (!model) {
        kDebug() << "Warning - Invalid Model!";
        return;
    }

    GamesViewItem* gamesViewItem = index.data(Qt::UserRole).value<GluonKDEPlayer::GamesViewItem*>();

    // setup the install button
    int margin = option.fontMetrics.height() / 2;
    int right = option.rect.width();

    KPushButton* playButton = qobject_cast<KPushButton*>(widgets.at(DelegatePlayButton));
    if (playButton) {
        playButton->setIcon( KIcon( "media-playback-start" ) );
        playButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
    }

    KSqueezedTextLabel* gameName = qobject_cast<KSqueezedTextLabel*>(widgets.at(DelegateGameName));

    // gameName->setWordWrap(true);
    if (gameName) {
        // if (model->hasPreviewImages()) {
            // // move the text right by kPreviewWidth + margin pixels to fit the preview
            // infoLabel->move(PreviewWidth + margin * 2, 0);
            // infoLabel->resize(QSize(option.rect.width() - PreviewWidth - (margin * 6) - m_buttonSize.width(), option.fontMetrics.height() * 7));

        // } else {
            gameName->move(margin, 0);
            gameName->resize(QSize(option.rect.width() - (margin * 4) - playButton->size().width(), option.fontMetrics.height() * 7));
        // }

        // QString text = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
            // "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; margin:0 0 0 0;}\n"
            // "</style></head><body><p><b>";

        // KUrl link = qvariant_cast<KUrl>(entry.homepage());
        // if (!link.isEmpty()) {
            // text += "<p><a href=\"" + link.url() + "\">" + entry.name() + "</a></p>\n";
        // } else {
            // text += entry.name();
        // }

        // text += "</b></p>\n";

        // QString authorName = entry.author().name();
        // QString email = entry.author().email();
        // QString authorPage = entry.author().homepage();

        // if (!authorName.isEmpty()) {
            // if (!authorPage.isEmpty()) {
                // text += "<p>" + i18nc("Show the author of this item in a list", "By <i>%1</i>", " <a href=\"" + authorPage + "\">" + authorName + "</a>") + "</p>\n";
            // } else if (!email.isEmpty()) {
                // text += "<p>" + i18nc("Show the author of this item in a list", "By <i>%1</i>", authorName) + " <a href=\"mailto:" + email + "\">" + email + "</a></p>\n";
            // } else {
                // text += "<p>" + i18nc("Show the author of this item in a list", "By <i>%1</i>", authorName) + "</p>\n";
            // }
        // }

        // QString summary = "<p>" + option.fontMetrics.elidedText(entry.summary(),
            // Qt::ElideRight, infoLabel->width() * 3) + "</p>\n";
        // text += summary;

        // unsigned int fans = entry.numberFans();
        // unsigned int downloads = entry.downloadCount();

        // QString fanString;
        // QString downloadString;
        // if (fans > 0) {
            // fanString = i18ncp("fan as in supporter", "1 fan", "%1 fans", fans);
        // }
        // if (downloads > 0) {
            // downloadString = i18np("1 download", "%1 downloads", downloads);
        // }
        // if (downloads > 0 || fans > 0) {
            // text += "<p>" + downloadString;
            // if (downloads > 0 && fans > 0) {
                // text += ", ";
            // }
            // text += fanString + QLatin1String("</p>\n");
        // }

        // text += "</body></html>";
        // // use simplified to get rid of newlines etc
        // text = replaceBBCode(text).simplified();
       gameName->setText(gamesViewItem->gameName());
    }

    KSqueezedTextLabel* gameDescription = qobject_cast<KSqueezedTextLabel*>(widgets.at(DelegateGameDescription));
    // gameName->setWordWrap(true);
    if (gameDescription) {
        // if (model->hasPreviewImages()) {
            // // move the text right by kPreviewWidth + margin pixels to fit the preview
            // infoLabel->move(PreviewWidth + margin * 2, 0);
            // infoLabel->resize(QSize(option.rect.width() - PreviewWidth - (margin * 6) - m_buttonSize.width(), option.fontMetrics.height() * 7));

        // } else {
            gameDescription->move(margin, 0);
            gameDescription->resize(QSize(option.rect.width() - (margin * 4) - playButton->size().width(), option.fontMetrics.height() * 7));
            gameDescription->setText(gamesViewItem->gameDescription());
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

    const GameItemsModel* realmodel = qobject_cast<const GameItemsModel*>(index.model());

    // if (realmodel->hasPreviewImages()) {
        int height = option.rect.height();
        QPoint point(option.rect.left() + margin, option.rect.top() + ((height - PreviewHeight) / 2));

        GamesViewItem* gamesViewItem = index.data(Qt::UserRole).value<GluonKDEPlayer::GamesViewItem*>();
        // if (entry.previewUrl(EntryInternal::PreviewSmall1).isEmpty()) {
            // // paint the no preview icon
            // //point.setX((PreviewWidth - m_noImage.width())/2 + 5);
            // //point.setY(option.rect.top() + ((height - m_noImage.height()) / 2));
            // //painter->drawPixmap(point, m_noImage);
        // } else {
            // QImage image = entry.previewImage(EntryInternal::PreviewSmall1);
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

    // }
    painter->restore();
}

QSize ItemsViewDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QSize size;

    size.setWidth(option.fontMetrics.height() * 4);
    size.setHeight(qMax(option.fontMetrics.height() * 7, PreviewHeight)); // up to 6 lines of text, and two margins
    return size;
}


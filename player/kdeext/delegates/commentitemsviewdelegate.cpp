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

#include "commentitemsviewdelegate.h"

#include "views/gametextlabel.h"

#include "lib/models/commentitemsmodel.h"

#include <KDE/KDebug>

#include <QtGui/QPainter>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QApplication>
#include <QtGui/QToolButton>

enum
{
    DelegateCommentAuthor,
    DelegateCommentTitle,
    DelegateCommentBody,
    DelegateCommentDateTime,
    DelegateCommentRating,
    DelegateCommentReplyButton
};

static const int PreviewWidth = 96;
static const int PreviewHeight = 72;

using namespace GluonKDEPlayer;

CommentItemsViewDelegate::CommentItemsViewDelegate( QAbstractItemView* itemView, QObject* parent )
    : KWidgetItemDelegate( itemView, parent )
    , m_preview( new KIcon( "gluon_creator" ) )
{
}

CommentItemsViewDelegate::~CommentItemsViewDelegate()
{
}

bool CommentItemsViewDelegate::eventFilter( QObject* watched, QEvent* event )
{
    if( event->type() == QEvent::MouseButtonDblClick )
    {
        return true;
    }

    return KWidgetItemDelegate::eventFilter( watched, event );
}

QList<QWidget*> CommentItemsViewDelegate::createItemWidgets() const
{
    QList<QWidget*> list;

    KSqueezedTextLabel* author = new KSqueezedTextLabel();
    author->setOpenExternalLinks( true );
    // not so nice - work around constness to install the event filter
    CommentItemsViewDelegate* delegate = const_cast<CommentItemsViewDelegate*>( this );
    author->installEventFilter( delegate );
    list << author;

    KSqueezedTextLabel* title = new KSqueezedTextLabel();
    title->setOpenExternalLinks( true );
    list << title;

    KSqueezedTextLabel* dateTime = new KSqueezedTextLabel();
    dateTime->setOpenExternalLinks( true );
    list << dateTime;

    KSqueezedTextLabel* rating = new KSqueezedTextLabel();
    rating->setOpenExternalLinks( true );
    list << rating;

    KSqueezedTextLabel* body = new KSqueezedTextLabel();
    body->setOpenExternalLinks( true );
    body->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
    list << body;

    KPushButton* replyButton = new KPushButton();
    replyButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
    list << replyButton;
    setBlockedEventTypes( replyButton, QList<QEvent::Type>() << QEvent::MouseButtonPress
                          << QEvent::MouseButtonRelease << QEvent::MouseButtonDblClick );
    connect( replyButton, SIGNAL( clicked() ), SLOT( slotReplyClicked() ) );

    return list;
}

void CommentItemsViewDelegate::updateItemWidgets( const QList<QWidget*> widgets,
        const QStyleOptionViewItem& option,
        const QPersistentModelIndex& index ) const
{
    const GluonPlayer::CommentItemsModel* model = qobject_cast<const GluonPlayer::CommentItemsModel*>( index.model() );
    if( !model )
    {
        kDebug() << "Warning - Invalid Model!";
        return;
    }

    // setup the install button
    int margin = option.fontMetrics.height() / 2;
    int right = option.rect.width();
    int bottom = option.rect.height();

    const_cast<QSize&>( m_buttonSize ) = QSize( 32, 32 );

    KPushButton* replyButton = qobject_cast<KPushButton*>( widgets.at( DelegateCommentReplyButton ) );
    if( replyButton )
    {
        replyButton->setVisible( const_cast<GluonPlayer::CommentItemsModel*>( model )->isOnline() );
        replyButton->setIcon( KIcon( "edit-undo" ) );
        replyButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
        replyButton->resize( m_buttonSize );
        replyButton->move( right - replyButton->width() - margin, bottom - m_buttonSize.height() * 1.5 );
    }

    KSqueezedTextLabel* author = qobject_cast<KSqueezedTextLabel*>( widgets.at( DelegateCommentAuthor ) );
    if( author )
    {
        author->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
        author->resize( right / 5, m_buttonSize.height() );
        author->move( margin, option.fontMetrics.height() );
        author->setText( index.data( GluonPlayer::CommentItemsModel::AuthorRole ).toString() );
    }

    KSqueezedTextLabel* dateTime = qobject_cast<KSqueezedTextLabel*>( widgets.at( DelegateCommentDateTime ) );
    if( dateTime )
    {
        dateTime->resize( author->size().width(), author->size().height() );
        dateTime->move( author->x() + author->size().width(), author->y() );
        dateTime->setText( index.data( GluonPlayer::CommentItemsModel::DateTimeRole ).toString() );
    }

    KSqueezedTextLabel* title = qobject_cast<KSqueezedTextLabel*>( widgets.at( DelegateCommentTitle ) );
    if( title )
    {
        title->resize( dateTime->size().width(), dateTime->size().height() );
        title->move( dateTime->x() + dateTime->size().width(), dateTime->y() );
        title->setText( index.data( GluonPlayer::CommentItemsModel::TitleRole ).toString() );
    }

    KSqueezedTextLabel* rating = qobject_cast<KSqueezedTextLabel*>( widgets.at( DelegateCommentRating ) );
    if( rating )
    {
        rating->resize( title->size().width(), title->size().height() );
        rating->move( title->x() + title->size().width(), title->y() );
        rating->setText( index.data( GluonPlayer::CommentItemsModel::RatingRole ).toString() );
    }

    KSqueezedTextLabel* body = qobject_cast<KSqueezedTextLabel*>( widgets.at( DelegateCommentBody ) );
    if( body )
    {
        body->resize( right - 2 * margin, bottom - author->size().height() - 2 * margin );
        body->move( margin, option.fontMetrics.height()  + author->size().height() );
        body->setText( index.data( GluonPlayer::CommentItemsModel::BodyRole ).toString() );
    }
}

// draws the preview
void CommentItemsViewDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& /* index */ ) const
{
    // int margin = option.fontMetrics.height() / 2;

    QStyle* style = QApplication::style();
    style->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter, 0 );

    painter->save();

    if( option.state & QStyle::State_Selected )
    {
        painter->setPen( QPen( option.palette.highlightedText().color() ) );
    }
    else
    {
        painter->setPen( QPen( option.palette.text().color() ) );
    }

    /* const GluonPlayer::GameItemsModel* realmodel = qobject_cast<const GluonPlayer::GameItemsModel*>(index.model());

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
    } */
    painter->restore();
}

QSize CommentItemsViewDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& /* index */ ) const
{
    QSize size;

    size.setWidth( option.fontMetrics.height() * 4 );
    size.setHeight( qMax( option.fontMetrics.height() * 7, PreviewHeight ) ); // up to 6 lines of text, and two margins
    return size;
}

void CommentItemsViewDelegate::slotReplyClicked()
{
    QModelIndex index = focusedIndex();
    if( index.isValid() )
    {
        emit commentReplyClicked( index );
    }
}

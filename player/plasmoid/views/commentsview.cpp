/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "commentsview.h"
#include "commentsviewitem.h"
#include <models/commentsmodel.h>
#include "newcommentform.h"

#include <Plasma/ItemBackground>
#include <Plasma/LineEdit>
#include <Plasma/Frame>
#include <Plasma/ScrollWidget>

#include <QTreeView>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>

CommentsView::CommentsView( QGraphicsItem* parent, Qt::WindowFlags wFlags )
    : AbstractItemView( parent, wFlags )
    , m_itemBackground( new Plasma::ItemBackground( this ) )
    , m_rootWidget( 0 )
    , m_commentsFrame( new Plasma::Frame( this ) )
    , m_commentsLayout( new QGraphicsLinearLayout( Qt::Vertical, m_commentsFrame ) )
    , m_isOnline( false )
{
    m_commentsFrame->setLayout( m_commentsLayout );
    m_contentLayout->addItem( m_commentsFrame );
}

void CommentsView::setModel( QAbstractItemModel* model )
{
    AbstractItemView::setModel( model );
    connect( model, SIGNAL( modelReset() ), SLOT( reloadComments() ) );

    m_rootWidget = new QGraphicsWidget( m_commentsFrame );
    for( int i = 0; i < m_model->rowCount(); ++i )
    {
        addComment( m_model->index( i, 0 ), m_rootWidget, 0 );
    }
}

CommentsViewItem* CommentsView::addComment( const QModelIndex& index, QGraphicsWidget* parent, int depth )
{
    CommentsViewItem* item = new CommentsViewItem( parent );
    item->setReplyEnabled( qobject_cast<GluonPlayer::CommentsModel*>( m_model )->isOnline() );
    item->setParent( parent );
    item->setDepth( depth );
    item->setModelIndex( index );
    item->setAcceptHoverEvents( true );
    item->installEventFilter( this );
    connect( item, SIGNAL( replyClicked() ), SLOT( showReply() ) );
    item->setRowInLayout( m_commentsLayout->count() );
    m_commentsLayout->addItem( item );

    if( m_model->hasChildren( index ) )  //There are one or more children
    {
        for( int i = 0; i < m_model->rowCount( index ); ++i )
        {
            addComment( index.child( i, 0 ), item, depth + 1 );
        }
    }

    return item;
}

bool CommentsView::eventFilter( QObject* obj, QEvent* event )
{
    if( event->type() == QEvent::GraphicsSceneHoverEnter )
    {
        QGraphicsItem* item = qobject_cast<QGraphicsItem*> ( obj );
        m_itemBackground->setTargetItem( item );
    }

    return QObject::eventFilter( obj, event );
}

void CommentsView::showReply()
{
    CommentsViewItem* parentItem = qobject_cast<CommentsViewItem*>( sender() );

    hideComments();
    NewCommentForm* form = new NewCommentForm( this );
    m_contentLayout->addItem( form );
    form->setParentIndex( parentItem->modelIndex() );

    connect( form, SIGNAL( accepted( QModelIndex, QString, QString ) ),
             SLOT( addNewUserComment( QModelIndex, QString, QString ) ) );
    connect( form, SIGNAL( canceled() ), SLOT( cancelNewComment() ) );
}

void CommentsView::removeComments()
{
    CommentsViewItem* toDelete;
    //TODO: Make the comments view paged
    while( m_commentsLayout->count() > 0 )   //Remove existing comments from GUI
    {
        toDelete = dynamic_cast<CommentsViewItem*>( m_commentsLayout->itemAt( 0 ) );
        m_commentsLayout->removeAt( 0 );
        toDelete->deleteLater();
    }
}

void CommentsView::loadComments()
{
    for( int i = 0; i < m_model->rowCount(); ++i )  //Reload comments
    {
        addComment( m_model->index( i, 0 ), m_rootWidget, 0 );
    }
}

void CommentsView::reloadComments()
{
    hideComments();
    removeComments();
    loadComments();
    showComments();
}

void CommentsView::addNewUserComment( QModelIndex parentIndex, QString title, QString body )
{
    GluonPlayer::CommentsModel* model = static_cast<GluonPlayer::CommentsModel*>( m_model );
    model->uploadComment( parentIndex, title, body );
    connect( model, SIGNAL( addCommentFailed() ), SLOT( showComments() ) );
    sender()->deleteLater();
}

void CommentsView::cancelNewComment()
{
    sender()->deleteLater();
    showComments();
}

void CommentsView::hideComments()
{
    m_commentsFrame->hide();
    m_contentLayout->removeItem( m_commentsFrame );
}

void CommentsView::showComments()
{
    m_contentLayout->addItem( m_commentsFrame );
    m_commentsFrame->show();
}

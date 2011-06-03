/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "messageview.h"

#include <core/gluon_global.h>
#include <engine/game.h>

#include <KDE/KLocalizedString>
#include <KDE/KToolBar>
#include <KDE/KAction>

// Yup, this should be a view... but for now...
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QApplication>
#include <QtGui/QClipboard>

using namespace GluonCreator;

class MessageView::MessageViewPrivate
{
    public:
        MessageViewPrivate()
        {
            view = 0;
        }
        QListWidget* view;
};

MessageView::MessageView( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags ),
      d( new MessageViewPrivate )
{
    setObjectName( "MessageView" );

    d->view = new QListWidget( this );
    d->view->addItem( new QListWidgetItem( i18n( "Welcome to Gluon Creator %1", GluonCore::Global::versionString() ), d->view ) );
    d->view->setSelectionMode( QAbstractItemView::ExtendedSelection );

    connect( GluonEngine::Game::instance(), SIGNAL( showDebug( const QString& ) ), SLOT( showDebug( const QString& ) ) );

    QWidget* widget = new QWidget( this );
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );

    KToolBar* toolBar = new KToolBar( this );
    toolBar->setIconDimensions( 16 );

    QAction* selectAll = toolBar->addAction( KIcon( "edit-select-all" ), i18n( "Select All" ), this, SLOT( selectAll() ) );
    d->view->addAction( selectAll );

    QAction* copy = toolBar->addAction( KIcon( "edit-copy" ), i18n( "Copy" ), this, SLOT( copy() ) );
    d->view->addAction( copy );

    KAction* separator = new KAction( d->view );
    separator->setSeparator( true );
    d->view->addAction( separator );

    QAction* clearSelection = toolBar->addAction( KIcon( "edit-clear-list" ), i18n( "Clear Selection" ), this, SLOT( clearSelection() ) );
    d->view->addAction( clearSelection );

    QAction* clearAll = toolBar->addAction( KIcon( "edit-clear" ), i18n( "Clear All" ), d->view, SLOT( clear() ) );
    d->view->addAction( clearAll );

    layout->addWidget( toolBar );
    layout->addWidget( d->view );

    setLayout( layout );
}

void MessageView::showDebug( const QString& debugText )
{
    QListWidgetItem* item = new QListWidgetItem( debugText, d->view );
    d->view->addItem( item );
    d->view->scrollToItem( item );
}

MessageView::~MessageView()
{
    delete d;
}

void MessageView::copy()
{
    QStringList messages;
    foreach( QListWidgetItem * item, d->view->selectedItems() )
    messages << item->text();

    QApplication::clipboard()->setText( messages.join( "\n" ) );
}

void MessageView::selectAll()
{
    int itemsCount = d->view->count();
    for( int i = 0; i < itemsCount; ++i )
        d->view->item( i )->setSelected( true );
}

void MessageView::clearSelection()
{
    int itemsCount = d->view->count();
    for( int i = 0; i < itemsCount; ++i )
        d->view->item( i )->setSelected( false );
}

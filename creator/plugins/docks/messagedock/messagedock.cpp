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

#include "messagedock.h"

#include <gluon_global.h>
#include <engine/game.h>
#include <core/log.h>

#include <KI18n/KLocalizedString>
#include <KXmlGui/KToolBar>

// Yup, this should be a view... but for now...
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtGui/QClipboard>

using namespace GluonCreator;

class MessageDock::MessageDockPrivate
{
    public:
        MessageDockPrivate()
        {
            view = 0;
        }

        QIcon logLevelToIcon( GluonCore::LogLevel level );

        QListWidget* view;
};

MessageDock::MessageDock( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QDockWidget( title, parent, flags ),
      d( new MessageDockPrivate )
{
    setObjectName( "MessageDock" );

    d->view = new QListWidget( this );
//     d->view->addItem( new QListWidgetItem( i18n( "Welcome to Gluon Creator %1", GluonCore::Global::versionString() ), d->view ) );
    d->view->setSelectionMode( QAbstractItemView::ExtendedSelection );

//     connect( GluonEngine::Game::instance(), SIGNAL(showDebug(QString,GluonCore::DebugType)), SLOT(showDebug(QString,GluonCore::DebugType)) );
    connect( GluonCore::Log::instance(), &GluonCore::Log::newMessage, this, &MessageDock::newMessage );

    QWidget* widget = new QWidget( this );
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );
    widget->setLayout( layout );

    KToolBar* toolBar = new KToolBar( this );
    toolBar->setIconDimensions( 16 );

    QAction* selectAll = toolBar->addAction( QIcon::fromTheme( "edit-select-all" ), i18n( "Select All" ), this, SLOT(selectAll()) );
    d->view->addAction( selectAll );

    QAction* copy = toolBar->addAction( QIcon::fromTheme( "edit-copy" ), i18n( "Copy" ), this, SLOT(copy()) );
    d->view->addAction( copy );

    QAction* separator = new QAction( d->view );
    separator->setSeparator( true );
    d->view->addAction( separator );

    QAction* clearSelection = toolBar->addAction( QIcon::fromTheme( "edit-clear-list" ), i18n( "Clear Selection" ), this, SLOT(clearSelection()) );
    d->view->addAction( clearSelection );

    QAction* clearAll = toolBar->addAction( QIcon::fromTheme( "edit-clear" ), i18n( "Clear All" ), d->view, SLOT(clear()) );
    d->view->addAction( clearAll );

    layout->addWidget( toolBar );
    layout->addWidget( d->view );
    setWidget( widget );

    INFO() << "Welcome to Gluon Creator " << GluonCore::Global::versionString() << " (" << GluonCore::Global::versionName() << ")";
}

void MessageDock::showDebug( const QString& debugText, const GluonCore::DebugType& debugType )
{
    QListWidgetItem* item = new QListWidgetItem( debugText, d->view );
    d->view->addItem( item );
    d->view->scrollToItem( item );
}

MessageDock::~MessageDock()
{
    delete d;
}

void MessageDock::copy()
{
    QStringList messages;
    foreach( QListWidgetItem * item, d->view->selectedItems() )
    messages << item->text();

    QApplication::clipboard()->setText( messages.join( "\n" ) );
}

void MessageDock::selectAll()
{
    int itemsCount = d->view->count();
    for( int i = 0; i < itemsCount; ++i )
        d->view->item( i )->setSelected( true );
}

void MessageDock::clearSelection()
{
    int itemsCount = d->view->count();
    for( int i = 0; i < itemsCount; ++i )
        d->view->item( i )->setSelected( false );
}

void MessageDock::newMessage( const GluonCore::LogData& message )
{
    if( message.category == GluonCore::QtCategory || message.level == GluonCore::LogDebug )
        return;

    QListWidgetItem* item = new QListWidgetItem( d->view );
    item->setIcon( d->logLevelToIcon( message.level ) );
    item->setText( "[" + message.time.toString( "HH:mm:ss" ) + "] " + message.message );
}

QIcon MessageDock::MessageDockPrivate::logLevelToIcon( GluonCore::LogLevel level )
{
    switch( level )
    {
        case GluonCore::LogCritical:
        case GluonCore::LogError:
            return QIcon::fromTheme( "dialog-error" );
        case GluonCore::LogWarning:
            return QIcon::fromTheme( "dialog-warning" );
        case GluonCore::LogInfo:
        case GluonCore::LogNotice:
            return QIcon::fromTheme( "dialog-information" );
        default:
            return QIcon();
    };
}

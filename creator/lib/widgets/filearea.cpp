/*****************************************************************************
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

#include "filearea.h"

#include "filemanager.h"

#include <core/debughelper.h>

#include <KDE/KParts/PartManager>
#include <KDE/KParts/ReadOnlyPart>
#include <KDE/KTabBar>
#include <KDE/KToolBar>
#include <KDE/KIcon>

#include <QtGui/QVBoxLayout>

using namespace GluonCreator;

class FileArea::Private
{
    public:
        Private()
            : currentPart( 0 ),
              tabBar( 0 ),
              toolBar( 0 ),
              layout( 0 )
        { }
        ~Private() { }

        void activePartChanged( KParts::Part* part );
        void tabMoved( int from, int to );
        void tabCloseRequested( int tab );

        KParts::Part* currentPart;

        KTabBar* tabBar;
        KToolBar* toolBar;

        QVBoxLayout* layout;

        QHash<QString, int> tabs;
};

FileArea::FileArea( QWidget* parent, Qt::WindowFlags f )
    : QWidget( parent, f ),
      d( new Private )
{
    d->layout = new QVBoxLayout( this );

    d->tabBar = new KTabBar( this );
    d->tabBar->setTabsClosable( true );
    d->tabBar->setDocumentMode( true );
    d->tabBar->setMovable( true );
    d->layout->addWidget( d->tabBar );
    d->tabBar->setExpanding( false );
    d->tabBar->setSelectionBehaviorOnRemove( QTabBar::SelectPreviousTab );

    connect( d->tabBar, SIGNAL(tabCloseRequested(int)), SLOT(tabCloseRequested(int)) );
    connect( d->tabBar, SIGNAL(currentChanged(int)), SLOT(setActiveTab(int)) );
    connect( d->tabBar, SIGNAL(tabMoved(int,int)), SLOT(tabMoved(int,int)) );

    d->toolBar = new KToolBar( "mainToolBar", this );
    d->layout->addWidget( d->toolBar );
    d->layout->setSpacing( 0 );
    d->layout->setContentsMargins( 0, 0, 0, 0 );

    setLayout( d->layout );

    connect( FileManager::instance(), SIGNAL(newPart(QString,QString,QString)), SLOT(addTab(QString,QString,QString)) );
    connect( FileManager::instance()->partManager(), SIGNAL(activePartChanged(KParts::Part*)), SLOT(activePartChanged(KParts::Part*)) );
    connect( FileManager::instance(), SIGNAL(fileClosed(QString)), SLOT(removeTab(QString)) );
}

FileArea::~FileArea()
{

}

void FileArea::addTab( const QString& name, const QString& title, const QString& icon )
{
    if( d->tabs.contains( name ) )
    {
        d->tabBar->setCurrentIndex( d->tabs.value( name ) );
        d->tabBar->setTabText( d->tabBar->currentIndex(), title );
        if( !icon.isEmpty() )
            d->tabBar->setTabIcon( d->tabBar->currentIndex(), KIcon( icon ) );
        return;
    }

    int tab;
    if( !icon.isEmpty() )
    {
        tab = d->tabBar->addTab( KIcon( icon ), title );
    }
    else
    {
        tab = d->tabBar->addTab( title );
    }

    d->tabs.insert( name, tab );
    d->tabBar->setCurrentIndex( tab );
}

void FileArea::removeTab( const QString& name )
{
    removeTab( d->tabs.value( name ) );
}

void FileArea::removeTab( int index )
{
    d->tabs.remove( d->tabs.key( index ) );

    for( QHash<QString, int>::iterator itr = d->tabs.begin(); itr != d->tabs.end(); ++itr )
    {
        if( itr.value() > index )
            itr.value()--;
    }

    d->tabBar->removeTab( index );
}

void FileArea::setActiveTab( int index )
{
    setActiveTab( d->tabs.key( index ) );
}

void FileArea::setActiveTab( const QString& name )
{
    KParts::Part* part = FileManager::instance()->part( name );
    if( !part )
        return;

    d->tabBar->setCurrentIndex( d->tabs.value( name ) );
    FileManager::instance()->setCurrentFile( name );
}

void FileArea::Private::activePartChanged( KParts::Part* part )
{
    if( currentPart )
    {
        layout->removeWidget( currentPart->widget() );
        currentPart->widget()->hide();
    }

    if( !part )
    {
        currentPart = 0;
        return;
    }

    layout->addWidget( part->widget() );
    part->widget()->show();

    currentPart = part;
}

void FileArea::Private::tabMoved( int from, int to )
{
    QString name = tabs.key( from );
    tabs.insert( name, to );
}

void FileArea::Private::tabCloseRequested(int tab)
{
    FileManager::instance()->closeFile( tabs.key( tab ) );
}

#include "moc_filearea.cpp"

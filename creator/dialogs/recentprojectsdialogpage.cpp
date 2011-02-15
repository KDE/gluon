/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Keith Rusler <xzekecomax@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "recentprojectsdialogpage.h"

#include <KDE/KLocalizedString>
#include <KDE/KIcon>
#include <KDE/KGlobal>
#include <KDE/KConfig>
#include <KDE/KConfigGroup>

#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QListWidget>

using namespace GluonCreator;

class RecentProjectsDialogPage::RecentProjectsDialogPagePrivate
{
    public:
        RecentProjectsDialogPagePrivate( RecentProjectsDialogPage* qq )
            : widget( 0 ),
              q( qq )
        {
        }

        void projectDoubleClicked( const QModelIndex& index )
        {
            QListWidgetItem* item = static_cast<QListWidgetItem*>( index.internalPointer() );
            if( item )
                emit q->projectRequested( item->data( Qt::UserRole ).toString() );
        }
    public:
        QListWidget* widget;
    private:
        RecentProjectsDialogPage* q;
};

RecentProjectsDialogPage::RecentProjectsDialogPage()
    : KPageWidgetItem( new QWidget(), i18n( "Recent Projects" ) ),
      d( new RecentProjectsDialogPagePrivate( this ) )
{
    setIcon( KIcon( "document-open-recent" ) );

    d->widget = new QListWidget( widget() );
    connect( d->widget, SIGNAL( doubleClicked( QModelIndex ) ),
             SLOT( projectDoubleClicked( QModelIndex ) ) );

    QVBoxLayout* layout = new QVBoxLayout( widget() );
    widget()->setLayout( layout );
    layout->addWidget( d->widget );

    const KConfigGroup group = KGlobal::config()->group( "Recent Files" );
    const int entryCount = ( group.entryMap().count() / 2 );

    for( int i = entryCount; i >= 1; --i )
    {
        const QString key = QString( "File%1" ).arg( i );
        const QString path = group.readPathEntry( key, QString() );

        QListWidgetItem* item = new QListWidgetItem;
        item->setIcon( KIcon( "document-open-recent" ) );
        QString projectName = KUrl( path ).directory().split('/').last();
        item->setText( QString( "%1\n%2" ).arg( projectName ).arg( path ) );
        item->setData( Qt::UserRole, path );
        d->widget->addItem( item );
    }
}

RecentProjectsDialogPage::~RecentProjectsDialogPage()
{
    delete d;
}

QString RecentProjectsDialogPage::selectedItem() const
{
    QListWidgetItem* item = d->widget->currentItem();
    if( item )
        return item->data( Qt::UserRole ).toString();
    return QString();
}

#include "recentprojectsdialogpage.moc"

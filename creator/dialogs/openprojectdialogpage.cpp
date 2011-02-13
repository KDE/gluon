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

#include "openprojectdialogpage.h"

#include "core/debughelper.h"
#include "engine/gameproject.h"

#include <KDE/KFile>
#include <KDE/KFileWidget>
#include <KDE/KIcon>
#include <KDE/KLocale>

#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>

using namespace GluonCreator;

class OpenProjectDialogPage::OpenProjectDialogPagePrivate
{
    public:
        explicit OpenProjectDialogPagePrivate( OpenProjectDialogPage* qq )
            : fileWidget( 0 ),
              q( qq )
        {
        }

        void projectSelected( const KUrl& url )
        {
            fileWidget->accept();
            emit q->projectRequested( url.url().remove( "file://" ) );
        }
    public:
        KFileWidget* fileWidget;
    private:
        OpenProjectDialogPage* q;
};

OpenProjectDialogPage::OpenProjectDialogPage()
    : KPageWidgetItem( new QWidget(), i18n( "Open Project" ) ),
      d( new OpenProjectDialogPagePrivate( this ) )
{
    setIcon( KIcon( "document-open" ) );

    d->fileWidget = new KFileWidget( KUrl( "kfiledialog:///OpenDialog" ), widget() );
    connect( d->fileWidget, SIGNAL( fileHighlighted( KUrl ) ),
             SLOT( projectSelected( KUrl ) ) );

    d->fileWidget->setOperationMode( KFileWidget::Opening );
    d->fileWidget->setFilter( QString( "*%1|Gluon Project Files" ).arg( GluonEngine::projectSuffix ) );
    d->fileWidget->setMode( KFile::File | KFile::ExistingOnly );
    d->fileWidget->setLocationLabel( i18n( "Project" ) );

    QVBoxLayout* layout = new QVBoxLayout;
    widget()->setLayout( layout );
    layout->addWidget( d->fileWidget );
}

OpenProjectDialogPage::~OpenProjectDialogPage()
{
    delete d;
}

#include "creator/dialogs/openprojectdialogpage.moc"

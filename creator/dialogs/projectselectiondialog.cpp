/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Keith Rusler <xzekecomax@gmail.com>
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

#include "projectselectiondialog.h"

#include <KDE/KLocalizedString>
#include <KDE/KConfig>

#include "newprojectdialogpage.h"
#include "recentprojectsdialogpage.h"
#include "openprojectdialogpage.h"

#include <core/debughelper.h>

using namespace GluonCreator;

class ProjectSelectionDialog::ProjectSelectionDialogPrivate
{
    public:
        explicit ProjectSelectionDialogPrivate( ProjectSelectionDialog* qq )
            : q( qq )
        {
            pages.clear();
        }

        void okClicked()
        {
            if( pages.key( q->currentPage() ) == ProjectSelectionDialog::NewProjectPage )
            {
                NewProjectDialogPage* page = static_cast<NewProjectDialogPage*>( q->currentPage() );
                if( page )
                    fileName = page->createProject();
            }

            if( pages.key( q->currentPage() ) == ProjectSelectionDialog::RecentProjectPage )
            {
                RecentProjectsDialogPage* page = static_cast<RecentProjectsDialogPage*>( q->currentPage() );
                if( page )
                    fileName = page->selectedItem();
            }

        }

        void projectRequested( const QString& project )
        {
            fileName = project;
            q->accept();
        }
    public:
        QHash<ProjectPage, KPageWidgetItem*> pages;
        QString fileName;
    private:
        ProjectSelectionDialog* q;
};

ProjectSelectionDialog::ProjectSelectionDialog( QWidget* parent, Qt::WFlags flags )
    : KPageDialog( parent, flags ),
      d( new ProjectSelectionDialogPrivate( this ) )
{
    setFaceType( List );
    setButtons( Ok | Close );

    addPage( new NewProjectDialogPage, NewProjectPage );
    addPage( new RecentProjectsDialogPage, RecentProjectPage );
    addPage( new OpenProjectDialogPage, OpenProjectPage );

    restoreDialogSize( KGlobal::config()->group( "ProjectSelectionDialog" ) );

    connect( this, SIGNAL( okClicked() ),
             SLOT( okClicked() ) );
}

ProjectSelectionDialog::~ProjectSelectionDialog()
{
    KConfigGroup group = KGlobal::config()->group( "ProjectSelectionDialog" );
    saveDialogSize( group );
    delete d;
}

void ProjectSelectionDialog::addPage( KPageWidgetItem* item, ProjectSelectionDialog::ProjectPage page )
{
    DEBUG_FUNC_NAME
    switch( page )
    {
        case NewProjectPage:
            DEBUG_TEXT( "New" );
            break;
        case OpenProjectPage:
        {
            DEBUG_TEXT( "Open" );
            connect( item, SIGNAL( projectRequested( QString ) ),
                     SLOT( projectRequested( QString ) ) );
            break;
        }
        case RecentProjectPage:
            DEBUG_TEXT( "Recent" );
            connect( item, SIGNAL( projectRequested( QString ) ),
                     SLOT( projectRequested( QString ) ) );
            break;
        default:
            DEBUG_TEXT( "Unknown Project Page" );
            break;
    };

    d->pages.insert( page, item );
    KPageDialog::addPage( item );
}

QString ProjectSelectionDialog::fileName() const
{
    return d->fileName;
}

void ProjectSelectionDialog::setPage( ProjectSelectionDialog::ProjectPage page )
{
    setCurrentPage( d->pages[page] );
}

#include "creator/dialogs/projectselectiondialog.moc"

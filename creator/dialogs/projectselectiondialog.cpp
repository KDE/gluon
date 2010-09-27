/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
        ProjectSelectionDialogPrivate() { }
        
        NewProjectDialogPage *newPage;
        RecentProjectsDialogPage *recentPage;
        OpenProjectDialogPage *openPage;
        
        QString fileName;
};

ProjectSelectionDialog::ProjectSelectionDialog(QWidget* parent, Qt::WFlags flags)
    : KPageDialog(parent, flags),
    d(new ProjectSelectionDialogPrivate)
{
    setFaceType(List);
    setButtons(KDialog::Ok | KDialog::Close);
    
    restoreDialogSize(KGlobal::config()->group("ProjectSelectionDialog"));

    d->newPage = new NewProjectDialogPage();
    addPage(d->newPage);
    
    d->recentPage = new RecentProjectsDialogPage();
    connect(d->recentPage, SIGNAL(projectRequested(QString)),
            SLOT(slotProjectRequested(QString)));
    addPage(d->recentPage);
    
    d->openPage = new OpenProjectDialogPage();
    addPage(d->openPage);
}

ProjectSelectionDialog::~ProjectSelectionDialog()
{
    KConfigGroup group = KGlobal::config()->group("ProjectSelectionDialog");
    saveDialogSize(group);
    delete d;
}

QString ProjectSelectionDialog::fileName()
{
    return d->fileName;
}

void ProjectSelectionDialog::slotButtonClicked(int button)
{
    DEBUG_FUNC_NAME
    if(button == KDialog::Ok)
    {
        if(currentPage() == d->newPage)
	{
	    DEBUG_TEXT("New");
            d->fileName = d->newPage->fileName();
	}
        else if(currentPage() == d->recentPage)
	{
	    DEBUG_TEXT("Recent");
            d->fileName = d->recentPage->fileName();
	}
        else if(currentPage() == d->openPage)
	{
	    DEBUG_TEXT("Open");
            d->fileName = d->openPage->fileName();
	}
	DEBUG_TEXT(d->fileName);
    
        if(d->fileName.isEmpty())
        {
            return;
        }
        else
        {
            KDialog::slotButtonClicked(button);
        }
    }
    else
    {
        KDialog::slotButtonClicked(button);
    }
}

void ProjectSelectionDialog::setPage(ProjectSelectionDialog::ProjectPage page)
{
    switch(page)
    {
        case PROJECTPAGE_NEW:
            setCurrentPage(d->newPage);
            break;
        case PROJECTPAGE_OPEN:
            setCurrentPage(d->openPage);
            break;
        case PROJECTPAGE_RECENT:
            setCurrentPage(d->recentPage);
            break;
    }
}

void ProjectSelectionDialog::slotProjectRequested(const QString& project)
{
    d->fileName = project;
    slotButtonClicked(Ok);
}

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

#include "openprojectdialogpage.h"

#include <QtGui/QWidget>

#include <KDE/KLocalizedString>
#include <KDE/KIcon>
#include <KFileWidget>
#include <QVBoxLayout>

using namespace GluonCreator;

class OpenProjectDialogPage::OpenProjectDialogPagePrivate
{
    public:
        KFileWidget *fileWidget;
};

GluonCreator::OpenProjectDialogPage::OpenProjectDialogPage()
    : KPageWidgetItem(new QWidget(), i18n("Open Project")),
    d(new OpenProjectDialogPagePrivate)
{
    setHeader(i18n("Open Project"));
    setIcon(KIcon("document-open"));
    
    d->fileWidget = new KFileWidget(KUrl("kfiledialog:///OpenDialog"), widget());
    d->fileWidget->setFilter(i18n("*.gluon|Gluon Project Files"));
    
    QVBoxLayout *layout = new QVBoxLayout();
    widget()->setLayout(layout);
    
    layout->addWidget(d->fileWidget);
}

GluonCreator::OpenProjectDialogPage::~OpenProjectDialogPage()
{
    delete d;
}

QString GluonCreator::OpenProjectDialogPage::fileName()
{
    return d->fileWidget->selectedFile();
}

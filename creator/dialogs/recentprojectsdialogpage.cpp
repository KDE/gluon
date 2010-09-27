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

#include "recentprojectsdialogpage.h"

#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QListWidget>

#include <KDE/KLocalizedString>
#include <KDE/KIcon>
#include <KDE/KGlobal>
#include <KDE/KConfig>
#include <KDE/KConfigGroup>

using namespace GluonCreator;

class RecentProjectsDialogPage::RecentProjectsDialogPagePrivate
{
    public:
        RecentProjectsDialogPagePrivate(RecentProjectsDialogPage* qq)
            : widget(0),
            q(qq)
        {
        }
    public:
        QListWidget *widget;
    public:
        void projectDoubleClicked(const QModelIndex& index)
        {
            QListWidgetItem* project = static_cast<QListWidgetItem*>(index.internalPointer());
            emit q->projectRequested(project->data(Qt::UserRole).toString());
        }
    private:
        RecentProjectsDialogPage* q;
};

GluonCreator::RecentProjectsDialogPage::RecentProjectsDialogPage()
    : KPageWidgetItem(new QWidget(), i18n("Recent Projects")),
    d(new RecentProjectsDialogPagePrivate(this))
{
    setHeader(i18n("Recent Projects"));
    setIcon(KIcon("document-open-recent"));
    
    d->widget = new QListWidget(widget());
    connect(d->widget, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(projectDoubleClicked(QModelIndex)));
    
    QVBoxLayout *layout = new QVBoxLayout(widget());
    widget()->setLayout(layout);
    
    layout->addWidget(d->widget);
    
    const KConfigGroup group = KGlobal::config()->group("Recent Files");
    
    int entryCount = (group.entryMap().count() / 2);
    for(int i = entryCount; i >= 1; --i)
    {
        QString key = QString("File%1").arg(i);
        QString path = group.readPathEntry(key, QString());
        
        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon(KIcon("document-open-recent"));
        item->setText(QString("%1\n%2").arg(KUrl(path).fileName()).arg(path));
        item->setData(Qt::UserRole, path);
        d->widget->addItem(item);
    }
}

GluonCreator::RecentProjectsDialogPage::~RecentProjectsDialogPage()
{
    delete d;
}

QString RecentProjectsDialogPage::fileName()
{
    return d->widget->selectedItems().at(0)->data(Qt::UserRole).toString();
}

#include "creator/dialogs/recentprojectsdialogpage.moc"

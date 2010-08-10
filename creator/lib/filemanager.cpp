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

#include "filemanager.h"

#include <QtGui/QVBoxLayout>

#include <KDE/KMimeType>
#include <KDE/KMimeTypeTrader>
#include <KDE/KRun>
#include <KDE/KService>
#include <KDE/KTabWidget>
#include <KDE/KToolBar>

#include <KDE/KParts/ReadWritePart>
#include <KDE/KParts/PartManager>

#include <core/debughelper.h>
#include <engine/asset.h>
#include <KActionCollection>
#include <qactiongroup.h>

using namespace GluonCreator;

template<> GLUON_CREATOR_VISIBILITY FileManager* GluonCore::Singleton<FileManager>::m_instance = 0;

class FileManager::FileManagerPrivate
{
    public:
        KTabWidget *tabWidget;

        KToolBar *mainToolBar;
        KParts::PartManager *partManager;
        
        QHash<QString, KParts::ReadOnlyPart*> parts;
        QHash<QString, int> tabs;
};

KTabWidget* FileManager::tabWidget()
{
    return d->tabWidget;
}

KParts::PartManager* FileManager::partManager()
{
    return d->partManager;
}

void FileManager::openAsset( GluonEngine::Asset* asset )
{
    if(!asset)
        return;

    openFile(asset->absolutePath(), asset->name());
}

void FileManager::openFile( const QString& fileName, const QString& name )
{
    if(fileName.isEmpty())
        return;
    
    QString tabName = name.isEmpty() ? KUrl(fileName).fileName() : name;
    if(d->parts.contains(tabName))
    {
        d->tabWidget->setCurrentIndex(d->tabs.value(tabName));
        return;
    }

    KMimeType::Ptr mime = KMimeType::findByPath(fileName);

    //Find a read-write kpart
    KParts::ReadOnlyPart *part = 0;
    KService::List parts = KMimeTypeTrader::self()->query(mime->name(), "KParts/ReadWritePart");
    if(parts.count() > 0)
    {
        part = parts.first()->createInstance<KParts::ReadWritePart>( qobject_cast<QObject*>( d->tabWidget ) );
    }
    else
    {
        //Apparently, there was no read/write part that could be instantiated, so try to find a read-only part
        parts = KMimeTypeTrader::self()->query(mime->name(), "KParts/ReadOnlyPart");
        //Nasty, nasty, nasty
        //Hack to force embed dragonplayer_part when trying to open an audio file, as that is not
        //by default associated with audio files...
        if(mime->name().contains("audio") && parts.count() == 0)
            parts.prepend(KService::serviceByDesktopPath("dragonplayer_part.desktop"));

        if(parts.count() > 0)
        {
            part = parts.first()->createInstance<KParts::ReadOnlyPart>( qobject_cast<QObject*>( d->tabWidget ) );
        }
    }

    if(part)
    {
        //Add the part if it is found
        KUrl url(fileName);
        part->openUrl(url);
        d->parts.insert(tabName, part);
        d->partManager->addPart(part, false);
        
        KToolBar* toolBar = addTab(part->widget(), tabName);
        
        QDomNodeList actions;
        QDomNodeList toolBars = part->domDocument().elementsByTagName("ToolBar");

        //Slight workaround to handle KatePart
        if(toolBars.count() == 0 && part->childClients().count() > 0)
            toolBars = part->childClients().at(0)->domDocument().elementsByTagName("ToolBar");
        
        int i = -1;
        while(++i < toolBars.count())
        {
            if(toolBars.at(i).attributes().namedItem("name").nodeValue() == "mainToolBar")
            {
                actions = toolBars.at(i).childNodes();
            }
        }

        DEBUG_BLOCK
        i = -1;
        while(++i < actions.count())
        {
            if(actions.at(i).nodeName() == "Action")
            {
                toolBar->addAction(part->action(actions.at(i).attributes().namedItem("name").nodeValue().toUtf8()));
            }
        }

        return;
    }

    //Nope, there really is no part that can be used.
    //So instead, just open it in an external application.
    KRun* runner = new KRun(KUrl(fileName), d->tabWidget);
    Q_UNUSED(runner);

}

void FileManager::setTabWidget( KTabWidget* widget )
{
    d->tabWidget = widget;
    connect(d->tabWidget, SIGNAL(closeRequest(QWidget*)), SLOT(closeTab(QWidget*)));
    connect(d->tabWidget, SIGNAL(currentChanged(int)), SLOT(tabChanged(int)));

    d->partManager = new KParts::PartManager(d->tabWidget);
}

void FileManager::closeTab( QWidget* widget )
{
    /*if(widget->objectName() == "gluon_viewer_part" || widget->objectName() == "gluon_editor_part")
        return;*/

    int tab = d->tabWidget->indexOf(widget);
    QString partName = d->tabs.key(tab);

    d->parts.remove(partName);
    d->tabs.remove(partName);
    
    widget->deleteLater();
}

void FileManager::tabChanged( int index )
{
    QString partName = d->tabs.key(index);
    d->partManager->setActivePart(d->parts.value(partName));
}

FileManager::FileManager()
    : d(new FileManagerPrivate)
{

}

FileManager::~FileManager()
{
    delete d;
}

KToolBar* FileManager::addTab( QWidget* widget, const QString& name )
{
    Q_ASSERT(widget);
    
    QWidget *base = new QWidget();
    base->setObjectName(name);
    QVBoxLayout *layout = new QVBoxLayout();
    base->setLayout(layout);

    KToolBar* toolBar = new KToolBar(base);
    toolBar->setIconDimensions(16);
    layout->addWidget(toolBar);
    layout->addWidget(widget);

    int id = d->tabWidget->addTab(base, name);
    d->tabs.insert(name, id);
    d->tabWidget->setCurrentIndex(id);

    return toolBar;
}


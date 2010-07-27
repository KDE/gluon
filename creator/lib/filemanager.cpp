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

#include <KDE/KTabWidget>
#include <KDE/KService>
#include <KDE/KMimeTypeTrader>
#include <KDE/KParts/ReadWritePart>
#include <KDE/KMimeType>

#include <core/debughelper.h>
#include <KRun>
#include <QVBoxLayout>
#include <KToolBar>
#include <engine/asset.h>

using namespace GluonCreator;

template<> GLUON_CREATOR_VISIBILITY FileManager* GluonCore::Singleton<FileManager>::m_instance = 0;

class FileManager::FileManagerPrivate
{
    public:
        KTabWidget *tabWidget;
        
};

KTabWidget* FileManager::tabWidget()
{
    return d->tabWidget;
}

void FileManager::openAsset( GluonEngine::Asset* asset )
{
    if(!asset)
        return;

    QString file = asset->absolutePath();
    KMimeType::Ptr mime = KMimeType::findByPath(file);

    //Find a read-write kpart
    KService::List parts = KMimeTypeTrader::self()->query(mime->name(), "KParts/ReadWritePart");
    if(parts.count() > 0)
    {
        KParts::ReadWritePart *part = parts.first()->createInstance<KParts::ReadWritePart>( qobject_cast<QObject*>( d->tabWidget ) );
        if(part)
        {
            //Add the part if it is found]
            KUrl url(file);
            part->openUrl(url);
            addTab(part->widget(), asset->name());

            return;
        }
    }

    //Apparently, there was no read/write part that could be instantiated, so try to find a read-only part
    parts = KMimeTypeTrader::self()->query(mime->name(), "KParts/ReadOnlyPart");
    //Nasty, nasty, nasty
    //Hack to force embed dragonplayer_part when trying to open an audio file, as that is not
    //by default associated with audio files...
    if(mime->name().contains("audio"))
        parts.prepend(KService::serviceByDesktopPath("dragonplayer_part.desktop"));
    
    if(parts.count() > 0)
    {
        KParts::ReadOnlyPart *part = parts.first()->createInstance<KParts::ReadOnlyPart>( qobject_cast<QObject*>( d->tabWidget ) );
        if(part)
        {
            //Add the part if it is found
            KUrl url(file);
            part->openUrl(url);
            addTab(part->widget(), asset->name());

            return;
        }
    }

    //Nope, there really is no part that can be used.
    //So instead, just open it in an external application.
    KRun* runner = new KRun(KUrl(file), d->tabWidget);
    Q_UNUSED(runner);
}

void FileManager::setTabWidget( KTabWidget* widget )
{
    d->tabWidget = widget;
    connect(d->tabWidget, SIGNAL(closeRequest(QWidget*)), SLOT(closeTab(QWidget*)));
}

void FileManager::closeTab( QWidget* widget )
{
    if(widget->objectName() == "gluon_viewer_part" || widget->objectName() == "gluon_editor_part")
        return;
    
    widget->deleteLater();
}

FileManager::FileManager()
    : d(new FileManagerPrivate)
{

}

FileManager::~FileManager()
{
    delete d;
}

void FileManager::addTab( QWidget* widget, const QString& name )
{
    if(widget)
    {
        QWidget *base = new QWidget();
        base->setObjectName(name);
        QVBoxLayout *layout = new QVBoxLayout();
        base->setLayout(layout);

        layout->addWidget(new KToolBar(base));
        layout->addWidget(widget);
        
        int id = d->tabWidget->addTab(base, name);
        d->tabWidget->setCurrentIndex(id);
    }
}


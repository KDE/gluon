/*****************************************************************************
* This file is part of the Gluon Development Platform
* Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
* Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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

#ifndef GLUON_CREATOR_FILEMANAGER_H
#define GLUON_CREATOR_FILEMANAGER_H

#include "gluoncreator_macros.h"
#include <KDE/KParts/ReadWritePart>
#include <core/singleton.h>

class KToolBar;

namespace KParts
{
    class PartManager;
}

namespace GluonEngine
{
    class Asset;
}

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT FileManager : public GluonCore::Singleton<FileManager>
    {
            Q_OBJECT
            GLUON_SINGLETON( FileManager )
        public:
            KParts::PartManager* partManager() const;
            KParts::Part* part( const QString& partName ) const;

        public Q_SLOTS:
            void initialize( QWidget* widget );
            void openAsset( GluonEngine::Asset* asset );
            /**
             * Open a file in the associated editor.
             *
             * \param fileName The name of the file to open.
             * \param name The name to use to identify the opened file.
             * fileName will be used if this is an empty string.
             * \param title The title of the tab created when embedding.
             * Name will be used if this is an empty string.
             * \param icon The icon to use for the file. Will be ignored when empty.
             * \param partName The name of the KPart to use. If empty,
             * an appropriate editor will be searched for.
             * \param partParams Parameters to pass on to the KPart when
             * loading.
             * \param closeable Determines whether the file can be closed.
             */
            void openFile( const QString& fileName, const QString& name = QString(), const QString& title = QString(), const QString& icon = QString(), const QString& partName = QString(), const QVariantList& partParams = QVariantList(), bool closeable = true );

            /**
             * Close a file and associated editor.
             *
             * \param file The name of the file to close.
             * \param force If true, ignore whether or not the file has
             * been marked as non-closable and close it anyway.
             */
            void closeFile( const QString& file, bool force = false );

            void setCurrentFile( const QString& file );

            /**
             * Close all open files.
             *
             * \param force Close all files, including those marked as non-closeable.
             */
            void closeAll( bool force = false );
	    void SaveAll();
	    void UndoOnEditor();
	    void RedoOnEditor();
	    
        Q_SIGNALS:
            void newPart( const QString& name, const QString& title, const QString& icon );
            void fileClosed( const QString& file );

        private:
            ~FileManager();

	    class Private;
	    QList<KParts::ReadWritePart> rwList;
	    Private* const d;
    };
}

#endif // GLUON_CREATOR_FILEMANAGER_H

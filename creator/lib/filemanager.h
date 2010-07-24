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

#ifndef GLUONCREATOR_FILEMANAGER_H
#define GLUONCREATOR_FILEMANAGER_H

#include <core/singleton.h>
#include "gluoncreator_macros.h"

namespace GluonEngine
{
    class Asset;
}

class KTabWidget;

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT FileManager : public GluonCore::Singleton<FileManager>
    {
        Q_OBJECT
        public:
            KTabWidget * tabWidget();

        public Q_SLOTS:
            void openAsset( GluonEngine::Asset* asset );

            void setTabWidget(KTabWidget *widget);

        private Q_SLOTS:
            void closeTab( QWidget* widget );

        private:
            friend class Singleton<FileManager>;
            
            FileManager();
            ~FileManager();
            Q_DISABLE_COPY(FileManager)

            void addTab( QWidget* widget, const QString& name );

            class FileManagerPrivate;
            FileManagerPrivate * const d;
    };
}

#endif // GLUONCREATOR_FILEMANAGER_H

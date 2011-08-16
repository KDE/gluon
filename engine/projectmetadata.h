/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#ifndef GLUON_ENGINE_PROJECTMETADATA
#define GLUON_ENGINE_PROJECTMETADATA

#include "gluon_engine_export.h"

#include <core/gluonobject.h>

namespace GluonEngine
{
    /**
     * ProjectMetaData saves the meta data of a project in a separate
     * file, so that you don't have to open the full project to get e.g. its
     * name.
     */
    class GLUON_ENGINE_EXPORT ProjectMetaData : public GluonCore::GluonObject
    {
            Q_OBJECT

            /** Project name */
            Q_PROPERTY( QString projectName READ projectName WRITE setProjectName )

            /** Project description */
            Q_PROPERTY( QString projectDescription READ projectDescription WRITE setProjectDescription )

            /** Path to the project */
            Q_PROPERTY( QString projectPath READ projectPath WRITE setProjectPath )

            /** ID of the project on the gaming server */
            Q_PROPERTY( QString projectId READ projectId WRITE setProjectId )

            GLUON_OBJECT( GluonEngine::ProjectMetaData )

        public:
            Q_INVOKABLE ProjectMetaData( QObject* parent = 0 );
            ProjectMetaData( QString projectPath, QString projectName, QString description, QString id, QObject* parent = 0 );
            virtual ~ProjectMetaData();

            QString projectName() const;
            void setProjectName( const QString& name );

            QString projectDescription() const;
            void setProjectDescription( const QString& description );

            QString projectPath() const;
            void setProjectPath( const QString& projectPath );

            QString projectId() const;
            void setProjectId( const QString& id );

            /** The directory the project file is in */
            QString projectDir() const;

            /** Save in the project given by projectPath */
            void save();

            /** Load from the project given by projectPath */
            void load();

        private:
            class ProjectMetaDataPrivate;
            ProjectMetaDataPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::ProjectMetaData* )

#endif // GLUON_ENGINE_PROJECTMETADATA

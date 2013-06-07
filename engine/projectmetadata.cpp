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

#include "projectmetadata.h"

#include <core/gdlserializer.h>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, ProjectMetaData )

class ProjectMetaData::ProjectMetaDataPrivate
{
    public:
        ProjectMetaDataPrivate() {}
        ~ProjectMetaDataPrivate() {}

        QString projectName;
        QString projectDescription;
        QString projectFilePath;
        QString projectId;
};

ProjectMetaData::ProjectMetaData(QObject* parent)
    : GluonObject(parent)
    , d( new ProjectMetaDataPrivate )
{
}

ProjectMetaData::ProjectMetaData( QString projectFilePath, QString projectName, QString projectDescription, QString projectId, QObject* parent )
    : GluonObject( parent )
    , d( new ProjectMetaDataPrivate )
{
    d->projectName = projectName;
    d->projectDescription = projectDescription;
    d->projectFilePath = projectFilePath;
    d->projectId = projectId;
}

ProjectMetaData::~ProjectMetaData()
{
    delete d;
}

QString ProjectMetaData::projectName() const
{
    return d->projectName;
}

void ProjectMetaData::setProjectName(const QString& name)
{
    d->projectName = name;
}

QString ProjectMetaData::projectDescription() const
{
    return d->projectDescription;
}

void ProjectMetaData::setProjectDescription(const QString& description)
{
    d->projectDescription = description;
}

QString ProjectMetaData::projectFilePath() const
{
    return d->projectFilePath;
}

void ProjectMetaData::setProjectFilePath(const QString& path)
{
    d->projectFilePath = path;
}

QString ProjectMetaData::projectId() const
{
    return d->projectId;
}

void ProjectMetaData::setProjectId(const QString& id)
{
    d->projectId = id;
}

QString ProjectMetaData::projectDir() const
{
    return projectFilePath().section( '/', 0, -2 );
}

void ProjectMetaData::save()
{
    if( d->projectFilePath.isEmpty() )
        return;

    if( !GluonCore::GDLSerializer::instance()->write( projectDir() + "/game.gluonmeta", GluonCore::GluonObjectList() << this ) )
        return;
}

void ProjectMetaData::load()
{
    if( d->projectFilePath.isEmpty() )
        return;

    GluonCore::GluonObjectList gdlList;
    if( !GluonCore::GDLSerializer::instance()->read( QUrl::fromLocalFile( projectDir() + "/game.gluonmeta" ), gdlList ) )
        return;

    ProjectMetaData* object = qobject_cast<ProjectMetaData*>( gdlList[0] );
    if( object )
    {
        setProjectName( object->projectName() );
        setProjectDescription( object->projectDescription() );
        setProjectId( object->projectId() );
    }

    qDeleteAll( gdlList );
}

 

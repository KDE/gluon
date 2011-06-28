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

#include <core/gdlhandler.h>

#include <QtCore/QFile>
#include <QtCore/QTextStream>

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, ProjectMetaData )

class ProjectMetaData::ProjectMetaDataPrivate
{
    public:
        ProjectMetaDataPrivate() {}
        ~ProjectMetaDataPrivate() {}

        QString projectName;
        QString description;
        QString projectPath;
        QString id;
};

ProjectMetaData::ProjectMetaData(QObject* parent)
    : GluonObject(parent)
    , d( new ProjectMetaDataPrivate() )
{
}

ProjectMetaData::ProjectMetaData( QString projectPath, QString projectName, QString description, QString id, QObject* parent )
    : GluonObject( parent )
    , d( new ProjectMetaDataPrivate() )
{
    d->projectName = projectName;
    d->description = description;
    d->projectPath = projectPath;
    d->id = id;
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

QString ProjectMetaData::description() const
{
    return d->description;
}

void ProjectMetaData::setDescription(const QString& description)
{
    d->description = description;
}

QString ProjectMetaData::projectPath() const
{
    return d->projectPath;
}

void ProjectMetaData::setProjectPath(const QString& projectPath)
{
    d->projectPath = projectPath;
}

QString ProjectMetaData::id() const
{
    return d->id;
}

void ProjectMetaData::setId(const QString& id)
{
    d->id = id;
}

QString ProjectMetaData::projectDir() const
{
    return projectPath().section( '/', 0, -2 );
}

void ProjectMetaData::save()
{
    if( d->projectPath.isEmpty() )
        return;

    QString gdlString = GluonCore::GDLHandler::instance()->toGDL( qobject_cast<GluonCore::GluonObject*>( this ) );
    QString saveDirectory = projectDir() + "/game.gluonmeta";
    QFile file( saveDirectory );
    if( !file.open(QIODevice::WriteOnly) )
        return;

    QTextStream stream( &file );
    stream << gdlString;
    file.close();
}

void ProjectMetaData::load()
{
    if( d->projectPath.isEmpty() )
        return;

    QString saveDirectory = projectDir() + "/game.gluonmeta";
    QList<GluonCore::GluonObject*> gdlList = GluonCore::GDLHandler::instance()->parseGDL(saveDirectory);
    if( gdlList.isEmpty() )
        return;

    ProjectMetaData* object = qobject_cast<ProjectMetaData*>(gdlList[0]);
    if( object )
    {
        setProjectName( object->projectName() );
        setDescription( object->description() );
        setId( object->id() );
    }

    qDeleteAll( gdlList );
}

#include "projectmetadata.moc"

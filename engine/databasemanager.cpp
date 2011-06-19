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

#include "databasemanager.h"

#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <QtGui/QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

using namespace GluonEngine;

GLUON_DEFINE_SINGLETON( GluonEngine::DatabaseManager )

class DatabaseManager::DatabaseManagerPrivate
{
    public:
        DatabaseManagerPrivate() {}
        ~DatabaseManagerPrivate() {}

        QStringList connections;

};

DatabaseManager::DatabaseManager()
    : d( new DatabaseManagerPrivate() )
{
    // TODO: do this in GluonCore::Singleton
    setParent( qApp );
}

DatabaseManager::~DatabaseManager()
{
    foreach( const QString& connection, d->connections )
    {
        QSqlDatabase db = QSqlDatabase::database(connection);
        db.close();
        QSqlDatabase::removeDatabase(connection);
    }
    delete d;
}

QString DatabaseManager::openStatisticDatabase(const QString& configPath, const QString& userName, const QString& gameName)
{
    QChar sep = QDir::separator();
    QString absolutePath = QString("%1%4%2%4%3%4statistics.db").arg(configPath).arg(userName).arg(gameName).arg(sep);

    // already open?
    if( d->connections.contains(absolutePath) )
    {
        if( QSqlDatabase::database(absolutePath).isOpen() )
            return absolutePath;
        else
            return QString();
    }

    d->connections.append(absolutePath);

    // does the file exist?
    QFileInfo info(absolutePath);
    bool databaseExists = info.exists();
    if( !databaseExists )
    {
        if( !info.dir().mkpath(info.absolutePath()) )
        {
            qDebug() << "Can't create database path " << info.absolutePath();
            return QString();
        }
    }
    qDebug() << "Database: Created path " << info.absolutePath();

    // open Database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", absolutePath);
    db.setHostName("localhost");
    db.setDatabaseName(absolutePath);
    if( !db.open() )
    {
        qDebug() << "Failed to open database " << absolutePath;
        return QString();
    }
    if( !databaseExists )
    {
        QSqlQuery query = db.exec("CREATE TABLE statistics ("
                                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                    "name TEXT, score NUMERIC, array TEXT );");
        if( !query.isActive() )
        {
            qDebug() << "Could not create table: " << query.lastError().text();
            return QString();
        }
    }
    return absolutePath;
}

int DatabaseManager::statisticEntry( const QString& databaseName, const QString& name )
{
    int id = -1;
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery readQuery = db.exec( QString("SELECT id FROM statistics WHERE name = '%1'").arg(name) );
    if( readQuery.next() )
    {
         id = readQuery.value(0).toInt();
    }
    else
    {
        QSqlQuery writeQuery = db.exec( QString("INSERT INTO statistics (name, score, array)"
                                            "VALUES ('%1', 0, '');").arg(name) );
        if( writeQuery.isActive() )
        {
            qDebug() << "Added statistics entry " << name;
            return statisticEntry(databaseName, name);
        }
        else
        {
            qDebug() << "Could not create entry: " << writeQuery.lastError().text();
        }
    }
    return id;
}

qlonglong DatabaseManager::statisticScore( const QString& database, int id ) const
{
    QSqlDatabase db = QSqlDatabase::database(database);
    QSqlQuery query = db.exec( QString("SELECT score FROM statistics WHERE id = %1").arg(id) );
    if( query.next() )
        return query.value(0).toLongLong();
    qDebug() << "Could not read score data (database: " << database << " )";
    return 0;
}

QList< qlonglong > DatabaseManager::statisticArray( const QString& database, int id ) const
{
    QSqlDatabase db = QSqlDatabase::database(database);
    QSqlQuery query = db.exec( QString("SELECT array FROM statistics WHERE id = %1").arg(id) );
    QList<qlonglong> list;
    if( query.next() )
    {
        QString arrayAsString = query.value(0).toString();
        QStringList arrayAsStringList = arrayAsString.split(',');
        bool ok;
        foreach( const QString& val, arrayAsStringList )
        {
            qlonglong i = val.toLongLong(&ok);
            if( ok )
                list.append(i);
        }
    }
    return list;
}

void DatabaseManager::setStatisticName( const QString& database, int id, const QString& name )
{
    QSqlDatabase db = QSqlDatabase::database(database);
    QSqlQuery query = db.exec( QString("UPDATE statistics SET name = '%1' WHERE id = %2")
                                .arg(name).arg(id) );
    if( !query.isActive() )
        qDebug() << "Could not update name: " << query.lastError().text();
}

void DatabaseManager::setStatisticScore( const QString& database, int id, qlonglong score )
{
    QSqlDatabase db = QSqlDatabase::database(database);
    QSqlQuery query = db.exec( QString("UPDATE statistics SET score = %1 WHERE id = %2")
                                .arg(score).arg(id) );
    if( !query.isActive() )
        qDebug() << "Could not update score: " << query.lastError().text();
}

void DatabaseManager::setStatisticArray( const QString& database, int id, const QList<qlonglong>& array )
{
    QStringList list;
    foreach( qlonglong num, array )
    {
        list.append( QString::number(num) );
    }
    QString val = list.join(",");
    QSqlDatabase db = QSqlDatabase::database(database);
    QSqlQuery query = db.exec( QString("UPDATE statistics SET array = '%1' WHERE id = %2")
                                .arg(val).arg(id) );
    if( !query.isActive() )
        qDebug() << "Could not update array: " << query.lastError().text();
}

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

#ifndef GLUON_ENGINE_DATABASEMANAGER_H
#define GLUON_ENGINE_DATABASEMANAGER_H

#include <core/singleton.h>

namespace GluonEngine
{
    class DatabaseManagerPrivate;

    /**
     * The statistic objects use this class to access their databases.
     * @Note: Don't access this class from different threads!
     */
    class DatabaseManager : public GluonCore::Singleton<DatabaseManager>
    {
        Q_OBJECT
        GLUON_SINGLETON( DatabaseManager )
        public:
            /**
             * Try to open the statistics database for the given user name and game name.
             * @return the database name or an empty string if opening failed
             */
            QString openStatisticDatabase( const QString& configPath, const QString& userName, const QString& gameName );

            /**
             * Get the id for a statistics entry. If it doesn't exist, it will
             * be created.
             * @param database the string you got by calling openStatisticDatabase
             * @param name the name of your statistic
             * @return the id or -1 if it couldn't find or create the entry
             */
            int statisticEntry( const QString& databaseName, const QString& name );

            qlonglong statisticScore(const QString& database, int id) const;
            QList<qlonglong> statisticArray( const QString& database, int id) const;

            /** Set the name of the statistic */
            void setStatisticName( const QString& database, int id, const QString& name );
            void setStatisticScore( const QString& database, int id, qlonglong score );
            void setStatisticArray( const QString& database, int id, const QList<qlonglong>& array );

        private:
            ~DatabaseManager();

            class DatabaseManagerPrivate;
            DatabaseManagerPrivate* d;
    };
}

#endif //GLUON_ENGINE_DATABASEMANAGER_H

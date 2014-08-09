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

#ifndef GLUON_ENGINE_STATISTICSASSET_H
#define GLUON_ENGINE_STATISTICSASSET_H

#include <core/metainfo.h>
#include <engine/asset.h>
#include <engine/savable.h>

namespace GluonEngine
{
    /**
     * StatisticsAsset handles a file which contains
     * several statistics. The file is written in GDL.
     */
    class StatisticsAsset : public Asset, public Savable
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset )
            GLUON_OBJECT( GluonEngine::StatisticsAsset )
            GLUON_ASSET_PLUGIN(metadata.json)

        public:
            Q_INVOKABLE StatisticsAsset( QObject* parent = 0 );
            virtual ~StatisticsAsset();

            /**
             * Reimplemented from Savable::writeContents()
             */
            virtual void writeContents( QIODevice* device );

            /** Reimplemented from Asset::load() */
            virtual void load();

            /** Reimplemented from Asset::unload() */
            virtual void unload();

            /** Creates the statistics from the file at startup */
            virtual void setFile( const QString& newFile );

            virtual bool shouldSerializeChildren() const;

        public Q_SLOTS:
            /**
             * Use this method to create Statistic objects. If you use the normal
             * constructor, it won't be saved.
             */
            void createStatistic();

            /**
             * Use this method to create TasksStatistic objects. If you use the normal
             * constructor, it won't be saved.
             */
            void createTasksStatistic();

            /**
             * Use this method to create MultiScoreStatistic objects. If you use the
             * normal constructor, it won't be saved.
             */
            void createMultiScoreStatistic();

            /**
             * Use this method to create BooleanStatistic objects. If you use the normal
             * constructor, it won't be saved.
             */
            void createBooleanStatistic();

        protected:
            /** Reimplemented from GluonCore::GluonObject::populateMetaInfo() */
            virtual void populateMetaInfo( GluonCore::MetaInfo* info );

        private:
            class StatisticsAssetPrivate;
            StatisticsAssetPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::StatisticsAsset* )

#endif //STATISTICSASSET_H

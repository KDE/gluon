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

#ifndef STATISTICSASSET_H
#define STATISTICSASSET_H

#include <engine/asset.h>
#include <engine/savable.h>
#include <core/metainfo.h>

namespace GluonEngine
{
    class Statistic;

    /**
     * StatisticsAsset handles a file which contains
     * several statistics. The file is written in GDL.
     */
    class GLUON_ASSET_STATISTICS_EXPORT StatisticsAsset : public Asset, public Savable
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::StatisticsAsset )
            Q_INTERFACES( GluonEngine::Asset )
        public:
            Q_INVOKABLE StatisticsAsset( QObject* parent = 0 );
            virtual ~StatisticsAsset();

            virtual const QStringList supportedMimeTypes() const;

            /** Reimplemented from Savable::contentsToGDL() */
            virtual QString contentsToGDL();

            /** Reimplemented from Asset::templates() */
            virtual const QList<AssetTemplate*> templates();

            /** Reimplemented from Asset::actions() */
            virtual QList<QAction*> actions();

            /** Creates the statistics from the file at startup */
            virtual void setFile( const QUrl& newFile );

        public Q_SLOTS:
            /**
             * Use this method to create Statistic objects. If you use the normal
             * constructor, it won't be saved.
             */
            void createStatistic();

        protected:
            /** Reimplemented from GluonCore::GluonObject::populateMetaInfo() */
            virtual void populateMetaInfo( GluonCore::MetaInfo*  info );

        private:
            class StatisticsAssetPrivate;
            StatisticsAssetPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::StatisticsAsset* )

#endif //STATISTICSASSET_H

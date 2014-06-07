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

#ifndef GLUON_ENGINE_ACHIEVEMENTSASSET_H
#define GLUON_ENGINE_ACHIEVEMENTSASSET_H

#include <core/metainfo.h>
#include <engine/asset.h>
#include <engine/savable.h>

namespace GluonEngine
{
    /**
     * AchievementsAsset handles a file which contains
     * several achievements. The file is written in GDL.
     */
    // TODO: Arjen Hiemstra says that the export macro should not be needed here, but Windows meeds it.
    class AchievementsAsset : public Asset, public Savable
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset )
            GLUON_OBJECT( GluonEngine::AchievementsAsset )
            GLUON_ASSET_PLUGIN( metadata.json )

        public:
            Q_INVOKABLE AchievementsAsset( QObject* parent = 0 );
            virtual ~AchievementsAsset();

            /**
             * Reimplemented from Savable::writeContents()
             */
            virtual void writeContents( QIODevice* device );

            /** Reimplemented from Asset::load() */
            virtual void load();

            /** Reimplemented from Asset::unload() */
            virtual void unload();

            /** Creates the achievements from the file at startup */
            virtual void setFile( const QString& newFile );

        public Q_SLOTS:
            /**
             * Use this method to create Achievement objects. If you use the normal
             * constructor, it won't be saved.
             */
            void createAchievement();

        protected:
            /** Reimplemented from GluonCore::GluonObject::populateMetaInfo() */
            virtual void populateMetaInfo( GluonCore::MetaInfo* info );

        private:
            class AchievementsAssetPrivate;
            AchievementsAssetPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::AchievementsAsset* )

#endif // GLUON_ENGINE_ACHIEVEMENTSASSET_H

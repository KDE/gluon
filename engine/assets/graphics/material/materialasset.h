/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUON_ENGINE_MATERIALASSET_H
#define GLUON_ENGINE_MATERIALASSET_H

#include <engine/gluon_engine_export.h>
#include <engine/asset.h>

namespace GluonGraphics
{
    class MaterialInstance;
};

namespace GluonEngine
{
    class MaterialAsset : public Asset
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset )
            GLUON_OBJECT( GluonEngine::MaterialAsset )

            Q_CLASSINFO( "org.gluon.category", "Graphics Rendering" )
            Q_CLASSINFO( "org.gluon.icon", "text-mathml" )

        public:
            Q_INVOKABLE MaterialAsset( QObject* parent = 0 );
            virtual ~MaterialAsset();

            virtual void load();

            virtual const QStringList supportedMimeTypes() const;
            virtual const QList<AssetTemplate*> templates();
            virtual QList<QAction*> actions();

            virtual void setName( const QString& newName );
            virtual void sanitize();
            virtual bool shouldSerializeChildren() const;

        public Q_SLOTS:
            void createInstance();

        Q_SIGNALS:
            void instanceCreated( GluonGraphics::MaterialInstance* );

        private:
            class Private;
            Private* const d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::MaterialAsset* )

#endif // GLUON_ENGINE_MATERIALASSET_H

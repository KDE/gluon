/******************************************************************************
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

#ifndef GLUON_ENGINE_TEXTUREASSET_H
#define GLUON_ENGINE_TEXTUREASSET_H

#include "engine/gluon_engine_export.h"
#include "engine/asset.h"

#include <graphics/texture.h>

namespace GluonEngine
{
    class GLUON_ASSET_TEXTURE_EXPORT TextureAsset : public Asset
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset )
            GLUON_OBJECT( GluonEngine::TextureAsset )
            Q_PROPERTY( GluonGraphics::Texture* texture READ texture );

        public:
            Q_INVOKABLE TextureAsset( QObject* parent = 0 );
            ~TextureAsset();


            virtual QIcon icon() const;

            void load();

            virtual const QStringList supportedMimeTypes() const;

            virtual void setName( const QString& newName );

            virtual GluonGraphics::Texture* texture() const;
        private:
            class TextureAssetPrivate;
            TextureAssetPrivate* d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::TextureAsset* )

#endif // GLUON_ENGINE_TEXTUREASSET_H

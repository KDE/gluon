/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include <engine/asset.h>
#include <graphics/qtquickrenderer.h>

namespace GluonEngine
{
    class QtQuickAsset : public Asset
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset )
            GLUON_OBJECT( GluonEngine::QtQuickAsset )

            Q_PROPERTY( GluonGraphics::Texture* texture READ texture );
            Q_PROPERTY( GluonGraphics::QtQuickRenderer* renderer READ renderer );

            Q_CLASSINFO( "org.gluon.category", "Graphics Rendering" )
            Q_CLASSINFO( "org.gluon.icon", "text-x-qml" )

        public:
            Q_INVOKABLE QtQuickAsset( QObject* parent = 0 );
            virtual ~QtQuickAsset();

            virtual void load();
            virtual void unload();
            virtual void reload();

            const QStringList supportedMimeTypes() const;

            void setName( const QString& newName );

            GluonGraphics::Texture* texture() const;
            GluonGraphics::QtQuickRenderer* renderer() const;

        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::QtQuickAsset* )

#endif // GLUON_ENGINE_TEXTUREASSET_H

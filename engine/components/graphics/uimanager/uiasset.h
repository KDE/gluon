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

#ifndef GLUON_ENGINE_UIASSET_H
#define GLUON_ENGINE_UIASSET_H

#include <gluon_engine_export.h>
#include <asset.h>

class QGraphicsWidget;
class QDeclarativeEngine;

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT UiAsset : public Asset
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset )
            GLUON_OBJECT( GluonEngine::UiAsset )

        public:
            Q_INVOKABLE UiAsset( QObject* parent = 0 );
            ~UiAsset();


            virtual QIcon icon() const;

            void load();

            virtual const QStringList supportedMimeTypes() const;

            virtual void setName( const QString& newName );

            QDeclarativeEngine *engine() const;
            QGraphicsWidget *widget() const;

        private:
            class UiAssetPrivate;
            UiAssetPrivate* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::UiAsset )
Q_DECLARE_METATYPE( GluonEngine::UiAsset* )

#endif // GLUON_ENGINE_TEXTUREASSET_H

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUONENGINE_SCRIPTINGASSET_H
#define GLUONENGINE_SCRIPTINGASSET_H

#include <engine/gluon_engine_export.h>
#include <engine/asset.h>

namespace GluonEngine
{
    class ScriptingAsset : public Asset
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset )
            GLUON_OBJECT( GluonEngine::ScriptingAsset )

            Q_CLASSINFO( "org.gluon.category", "Game Logic" )
            Q_CLASSINFO( "org.gluon.icon", "application-javascript" )

        public:
            Q_INVOKABLE ScriptingAsset( QObject* parent = 0 );
            virtual ~ScriptingAsset();

            virtual const QStringList supportedMimeTypes() const;
            virtual const QList<AssetTemplate*> templates();
            virtual void load();
            virtual void unload();

            virtual QString className() const;
        private:
            class Private;
            Private* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::ScriptingAsset* )

#endif // GLUONENGINE_SCRIPTINGASSET_H

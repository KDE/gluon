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

#ifndef GLUONENGINE_SCRIPTASSET_H
#define GLUONENGINE_SCRIPTASSET_H

#include <engine/gluon_engine_export.h>
#include <engine/asset.h>

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT ScriptAsset : public GluonEngine::Asset
    {
            Q_OBJECT
            Q_INTERFACES(GluonEngine::Asset)
            GLUON_OBJECT(GluonEngine::ScriptAsset)

        public:
            ScriptAsset(QObject* parent = 0);
            ~ScriptAsset();

            virtual const QStringList supportedMimeTypes() const;
            virtual void load();
            virtual const QList<AssetTemplate*> templates();

        private:
            class ScriptAssetPrivate;
            ScriptAssetPrivate* d;
    };

}

Q_DECLARE_METATYPE(GluonEngine::ScriptAsset)
Q_DECLARE_METATYPE(GluonEngine::ScriptAsset*)

#endif // GLUONENGINE_SCRIPTASSET_H

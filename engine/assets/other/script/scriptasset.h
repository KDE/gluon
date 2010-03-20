/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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

        private:
            class ScriptAssetPrivate;
            ScriptAssetPrivate* d;
    };

}

#endif // GLUONENGINE_SCRIPTASSET_H

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

#ifndef BEHAVIORTREE_BTASSET_H
#define BEHAVIORTREE_BTASSET_H

#include "engine/asset.h"
#include "engine/gluon_engine_export.h"
#include "smarts/lib/btnode.h"
#include "smarts/lib/btbrain.h"

namespace GluonEngine
{
    class btAssetPrivate;
    
    class BTCOMPONENT_EXPORT btAsset : public GluonEngine::Asset
    {
        Q_OBJECT
        GLUON_OBJECT(GluonEngine::btAsset)
        Q_INTERFACES(GluonEngine::Asset)
        
        public:
            btAsset(QObject *parent = 0);
            btAsset(const btAsset& other, QObject* parent = 0);
            ~btAsset();
            
            virtual void setFile(const QUrl &newFile);
	    virtual const QStringList supportedMimeTypes() const;
            
        private:
            btAssetPrivate* d;
    };
}

Q_DECLARE_METATYPE(GluonEngine::btAsset)
Q_DECLARE_METATYPE(GluonEngine::btAsset*)

#endif // BEHAVIORTREE_BTASSET_H

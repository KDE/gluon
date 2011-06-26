/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef BEHAVIORTREE_ASSET_H
#define BEHAVIORTREE_ASSET_H

#include <engine/asset.h>
#include "bt_export.h"
#include <smarts/lib/btnode.h>
#include <smarts/lib/btbrain.h>

namespace BehaviorTree
{
    class AssetPrivate;
    
    class BTCOMPONENT_EXPORT Asset : public GluonEngine::Asset
    {
        Q_OBJECT
        GLUON_OBJECT(BehaviorTree::Asset)
        Q_INTERFACES(GluonEngine::Asset)
        
        public:
            Asset(QObject *parent = 0);
            Asset(const Asset& other, QObject* parent = 0);
            ~Asset();
            
            virtual void setFile(const QUrl &newFile);
	    virtual const QStringList supportedMimeTypes() const;
            
        private:
            AssetPrivate* d;
    };
}

Q_DECLARE_METATYPE(BehaviorTree::Asset)
Q_DECLARE_METATYPE(BehaviorTree::Asset*)

#endif // BEHAVIORTREE_ASSET_H

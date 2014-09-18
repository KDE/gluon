/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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
 *
 */

#include "factoryplugin.h"

#include "achievement.h"
#include "asset.h"
#include "booleanstatistic.h"
#include "gameproject.h"
#include "multiscorestatistic.h"
#include "prefab.h"
#include "prefabinstance.h"
#include "projectmetadata.h"
#include "prefabinstancechild.h"
#include "tasksstatistic.h"

using namespace GluonEngine;

GluonCore::GluonObjectList FactoryPlugin::typesToRegister()
{
    return GluonCore::GluonObjectList()
        << new Achievement( this )
        << new Asset( this )
        << new BooleanStatistic( this )
        << new GameObject( this )
        << new GameProject( this )
        << new MultiScoreStatistic( this )
        << new Prefab( this )
        << new PrefabInstance( this )
        << new PrefabInstanceChild( this )
        << new ProjectMetaData( this )
        << new Scene( this )
        << new Statistic( this )
        << new TasksStatistic( this );
}

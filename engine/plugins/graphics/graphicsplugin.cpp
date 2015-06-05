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

#include "graphicsplugin.h"

#include "materialasset.h"
#include "textureasset.h"
#include "qtquickasset.h"
#include "cameracontrollercomponent.h"
#include "spriterenderercomponent.h"
#include "interfacerenderercomponent.h"

using namespace GluonEngine;

GluonCore::GluonObjectList GraphicsPlugin::typesToRegister()
{
    return GluonCore::GluonObjectList()
        << new MaterialAsset( this )
        << new TextureAsset( this )
        << new QtQuickAsset( this )
        << new CameraControllerComponent( this )
        << new SpriteRendererComponent( this )
        << new GluonEngine::InterfaceRendererComponent( this );

}

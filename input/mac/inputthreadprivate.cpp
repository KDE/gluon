/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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
#include "inputthreadprivate.h"

using namespace GluonInput;

InputThreadPrivate::InputThreadPrivate()
{
}

InputThreadPrivate::InputThreadPrivate(InputThreadPrivate &other)
        : QSharedData(other),
        vendor(other.vendor),
        product(other.product),
        version(other.version),
        bustype(other.bustype),
        deviceName(other.deviceName),
        msgError(other.msgError),
        error(other.error),
        deviceType(other.deviceType),
        buttonCapabilities(other.buttonCapabilities),
//        relAxisCapabilities(other.relAxisCapabilities),
        axisCapabilities(other.axisCapabilities),
        axisInfos(other.axisInfos),
        device(other.device)
{
}

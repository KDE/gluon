/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
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
    m_error = false;
}

InputThreadPrivate::InputThreadPrivate(InputThreadPrivate &other)
        : QSharedData(other),
        m_fd(other.m_fd),
        m_device_info(other.m_device_info),
        m_currentEvent(other.m_currentEvent),
        m_devicePath(other.m_devicePath),
        m_vendor(other.m_vendor),
        m_product(other.m_product),
        m_version(other.m_version),
        m_bustype(other.m_bustype),
        m_deviceName(other.m_deviceName),
        m_msgError(other.m_msgError),
        m_error(other.m_error),
        m_deviceType(other.m_deviceType),
        m_buttonCapabilities(other.m_buttonCapabilities),
        m_relAxisCapabilities(other.m_relAxisCapabilities),
        m_absAxisCapabilities(other.m_absAxisCapabilities),
        m_absAxisInfos(other.m_absAxisInfos)
{
}

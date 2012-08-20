/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Laszlo Papp <lpapp@kde.org>
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

#include "touchinputcomponent.h"

#include <input/inputmanager.h>
#include <input/touch.h>
#include <core/debughelper.h>

REGISTER_OBJECTTYPE( GluonEngine, TouchInputComponent );

using namespace GluonEngine;

TouchInputComponent::TouchInputComponent( QObject* parent )
    : Component( parent )
    , m_actionHeld( false )
    , m_actionStarted( false )
    , m_actionStopped( false )
    , m_touch( 0 )
{
}

TouchInputComponent::~TouchInputComponent()
{
}

QString TouchInputComponent::category() const
{
    return QString( "Input" );
}

void TouchInputComponent::initialize()
{
    if( !m_touch )
        m_touch = GluonInput::InputManager::instance()->touch();
}

void TouchInputComponent::start()
{
    if( m_touch )
    {
        m_touch->setEnabled( true );
    }
    else
    {
        debug( "WARNING! No touch found!" );
    }
}

void TouchInputComponent::update( int elapsedMilliseconds )
{
    DEBUG_BLOCK
    if( m_actionStarted )
        m_actionStarted = false;

    if( m_actionStopped )
        m_actionStopped = false;

    if( m_touch && m_touch->buttonPressed( m_touchCode ) )
    {
        if( !m_actionHeld )
        {
            m_actionStarted = true;
            m_actionHeld = true;
        }
    }
    else
    {
        if( m_actionHeld )
        {
            m_actionStopped = true;
            m_actionHeld = false;
        }
    }
}

void TouchInputComponent::stop()
{
    if( m_touch )
    {
        m_touch->setEnabled( false );
    }

    m_actionStopped = false;
    m_actionStarted = false;
    m_actionHeld = false;
}

bool TouchInputComponent::isActionStarted()
{
    return m_actionStarted;
}

bool TouchInputComponent::isActionHeld()
{
    return m_actionHeld;
}

bool TouchInputComponent::isActionStopped()
{
    return m_actionStopped;
}

TouchInputComponent::TouchName
TouchInputComponent::touchCode() const
{
    return m_touchCode;
}

void TouchInputComponent::setTouchCode( TouchInputComponent::TouchName newTouchCode )
{
    m_touchCode = newTouchCode;
}

Q_EXPORT_PLUGIN2( gluon_component_touchinput, GluonEngine::TouchInputComponent );

#include "touchinputcomponent.moc"

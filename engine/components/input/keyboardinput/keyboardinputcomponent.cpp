/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "keyboardinputcomponent.h"

#include <input/inputmanager.h>
#include <input/keyboard.h>
#include <core/debughelper.h>

REGISTER_OBJECTTYPE( GluonEngine, KeyboardInputComponent );

using namespace GluonEngine;

KeyboardInputComponent::KeyboardInputComponent( QObject* parent )
    : Component( parent )
    , m_actionHeld( false )
    , m_actionStarted( false )
    , m_actionStopped( false )
    , m_keyCode( Qt::Key_unknown )
    , m_keyboard( 0 )
{
}

KeyboardInputComponent::~KeyboardInputComponent()
{
}

QString
KeyboardInputComponent::category() const
{
    return QString( "Input" );
}

void KeyboardInputComponent::initialize()
{
    if( !m_keyboard )
        m_keyboard = GluonInput::InputManager::instance()->keyboard();
}

void
KeyboardInputComponent::start()
{
    if( m_keyboard )
    {
        m_keyboard->setEnabled( true );
    }
    else
    {
        debug( "WARNING! No keyboard found!" );
    }
}

void
KeyboardInputComponent::update( int elapsedMilliseconds )
{
    DEBUG_BLOCK
    if( m_actionStarted )
        m_actionStarted = false;

    if( m_actionStopped )
        m_actionStopped = false;

    if( m_keyboard && m_keyboard->buttonPressed( m_keyCode ) )
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

void KeyboardInputComponent::stop()
{
    if( m_keyboard )
    {
        m_keyboard->setEnabled( false );
    }

    m_actionStopped = false;
    m_actionStarted = false;
    m_actionHeld = false;
}

bool
KeyboardInputComponent::isActionStarted()
{
    return m_actionStarted;
}

bool
KeyboardInputComponent::isActionHeld()
{
    return m_actionHeld;
}

bool
KeyboardInputComponent::isActionStopped()
{
    return m_actionStopped;
}

Qt::Key
KeyboardInputComponent::keyCode() const
{
    return m_keyCode;
}

void
KeyboardInputComponent::setKeyCode( Qt::Key newKeyCode )
{
    m_keyCode = newKeyCode;
}

Q_EXPORT_PLUGIN2( gluon_component_keyboardinput, GluonEngine::KeyboardInputComponent );

#include "keyboardinputcomponent.moc"

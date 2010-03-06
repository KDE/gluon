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

#include "keyboardinputcomponent.h"
#include "input/inputdetection.h"

#include <QtCore/QEvent>

#include <core/debughelper.h>

REGISTER_OBJECTTYPE(GluonEngine,KeyboardInputComponent);

using namespace GluonEngine;

KeyboardInputComponent::KeyboardInputComponent(QObject* parent)
    : Component(parent)
{
    m_actionHeld = false;
    m_actionStarted = false;
    m_actionStopped = false;
    m_keyCode = Key_Space;
}

void
KeyboardInputComponent::start()
{
    DEBUG_FUNC_NAME


    foreach(const GluonInput::InputDevice *input, GluonInput::InputDetection::instance()->keyboardList())
    {
        DEBUG_TEXT(QString("Enabling input for device: %1").arg(input->deviceName()));
        connect(input, SIGNAL(eventSent(GluonInput::InputEvent*)), this, SLOT(inputEvent(GluonInput::InputEvent*)));
        connect(input, SIGNAL(buttonPressed(int)), this, SLOT(buttonPressed(int)));
    }
    GluonEngine::Component::start();
}

void
KeyboardInputComponent::update(int elapsedMilliseconds)
{
    if (m_actionStarted)
        m_actionStarted = false;

    if (m_actionStopped)
    {
        m_actionStopped = false;
        m_actionHeld = false;
    }

/*    if ( (m_distanceMovement == QVector3D(0,0,0)) && m_actionHeld )
        m_actionStopped = true;

    m_lastFrame = m_distanceMovement;
    m_distanceMovement = QVector3D(0,0,0);
    m_axisMovement = 0;*/
}

void KeyboardInputComponent::stop()
{
    disconnect(this, SLOT(inputEvent(GluonInput::InputEvent*)));
    GluonEngine::Component::stop();
}

void
KeyboardInputComponent::inputEvent(GluonInput::InputEvent *inputEvent)
{
    DEBUG_FUNC_NAME
    if(inputEvent->code() == m_keyCode)
    {
        if(inputEvent->value() == 0)
        {
            m_actionStopped = true;
        }
        else if(inputEvent->value() == 1)
        {
            m_actionStarted = true;
            m_actionHeld = true;
        }
    }
}

void KeyboardInputComponent::buttonPressed(int key)
{
    DEBUG_FUNC_NAME
    DEBUG_TEXT(QString("Key %1 was pressed.").arg(key));
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

KeyboardInputComponent::KeyName
KeyboardInputComponent::keyCode() const
{
    return m_keyCode;
}

void
KeyboardInputComponent::setKeyCode(const KeyName& newKeyCode)
{
    m_keyCode = newKeyCode;
}

// QVector3D
// KeyboardInputComponent::getDistanceMovement(const QString &actionName)
// {
//    return m_distanceMovement;
// }
//
// float
// KeyboardInputComponent::getAxisMovement(const QString &actionName)
// {
//    return m_distanceMovement.length();
// }

Q_EXPORT_PLUGIN2(gluon_component_keyboardinput, GluonEngine::KeyboardInputComponent);

#include "keyboardinputcomponent.moc"

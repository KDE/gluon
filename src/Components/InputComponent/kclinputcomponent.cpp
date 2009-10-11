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

#include "kclinputcomponent.h"


KCLInputComponent::KCLInputComponent(QObject* parent) : : Component(parent)
{
  QWidget::setMouseTracking();
}


KCLInputComponent::QMouseEvent::QMouseEvent(Type type, const QPoint& pos, const QPoint& globalPos, 
					    Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers)
{
  m_actionStarted = true;
  m_distanceMovement += QVector3D(pos.rx(), pos.ry(), 0);
  m_buttons = buttons;
  if (!m_actionStarted)
  {
    m_actionStarted = true;
    m_actionHeld = true;
  }
 
}



void KCLInputComponent::Draw(int timeLapse)
{
  if (m_actionStarted)
    m_actionStarted = false;
  
  if (m_actionStopped)
  {
    m_actionStopped = false;
    m_actionHeld = false;
  }
  
  if ( (m_distanceMovement == QVector3D(0,0,0)) && m_actionHeld )
    m_actionStopped = true;

  m_lastFrame = m_distanceMovement;
  m_distanceMovement = QVector3D(0,0,0);
  m_axisMovement = 0;
}


bool KCLInputComponent::GetActionStarted(QString actionName)
{
  return m_actionStarted;
}



bool KCLInputComponent::GetActionHeld(QString actionName)
{
  return m_actionHeld;
}



bool KCLInputComponent::GetActionStopped(QString actionName)
{
  return m_actionStopped;
}


QVector3D KCLInputComponent::GetDistanceMovement(QString actionName)
{
   return m_distanceMovement;
}


float KCLInputComponent::GetAxisMovement(QString actionName)
{
   return m_distanceMovement.length();
}









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

#ifndef KCLINPUTCOMPONENT_H
#define KCLINPUTCOMPONENT_H

#include "component.h"
#include <kcl/kcl.h>
#include <QWidget>
#include <QMouseEvent>
#include <QGui>

class KCLInputComponent
{

Q_OBJECT;
Q_PROPERTY(QList<InputAction> inputActions READ inputActions WRITE setInputActions);
 
public:
    KCLInputComponent(QObject * parent = 0);
    // True on any frame between GetActionStarted and
    // GetActionStopped, inclusive of those two frames
    bool GetActionHeld(QString actionName);
    // True on the frame when an action was begun (for example the
    // button represented by buttonName was pressed on a controller)
    bool GetActionStarted(QString actionName);
    // True on the frame when an action was stopped (for example a
    // button was released on a controller)
    bool GetActionStopped(QString actionName);
    // The movement compared to last frame
    QVector3D GetDistanceMovement(QString actionName);
    // The movement along one axis compared to last frame
    float GetAxisMovement(QString actionName);
    virtual void Draw(int timeLapse = 0);
       
private:
    QMouseEvent::QMouseEvent ( Type type, const QPoint & pos, const QPoint & globalPos, 
			       Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers );
    Qt::MouseButtons m_buttons;
    Qt::MouseButtons m_buttonsLastFrame;
    bool m_actionHeld;
    bool m_actionStarted;
    bool m_actionStopped;
    QVector3D m_distanceMovement;
    QVector3D m_lastFrame;
    float m_axisMovement;
    
  
  
};

#endif // KCLINPUTCOMPONENT_H

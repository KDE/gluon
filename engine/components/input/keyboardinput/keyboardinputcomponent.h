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

#ifndef KEYBOARDINPUTCOMPONENT_H
#define KEYBOARDINPUTCOMPONENT_H

#include "component.h"
#include "input/inputevent.h"
//#include "input/keyboard.h"
#include <QVector3D>

namespace GluonEngine
{
    class KeyboardInputComponent : public Component
    {
        Q_OBJECT;
        GLUON_OBJECT(GluonEngine::KeyboardInputComponent)
        Q_PROPERTY(KeyName keyCode READ keyCode WRITE setKeyCode);
        Q_ENUMS(KeyName)
        Q_INTERFACES(GluonEngine::Component)
        //Q_PROPERTY(QList<InputAction> inputActions READ inputActions WRITE setInputActions);

        public:
            enum KeyName
            {
                Key_Enter,
                Key_Space,
                Key_0
            };

            KeyboardInputComponent(QObject * parent = 0);

            //  True on any frame between getActionStarted and
            //  getActionStopped, inclusive of those two frames
            Q_INVOKABLE bool isActionHeld();
            // True on the frame when an action was begun (for example the
            // button represented by buttonName was pressed on a controller)
            Q_INVOKABLE bool isActionStarted();
            // True on the frame when an action was stopped (for example a
            // button was released on a controller)
            Q_INVOKABLE bool isActionStopped();
            // The movement compared to last frame
            //QVector3D getDistanceMovement(QString actionName);
            // The movement along one axis compared to last frame
            //float getAxisMovement(QString actionName);

            virtual void start();
            virtual void update(int elapsedMilliseconds);
            //virtual void draw(int timeLapse);
            virtual void stop();

            KeyName keyCode() const;
            void setKeyCode(const KeyName &newKeyCode);

        public Q_SLOTS:
            void inputEvent(GluonInput::InputEvent* inputEvent);

        private:
            KeyName m_keyCode;
/*            Qt::MouseButtons m_buttons;
            Qt::MouseButtons m_buttonsLastFrame;*/
            bool m_actionHeld;
            bool m_actionStarted;
            bool m_actionStopped;
/*            QVector3D m_distanceMovement;
            QVector3D m_lastFrame;
            float m_axisMovement;*/
    };
}

#endif // KEYBOARDINPUTCOMPONENT_H

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
#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <QtCore/QEvent>
#include <QtCore/QSharedData>

namespace GluonInput
{
    class InputEventPrivate;

    class InputEvent : public QEvent
    {
        public:
		
			enum InputTypeFlag 
			{
				Button = QEvent::Type(QEvent::User+1),
				RelativeAxis = QEvent::Type(QEvent::User+2),
				AbsoluteAxis = QEvent::Type(QEvent::User+3)
			};
		
            InputEvent(int code, int value, QEvent::Type eventType);

            int code() const;
            int value() const;

        private:
            QSharedDataPointer<InputEventPrivate> d;
    };
}
#endif

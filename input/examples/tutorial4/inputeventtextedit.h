/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef INPUTEVENTTEXTEDIT_H
#define INPUTEVENTTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMoveEvent>

class InputEventTextEdit : public QTextEdit
{
        Q_OBJECT
    public:
        explicit InputEventTextEdit( QTextEdit* parent = 0 );
        virtual ~InputEventTextEdit();

    protected:
        void keyPressEvent( QKeyEvent* event );
        void keyReleaseEvent( QKeyEvent* event );
        void mousePressEvent( QMouseEvent* event );
        void mouseReleaseEvent( QMouseEvent* event );
        void mouseMoveEvent( QMouseEvent* event );
        void moveEvent( QMoveEvent* event );

    signals:
        void buttonStateChanged( int code, int value );
};

#endif // INPUTEVENTTEXTEDIT_H

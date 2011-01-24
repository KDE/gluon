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

#include "inputeventtextedit.h"

InputEventTextEdit::InputEventTextEdit( QTextEdit* parent )
    : QTextEdit( parent )
{
}

InputEventTextEdit::~InputEventTextEdit()
{
}

void InputEventTextEdit::keyPressEvent( QKeyEvent* event )
{
    append( event->text() + " is pressed" );
}

void InputEventTextEdit::keyReleaseEvent( QKeyEvent* event )
{
    append( event->text() + " is released" );
}

void InputEventTextEdit::mousePressEvent( QMouseEvent* event )
{
}

void InputEventTextEdit::mouseReleaseEvent( QMouseEvent* event )
{
}

void InputEventTextEdit::mouseMoveEvent( QMouseEvent* event )
{
}

void InputEventTextEdit::moveEvent( QMoveEvent* event )
{
}

#include "inputeventtextedit.moc"

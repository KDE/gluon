/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "keyboardinputcomponenttest.h"

#include <engine/gameobject.h>
#include <engine/components/input/keyboardinput/keyboardinputcomponenttest.h>

#include <QtTest/QtTest>

using namespace GluonEngine;

KeyboardInputComponentTest::KeyboardInputComponentTest()
{
}

KeyboardInputComponentTest::~KeyboardInputComponentTest()
{
}

void KeyboardInputComponentTest::testCategory()
{
    KeyboardInputComponent keyboardInputComponent;
    QVERIFY(keyboardInputComponent.category() == "Input");
}

void KeyboardInputComponentTest::testInitialize()
{
}

void KeyboardInputComponentTest::testStart()
{
}

void KeyboardInputComponentTest::testUpdate()
{
}

void KeyboardInputComponentTest::testStop()
{
}

void KeyboardInputComponentTest::testKeyCode()
{
    KeyboardInputComponent keyboardInputComponent();
    QCOMPARE(keyboardInputComponent.keyCode(), Qt::Key_unknown);
    keyboardInputComponent.setKeyCode(Qt::Key_Escape);
    QCOMPARE(keyboardInputComponent.keyCode(), Qt::Key_Escape);
}

QTEST_MAIN(KeyboardInputComponentTest)

#include "keyboardinputcomponenttest.moc"

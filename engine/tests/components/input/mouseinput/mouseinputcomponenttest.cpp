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

#include "mouseinputcomponenttest.h"

#include <engine/gameobject.h>
#include <engine/components/input/mouseinput/mouseinputcomponent.h>

#include <QtTest/QtTest>

using namespace GluonEngine;

MouseInputComponentTest::MouseInputComponentTest()
{
}

MouseInputComponentTest::~MouseInputComponentTest()
{
}

void MouseInputComponentTest::testCategory()
{
    MouseInputComponent mouseInputComponent;
    QVERIFY(mouseInputComponent.category() == "Input");
}

void MouseInputComponentTest::testInitialize()
{
}

void MouseInputComponentTest::testStart()
{
}

void MouseInputComponentTest::testUpdate()
{
}

void MouseInputComponentTest::testStop()
{
}

void MouseInputComponentTest::testMouseButton()
{
    MouseInputComponent mouseInputComponent;
    QCOMPARE(mouseInputComponent.mouseButton(), GluonInput::Mouse::MOUSE_BUTTON_UNKNOWN);
    mouseInputComponent.setMouseButton(GluonInput::Mouse::MOUSE_BUTTON_LEFT);
    QCOMPARE(mouseInputComponent.mouseButton(), luonInput::Mouse::MOUSE_BUTTON_LEFT);
}

void MouseInputComponentTest::testMouseTrack()
{
    MouseInputComponent mouseInputComponent;
    QCOMPARE(mouseInputComponent.mouseTrack, false);
    bool enable = true;
    mouseInputComponent.setMouseTrack(enable);
    QCOMPARE(mouseInputComponent.mouseTrack(), enable);
}

QTEST_MAIN(MouseInputComponentTest)

#include "mouseinputcomponenttest.moc"

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

#include "componenttest.h"

#include <engine/component.h>
#include <engine/gameobject.h>

#include <QtTest/QtTest>

using namespace GluonEngine;

ComponentTest::ComponentTest()
{
}

ComponentTest::~ComponentTest()
{
}

void ComponentTest::testCategory()
{
    Component component;
    QVERIFY(component.category() == "Uncategorised");
}

void ComponentTest::testDescription()
{
    Component component;
    QVERIFY(component.description().isEmpty() == true);
    QString testDescription = "testDescription";
    component.setDescription(testDescription);
    QCOMPARE(component.description(), testDescription);
}

void ComponentTest::testEnabled()
{
    Component component;
    component.setEnabled(false);
    QCOMPARE(component.enabled(), false);
    component.setEnabled(true);
    QCOMPARE(component.enabled(), true);
    component.setEnabled(false);
    QCOMPARE(component.enabled(), false);
}

void ComponentTest::testGameObject()
{
    Component component;
    GameObject gameObject;
    component.setGameObject(&gameObject);
    QCOMPARE(component.gameObject(), &gameObject);
}

QTEST_MAIN(ComponentTest)

 

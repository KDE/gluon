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

#include "gameobjecttest.h"

#include <engine/gameobject.h>

#include <QtTest/QtTest>

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace GluonEngine;

GameObjectTest::GameObjectTest()
{
}

GameObjectTest::~GameObjectTest()
{
}

void GameObjectTest::testDescription()
{
    GameObject gameObject;
    QVERIFY(gameObject.description().isEmpty() == true);
    QString testDescription = "testDescription";
    gameObject.setDescription(testDescription);
    QCOMPARE(gameObject.description(), testDescription);
}

void GameObjectTest::testEnabled()
{
    GameObject gameObject;
    gameObject.setEnabled(false);
    QCOMPARE(gameObject.enabled(), false);
    gameObject.setEnabled(true);
    QCOMPARE(gameObject.enabled(), true);
    gameObject.setEnabled(false);
    QCOMPARE(gameObject.enabled(), false);
}

void GameObjectTest::testPosition()
{
    GameObject gameObject;
    Eigen::Vector3f vector3D(1.0, 2.0, 3.0);
    gameObject.setPosition(vector3D);
    QCOMPARE(gameObject.position(), vector3D);
}

void GameObjectTest::testScale()
{
    GameObject gameObject;
    Eigen::Vector3f vector3D(1.0, 2.0, 3.0);
    gameObject.setScale(vector3D);
    QCOMPARE(gameObject.scale(), vector3D);
}

void GameObjectTest::testOrientation()
{
    GameObject gameObject;
    Eigen::Quaternionf quaternion( 1.0, 2.0, 3.0, 1.0 );
    gameObject.setOrientation(quaternion);
    QCOMPARE(gameObject.orientation().x(), quaternion.x());
    QCOMPARE(gameObject.orientation().y(), quaternion.y());
    QCOMPARE(gameObject.orientation().z(), quaternion.z());
    QCOMPARE(gameObject.orientation().w(), quaternion.w());
}

QTEST_MAIN(GameObjectTest)

#include "gameobjecttest.moc"

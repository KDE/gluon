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

#include "gluonobjecttest.h"

#include <core/gluonobject.h>

#include <QtTest/QtTest>

using namespace GluonCore;

GluonObjectTest::GluonObjectTest()
{
}

GluonObjectTest::~GluonObjectTest()
{
}

void GluonObjectTest::testAddChild()
{
    GluonObject parentObject;
    GluonObject childObject;
    parentObject.addChild(&childObject);
    QCOMPARE(parentObject.children().count(), 1);
    QCOMPARE(&childObject, parentObject.children().at(0));
}

void GluonObjectTest::testAddChildAt()
{
    GluonObject parentObject;
    GluonObject childObject1;
    GluonObject childObject2;
    parentObject.addChild(&childObject1);
    parentObject.addChildAt(&childObject2, 0);
    QCOMPARE(&childObject2, parentObject.child(0));
    QCOMPARE(&childObject1, parentObject.child(1));
}

void GluonObjectTest::testChildAt()
{
    GluonObject parentObject("ParentObject");
    GluonObject childObject("ChildObject");
    parentObject.addChild(&childObject);
    QCOMPARE(&childObject, parentObject.child(0));
}

void GluonObjectTest::testChildByName()
{
    QString parentObjectName("ParentObject");
    GluonObject parentObject(parentObjectName);
    QString childObjectName("ChildObject");
    GluonObject childObject(childObjectName);
    parentObject.addChild(&childObject);

    QCOMPARE(&childObject, parentObject.child(childObjectName));
    QCOMPARE(&childObject, parentObject.findItemByName(childObjectName));

    QCOMPARE(&parentObject, parentObject.findGlobalItemByName(parentObjectName));
    QCOMPARE(&parentObject, childObject.findGlobalItemByName(parentObjectName));
    QCOMPARE(&childObject, parentObject.findGlobalItemByName(parentObjectName
                                                             + "/" + childObjectName));

    QString grandChildObjectName("grandChildObject");
    GluonObject grandChildObject(grandChildObjectName);
    childObject.addChild(&grandChildObject);

    QCOMPARE(&grandChildObject, childObject.findItemByName(grandChildObjectName));
    QCOMPARE(&grandChildObject, parentObject.findItemByName(childObjectName
                                                            + "/" + grandChildObjectName));
}

void GluonObjectTest::testName()
{
    GluonObject gluonObject;
    gluonObject.setName("GluonObjectTest");
    QCOMPARE(gluonObject.name(), QString("GluonObjectTest"));
}

void GluonObjectTest::testSupportedMimeTypes()
{
    GluonObject gluonObject;
    QCOMPARE(gluonObject.supportedMimeTypes(), QStringList());
}

void GluonObjectTest::testRemoveChild()
{
    GluonObject parentObject("ParentObject");
    GluonObject childObject("ChildObject");
    parentObject.addChild(&childObject);
    QCOMPARE(parentObject.children().count(), 1);
    QCOMPARE(&childObject, parentObject.children().at(0));
    parentObject.removeChild(&childObject);
    QCOMPARE(parentObject.children().isEmpty(), true);
}

void GluonObjectTest::testMetaInfo()
{
    GluonObject gluonObject;
    QVERIFY2(gluonObject.metaInfo() != 0, "The meta info has not been created \
             successfully!");
}

void GluonObjectTest::testHasMetaInfo()
{
    GluonObject gluonObject;
    QCOMPARE(gluonObject.hasMetaInfo(), false);
    gluonObject.metaInfo();
    QCOMPARE(gluonObject.hasMetaInfo(), true);
}

void GluonObjectTest::testQualifiedName()
{
    QString gluonObject1Name = "GluonObject1";
    QString gluonObject2Name = "GluonObject2";
    QString gluonObject3Name = "GluonObject3";
    GluonObject gluonObject1(gluonObject1Name);
    GluonObject gluonObject2(gluonObject2Name);
    GluonObject gluonObject3(gluonObject3Name);
    gluonObject1.addChild(&gluonObject2);
    gluonObject2.addChild(&gluonObject3);

    QCOMPARE(gluonObject1.qualifiedName(&gluonObject1), QString(""));
    QCOMPARE(gluonObject2.qualifiedName(&gluonObject1), gluonObject2Name);
    QCOMPARE(gluonObject2.qualifiedName(&gluonObject2), QString(""));
    QCOMPARE(gluonObject3.qualifiedName(&gluonObject1),
             gluonObject2Name + '/' + gluonObject3Name);
    QCOMPARE(gluonObject3.qualifiedName(&gluonObject2), gluonObject3Name);
    QCOMPARE(gluonObject3.qualifiedName(&gluonObject3), QString(""));

    // now with wrong local root
    QCOMPARE(gluonObject2.qualifiedName(&gluonObject3),
             gluonObject1Name + '/' + gluonObject2Name);
    QCOMPARE(gluonObject1.qualifiedName(&gluonObject3), gluonObject1Name);
}

void GluonObjectTest::testFullyQualifiedName()
{
    QString parentObjectName = "ParentObject";
    QString childObjectName = "ChildObject";
    GluonObject parentObject(parentObjectName);
    GluonObject childObject(childObjectName);
    parentObject.addChild(&childObject);
    QCOMPARE(childObject.fullyQualifiedName(),
             parentObjectName + '/' + childObjectName);
}

void GluonObjectTest::testNameToObjectName()
{
    GluonObject gluonObject;
    QCOMPARE(gluonObject.nameToObjectName("@_Gluon Object1&"), QString("_GluonObject1"));
}

QTEST_MAIN(GluonObjectTest)

#include "gluonobjecttest.moc"

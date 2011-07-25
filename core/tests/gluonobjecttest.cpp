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

void GluonObjectTest::testChildAt()
{
    GluonObject parentObject("ParentObject");
    GluonObject childObject("ChildObject");
    parentObject.addChild(&childObject);
    QCOMPARE(&childObject, parentObject.child(0));
}

void GluonObjectTest::testChildByName()
{
    GluonObject parentObject("ParentObject");
    GluonObject childObject("ChildObject");
    parentObject.addChild(&childObject);
    QCOMPARE(&childObject, parentObject.child("ChildObject"));
    QCOMPARE(&childObject, parentObject.findItemByName("ChildObject"));
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
}

void GluonObjectTest::testShouldSerializeChildren()
{
    GluonObject gluonObject;
    QCOMPARE(gluonObject.shouldSerializeChildren(), true);
}

void GluonObjectTest::testQualifiedname()
{
    GluonObject gluonObject1("GluonObject1");
    GluonObject gluonObject2("GluonObject2");
    GluonObject gluonObject3("GluonObject3");
    gluonObject1.addChild(&gluonObject2);
    gluonObject2.addChild(&gluonObject3);
    QCOMPARE(gluonObject1.qualifiedName(&gluonObject3), QString("GluonObject1"));
    QCOMPARE(gluonObject2.qualifiedName(&gluonObject3), QString("GluonObject1/GluonObject2"));
    QCOMPARE(gluonObject3.qualifiedName(&gluonObject3), QString("GluonObject1/GluonObject2/GluonObject3"));
}

void GluonObjectTest::testFullyqualifiedname()
{
    GluonObject parentObject("ParentObject");
    GluonObject childObject("ChildObject");
    parentObject.addChild(&childObject);
    QCOMPARE(childObject.fullyQualifiedName(), QString("ParentObject/ChildObject"));
}

void GluonObjectTest::testNameToObjectName()
{
    GluonObject gluonObject;
    QCOMPARE(gluonObject.nameToObjectName("@GluonObject&"),QString("GluonObject"));
}

QTEST_MAIN(GluonObjectTest)

#include "gluonobjecttest.moc"

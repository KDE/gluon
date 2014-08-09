/******************************************************************************
 * This file is part of the Gluon Development Platform
 *
 * Copyright (c) 2010 Clark Gaebel <cg.wowus.cg@gmail.com>
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

#include "gdlserializertest.h"

#include <core/gdlserializer.h>
#include <core/gluonobject.h>
#include <core/gluonvarianttypes.h>

#include <QtTest>
#include <QMetaProperty>
#include <QColor>

#define CHECK_PARSE(source, target, count)\
    GluonObjectList target;\
    QVERIFY(GDLSerializer::instance()->parse(source, target));\
    QCOMPARE(target.size(), count);

#define CHECK_PROPERTY(object, name, proptype)\
    QVERIFY(object->dynamicPropertyNames().contains(#name));\
    QVariant name = object->property(#name);\
    QCOMPARE(static_cast<int>(name.type()), static_cast<int>(proptype));

#define CHECK_PROPERTY_VALUE(object, name, proptype, convert, expected)\
    CHECK_PROPERTY(object, name, proptype);\
    QCOMPARE(name.convert(), expected);

#define CHECK_OBJECT(object, expectedName, childCount)\
    QCOMPARE(object->metaObject()->className(), "GluonCore::GluonObject");\
    QCOMPARE(object->name(), QStringLiteral(#expectedName));\
    QCOMPARE(object->children().size(), childCount);

/**
 * Additional things to test:
 * - Whitespace/newlines
 * - Incorrect input that should not be parsed.
 * - Incorrect values for properties, like uint(-5) and similar error cases.
 * - Object references
 */

using namespace GluonCore;

GDLSerializerTest::GDLSerializerTest( QObject* parent )
    : QObject(parent)
{
}

GDLSerializerTest::~GDLSerializerTest()
{
}

void GDLSerializerTest::initTestCase()
{
    m_singleObjectSingleProperty = "{ GluonCore::GluonObject(\"TestObject\") testProperty int(10) }";
    m_singleObjectMultiProperty =
        "{ GluonCore::GluonObject(\"TestObject\")"
        "    boolProperty bool(true)"
        "    uintProperty uint(5)"
        "    intProperty int(-5)"
        "    longProperty longlong(9)"
        "    floatProperty float(3.14)"
        "    stringProperty string(\"Test\")"
        "    rgbaProperty rgba(255; 255; 255; 100)"
        "    vector2dProperty vector2d(5.0; 5.0)"
        "    vector3dProperty vector3d(5.0; 5.0; 5.0)"
        "    vector4dProperty vector4d(5.0; 5.0; 5.0; 5.0)"
        "    quaternionProperty quaternion(1.0; 0.0; 0.0; 0.0)"
        "    size2dProperty size2d(5.0; 5.0)"
        "    urlProperty url(\"http://gamingfreedom.org\")"
        "}";
    m_objectTree =
        "{ GluonCore::GluonObject(\"TestParent\")"
        "    parentProperty int(10)"
        "    { GluonCore::GluonObject(\"TestChild\")"
        "        childProperty int(10)"
        "        { GluonCore::GluonObject(\"TestGrandChild\") }"
        "    }"
        "    { GluonCore::GluonObject(\"TestSibling\") }"
        "}";

    m_multiRoot =
        "{ GluonCore::GluonObject(\"TestObject1\")"
        "    testProperty int(10)"
        "}"
        "{ GluonCore::GluonObject(\"TestObject2\")"
        "    testProperty2 int(10)"
        "}";

    m_multiLineString =
        "{ GluonCore::GluonObject(\"TestObject\")"
        "    stringProperty string(\"Some very long testing test\nwith several\nnewlines\nembedded\")"
        "}";

    m_list =
        "{ GluonCore::GluonObject(\"TestObject\")"
        "    listProperty list([int(10); float(3.14); vector4d(5.0; 5.0; 5.0; 5.0);])"
        "}";
}

void GDLSerializerTest::testSingleObjectSingleProperty()
{
    CHECK_PARSE(m_singleObjectSingleProperty, list, 1)

    GluonObject* object = list.at(0);
    CHECK_OBJECT(object, TestObject, 0)
    CHECK_PROPERTY_VALUE(object, testProperty, QMetaType::Int, toInt, 10)
}

void GDLSerializerTest::testSingleObjectMultiProperty()
{
    CHECK_PARSE(m_singleObjectMultiProperty, list, 1)

    GluonObject* object = list.at(0);
    CHECK_OBJECT(object, TestObject, 0)

    CHECK_PROPERTY_VALUE(object, boolProperty, QMetaType::Bool, toBool, true)
    CHECK_PROPERTY_VALUE(object, uintProperty, QMetaType::UInt, toUInt, 5u)
    CHECK_PROPERTY_VALUE(object, intProperty, QMetaType::Int, toInt, -5)
    CHECK_PROPERTY_VALUE(object, longProperty, QMetaType::LongLong, toLongLong, 9LL)
    CHECK_PROPERTY_VALUE(object, floatProperty, QMetaType::Float, toFloat, 3.14f)
    CHECK_PROPERTY_VALUE(object, stringProperty, QMetaType::QString, toString, QStringLiteral("Test"))
    CHECK_PROPERTY_VALUE(object, urlProperty, QMetaType::QUrl, toUrl, QUrl("http://gamingfreedom.org"))
    CHECK_PROPERTY_VALUE(object, size2dProperty, QMetaType::QSizeF, toSizeF, QSizeF(5.0f, 5.0f))

    CHECK_PROPERTY(object, rgbaProperty, QMetaType::QColor)
    QCOMPARE(rgbaProperty.value<QColor>(), QColor(255, 255, 255, 100));

    CHECK_PROPERTY(object, vector2dProperty, QMetaType::User)
    QCOMPARE(vector2dProperty.userType(), VariantType::Vector2f);
    QCOMPARE(vector2dProperty.value<Eigen::Vector2f>(), Eigen::Vector2f(5.0, 5.0));

    CHECK_PROPERTY(object, vector3dProperty, QMetaType::User)
    QCOMPARE(vector3dProperty.userType(), VariantType::Vector3f);
    QCOMPARE(vector3dProperty.value<Eigen::Vector3f>(), Eigen::Vector3f(5.0, 5.0, 5.0));

    CHECK_PROPERTY(object, vector4dProperty, QMetaType::User)
    QCOMPARE(vector4dProperty.userType(), VariantType::Vector4f);
    QCOMPARE(vector4dProperty.value<Eigen::Vector4f>(), Eigen::Vector4f(5.0, 5.0, 5.0, 5.0));

    CHECK_PROPERTY(object, quaternionProperty, QMetaType::User)
    QCOMPARE(quaternionProperty.userType(), VariantType::Quaternionf);
    Eigen::Quaternionf v = quaternionProperty.value<Eigen::Quaternionf>();
    Eigen::Quaternionf q(0.0, 1.0, 0.0, 0.0);
    QCOMPARE(v.coeffs(), q.coeffs());
}

void GDLSerializerTest::testObjectTree()
{
    CHECK_PARSE(m_objectTree, list, 1);

    GluonObject* object = list.at(0);
    CHECK_OBJECT(object, TestParent, 2)
    CHECK_PROPERTY_VALUE(object, parentProperty, QMetaType::Int, toInt, 10)

    object = object->child(0);
    CHECK_OBJECT(object, TestChild, 1)
    CHECK_PROPERTY_VALUE(object, childProperty, QMetaType::Int, toInt, 10)

    object = object->child(0);
    CHECK_OBJECT(object, TestGrandChild, 0)

    object = list.at(0)->child(1);
    CHECK_OBJECT(object, TestSibling, 0)
}

void GDLSerializerTest::testMultiRoot()
{
    CHECK_PARSE(m_multiRoot, list, 2)

    GluonObject* object = list.at(0);
    CHECK_OBJECT(object, TestObject1, 0)
    CHECK_PROPERTY_VALUE(object, testProperty, QMetaType::Int, toInt, 10)

    object = list.at(1);
    CHECK_OBJECT(object, TestObject2, 0)
    CHECK_PROPERTY_VALUE(object, testProperty2, QMetaType::Int, toInt, 10)
}

void GDLSerializerTest::testMultilineString()
{
    CHECK_PARSE(m_multiLineString, list, 1)

    GluonObject* object = list.at(0);
    CHECK_OBJECT(object, TestObject, 0)
    CHECK_PROPERTY_VALUE(object, stringProperty, QMetaType::QString, toString, QStringLiteral("Some very long testing test\nwith several\nnewlines\nembedded"))
}

void GDLSerializerTest::testList()
{
    CHECK_PARSE(m_list, objectList, 1)

    GluonObject* object = objectList.at(0);
    CHECK_OBJECT(object, TestObject, 0)

    QVERIFY(object->dynamicPropertyNames().contains("listProperty"));
    QVariant listProperty = object->property("listProperty");

    QVariantList list = listProperty.toList();
    QCOMPARE(list.size(), 3);

    QVariant listItem0 = list.at(0);
    QCOMPARE(static_cast<int>(listItem0.type()), static_cast<int>(QMetaType::Int));
    QCOMPARE(listItem0.toInt(), 10);

    QVariant listItem1 = list.at(1);
    QCOMPARE(static_cast<int>(listItem1.type()), static_cast<int>(QMetaType::Float));
    QCOMPARE(listItem1.toFloat(), 3.14f);

    QVariant listItem2 = list.at(2);
    QCOMPARE(static_cast<int>(listItem2.type()), static_cast<int>(QMetaType::User));
    QCOMPARE(listItem2.userType(), GluonCore::VariantType::Vector4f);
    QCOMPARE(listItem2.value<Eigen::Vector4f>(), Eigen::Vector4f(5.f, 5.f, 5.f, 5.f));
}

QTEST_MAIN(GDLSerializerTest)

 

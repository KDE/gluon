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

#include "metainfotest.h"

#include <core/metainfo.h>

#include <QtTest/QtTest>

using namespace GluonCore;

MetaInfoTest::MetaInfoTest()
{
}

MetaInfoTest::~MetaInfoTest()
{
}

void MetaInfoTest::testHasPropertyRange()
{
    MetaInfo metaInfo(0);
    QCOMPARE(metaInfo.hasPropertyRange("test"), false);
    metaInfo.setPropertyRange("test", 0.0, 10.0);
    QCOMPARE(metaInfo.hasPropertyRange("test"), true);
}

void MetaInfoTest::testPropertyRangeMin()
{
    MetaInfo metaInfo(0);
    metaInfo.setPropertyRange("test", 0.0, 10.0);
    QCOMPARE(metaInfo.propertyRangeMin("test"), 0.0);
}

void MetaInfoTest::testPropertyRangeMax()
{
    MetaInfo metaInfo(0);
    metaInfo.setPropertyRange("test", 0.0, 10.0);
    QCOMPARE(metaInfo.propertyRangeMax("test"), 10.0);
}

void MetaInfoTest::testRemovePropertyRange()
{
    MetaInfo metaInfo(0);
    metaInfo.setPropertyRange("test", 0.0, 10.0);
    QCOMPARE(metaInfo.hasPropertyRange("test"), true);
    metaInfo.removePropertyRange("test");
    QCOMPARE(metaInfo.hasPropertyRange("test"), false);
}

void MetaInfoTest::testBoundRange()
{
    MetaInfo metaInfo(0);
    metaInfo.setPropertyRange("test", 10.0, 20.0);

    QCOMPARE(metaInfo.hasPropertyRange("test"), true);
    QCOMPARE(metaInfo.applyRange("test", 5.0), 10.0);
    QCOMPARE(metaInfo.applyRange("test", 50.0), 20.0);
}

void MetaInfoTest::testHasPropertySteps()
{
    MetaInfo metaInfo(0);
    QCOMPARE(metaInfo.hasPropertySteps("test"), false);
    metaInfo.setPropertySteps("test", 10);
    QCOMPARE(metaInfo.hasPropertySteps("test"), true);
}

void MetaInfoTest::testPropertySteps()
{
    MetaInfo metaInfo(0);
    metaInfo.setPropertySteps("test", 10);
    QVERIFY(metaInfo.propertySteps("test") == 10);
}

void MetaInfoTest::testRemovePropertySteps()
{
    MetaInfo metaInfo(0);
    metaInfo.setPropertySteps("test", 10);
    QCOMPARE(metaInfo.hasPropertySteps("test"), true);
    metaInfo.removePropertySteps("test");
    QCOMPARE(metaInfo.hasPropertySteps("test"), false);
}

void MetaInfoTest::testBoundSteps()
{
    MetaInfo metaInfo(0);
    QCOMPARE(metaInfo.hasPropertyRange("test"), false);
    QCOMPARE(metaInfo.hasPropertySteps("test"), false);
    metaInfo.setPropertySteps("test", 10);
    metaInfo.setPropertyRange("test", 0.0, 10.0);
    QCOMPARE(metaInfo.applySteps("test", 5.1), 5.0);
}

void MetaInfoTest::testBoundRangeAndSteps()
{
    MetaInfo metaInfo(0);
    QCOMPARE(metaInfo.hasPropertyRange("test"), false);
    QCOMPARE(metaInfo.hasPropertySteps("test"), false);
    metaInfo.setPropertySteps("test", 10);
    metaInfo.setPropertyRange("test", 10.0, 20.0);
    QCOMPARE(metaInfo.applyRangeAndStep("test", 5.0), 10.0);
    QCOMPARE(metaInfo.applyRangeAndStep("test", 50.0), 20.0);
}

void MetaInfoTest::testDefaultExtension()
{
    MetaInfo metaInfo(0);
    QCOMPARE(metaInfo.defaultExtension(), QString());
    metaInfo.setDefaultExtension("test");
    QCOMPARE(metaInfo.defaultExtension(), QString("test"));
}

QTEST_MAIN(MetaInfoTest)

#include "metainfotest.moc"

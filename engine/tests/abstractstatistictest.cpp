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

#include "abstractstatistictest.h"

#include <engine/abstractstatistic.h>

#include <QtTest/QtTest>

using namespace GluonEngine;

AbstractStatisticTest::AbstractStatisticTest()
{
}

AbstractStatisticTest::~AbstractStatisticTest()
{
}

void AbstractStatisticTest::testIsDatabaseOpen()
{
    AbstractStatistic abstractStatistic;
    QCOMPARE(abstractStatistic.isDatabaseOpen(), false);
}

void AbstractStatisticTest::testInitialize()
{
}

void AbstractStatisticTest::testCleanup()
{
}

void AbstractStatisticTest::testSetName()
{
    AbstractStatistic abstractStatistic;
    const QString name = "testAbstractStatistic";
    abstractStatistic.setName(name);
    QCOMPARE(abstractStatistic.name(), name);
    QCOMPARE(abstractStatistic.isDatabaseOpen(), false);
}

void AbstractStatisticTest::testValue()
{
    AbstractStatistic abstractStatistic;
    const qlonglong value = 100000;
    abstractStatistic.setValue(value);
    QCOMPARE(abstractStatistic.value(), value);
}

void AbstractStatisticTest::testInvalidate()
{
    AbstractStatistic abstractStatistic;
    // TODO: initialize here
    abstractStatistic.invalidate();
    QCOMPARE(abstractStatistic.isDatabaseOpen(), false);
}

// void AbstractStatisticTest::testArray()
// {
    // QList<qlonglong> array;
    // array << 100000 << 50000;
    // AbstractStatistic abstractStatistic;
    // abstractStatistic.setArray(array);
    // QCOMPARE(abstractStatistic.array(), array);
// }

// void AbstractStatisticTest::testArrayAppend()
// {
    // QList<qlonglong> array;
    // array << 100000 << 50000;
    // AbstractStatistic abstractStatistic;
    // abstractStatistic.arrayAppend(100000);
    // abstractStatistic.arrayAppend(50000);
    // QCOMPARE(abstractStatistic.array(), array());
// }

// void AbstractStatisticTest::testRemoveAt()
// {
    // QList<qlonglong> array;
    // array << 100000 << 50000;
    // AbstractStatistic abstractStatistic;
    // abstractStatistic.arrayAppend(100000);
    // abstractStatistic.arrayAppend(50000);
    // abstractStatistic.arrayAppend(10000);
    // QCOMPARE(abstractStatistic.array(), array());
// }

void AbstractStatisticTest::testCommit()
{
}

QTEST_MAIN(AbstractStatisticTest)

 

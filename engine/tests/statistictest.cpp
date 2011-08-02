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

#include "statistictest.h"

#include <engine/statistic.h>

#include <QtTest/QtTest>

using namespace GluonEngine;

StatisticTest::StatisticTest()
{
}

StatisticTest::~StatisticTest()
{
}

void StatisticTest::testScore()
{
    Statistic statistic;
    QCOMPARE(statistic.score(), 0ll);
    statistic.setScore(100000);
    QCOMPARE(statistic.score(), 100000ll);
}

void StatisticTest::testIncrease()
{
    Statistic statistic;
    QCOMPARE(statistic.score(), 0ll);
    statistic.increase();
    QCOMPARE(statistic.score(), 1ll);
}

void StatisticTest::testDecrease()
{
    Statistic statistic;
    QCOMPARE(statistic.score(), 0ll);
    statistic.add(500000);
    QCOMPARE(statistic.score(), 500000ll);
    statistic.decrease();
    QCOMPARE(statistic.score(), 499999ll);
}

void StatisticTest::testAdd()
{
    Statistic statistic;
    QCOMPARE(statistic.score(), 0ll);
    statistic.add(50000);
    QCOMPARE(statistic.score(), 50000ll);
}

void StatisticTest::testSub()
{
    Statistic statistic;
    QCOMPARE(statistic.score(), 0ll);
    statistic.add(200000);
    QCOMPARE(statistic.score(), 200000ll);
    statistic.sub(20000);
    QCOMPARE(statistic.score(), 180000ll);
}

void StatisticTest::testReset()
{
    Statistic statistic;
    QCOMPARE(statistic.score(), 0ll);
    statistic.add(2000000);
    QCOMPARE(statistic.score(), 2000000ll);
    statistic.reset();
    QCOMPARE(statistic.score(), 0ll);
}

void StatisticTest::testCommitScore()
{
    Statistic statistic;
    QCOMPARE(statistic.score(), 0ll);
    statistic.setScore(45000);
    statistic.commitScore();
    QCOMPARE(statistic.score(), 45000ll);
    statistic.setScore(0);
    statistic.commitScore();
    QCOMPARE(statistic.value(), 45000ll);
}

QTEST_MAIN(StatisticTest)

#include "statistictest.moc"

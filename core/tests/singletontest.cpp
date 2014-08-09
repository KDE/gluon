/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 <copyright>
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

#include "singletontest.h"

#include <QtTest>

using namespace GluonCore;

GLUON_DEFINE_SINGLETON(GluonCore::TestSingleton)

TestSingleton::TestSingleton(QObject* parent)
    : Singleton< GluonCore::TestSingleton >(parent)
{

}

QTEST_MAIN(SingletonTest);

void SingletonTest::initTestCase()
{
    // Called before the first testfunction is executed
}

void SingletonTest::cleanupTestCase()
{
    // Called after the last testfunction was executed
}

void SingletonTest::init()
{
    // Called before each testfunction is executed
}

void SingletonTest::cleanup()
{
    // Called after every testfunction
}

void SingletonTest::testThreadedRead()
{

}

void SingletonTest::testRead()
{
//     QCOMPARE(TestSingleton::sm_instance.load(), nullptr);

//     TestSingleton::instance();

    QCOMPARE(TestSingleton::instance(), TestSingleton::sm_instance.load());
}



/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Aish Raj Dahal <dahalaishraj@gmail.com>
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

#include "btbraintest.h"

#include <smarts/lib/btbrain.h>
#include <smarts/lib/btfactory.h>

#include <QtTest/QtTest>

using namespace GluonSmarts;

btbraintest::btbraintest()
    :m_testNameString("TestNameString")
    ,m_testFileString("TestFileString")
    ,m_testDescString("TestDescString")
{
}

btbraintest::~btbraintest()
{
}

void btbraintest::testSetName()
{
    btBrain parentNode( m_testNameString, m_testFileString, this);
    parentNode.setName(m_testNameString);
    QCOMPARE(parentNode.name(), m_testNameString);
}

void btbraintest::testSetDescription()
{
    btBrain parentNode( m_testNameString, m_testFileString, this);
    parentNode.setDescription(m_testDescString);
    QCOMPARE(parentNode.description(), m_testDescString);
}

QTEST_MAIN(btbraintest)
#include "btbraintest.moc"


/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Laszlo Papp <lpapp@kde.org>
 * Copyright (c) 2012 Arnolds Bogdanovs <arnolds.bogdanovs@inbox.lv>
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

#include "btnodetest.h"

#include <smarts/lib/btnode.h>
#include <smarts/lib/btfactory.h>

#include <QtTest/QtTest>

using namespace GluonSmarts;

btnodetest::btnodetest()
    : m_testString("TestString")
    , m_overRangeValue(10)
    , m_firstChild(0)
    , m_secondChild(1)
{
}

btnodetest::~btnodetest()
{
}

void btnodetest::testSetName()
{
    btNode parentNode(this);
    parentNode.setName(m_testString);
    QCOMPARE(parentNode.name(), m_testString);
}

void btnodetest::testSetDescription()
{
    btNode parentNode(this);
    parentNode.setDescription(m_testString);
    QCOMPARE(parentNode.description(), m_testString);
}

void btnodetest::testSetClassName()
{
    btNode parentNode(this);
    parentNode.setClassName(m_testString);
    QCOMPARE(parentNode.className(), m_testString);
}

void btnodetest::testSetType()
{
    btNode parentNode(this);
    QCOMPARE(parentNode.type(), GluonSmarts::btNode::UnusableNodeType);

    parentNode.setType(GluonSmarts::btNode::ActionNodeType);
    QCOMPARE(parentNode.type(), GluonSmarts::btNode::ActionNodeType);
}

void btnodetest::testAppendChild()
{
    btNode parentNode(this);
    btNode* childNode = new btNode(this);
    QCOMPARE(parentNode.childCount(), 0);

    parentNode.appendChild(childNode);
    QCOMPARE(parentNode.childCount(), 1);
    QCOMPARE(parentNode.child(0), childNode);
}

void btnodetest::testInsertChild()
{
    btNode parentNode(this);
    btNode* childNode = new btNode(this);
    btNode* childNode2 = new btNode(this);
    QCOMPARE(parentNode.childCount(), 0);

    parentNode.insertChild(0, childNode);
    QCOMPARE(parentNode.childCount(), 1);
    QCOMPARE(parentNode.child(m_firstChild), childNode);

    parentNode.insertChild(m_overRangeValue, childNode2);
    QCOMPARE(parentNode.childCount(), 2);
    QCOMPARE(parentNode.child(m_secondChild), childNode2);
}

void btnodetest::testRemoveChild()
{
    btNode parentNode(this);
    btNode* childNode = new btNode(this);
    QCOMPARE(parentNode.childCount(), 0);

    parentNode.appendChild(childNode);
    QCOMPARE(parentNode.childCount(), 1);

    parentNode.removeChild(m_firstChild);
    QCOMPARE(parentNode.childCount(), 0);

    parentNode.removeChild(m_firstChild);
    QCOMPARE(parentNode.childCount(), 0);

    parentNode.appendChild(childNode);
    QCOMPARE(parentNode.childCount(), 1);

    parentNode.removeChild(m_overRangeValue);
    QCOMPARE(parentNode.childCount(), 1);
}

void btnodetest::testSetCurrentChildIndex()
{
    btNode parentNode(this);
    btNode* childNode = new btNode(this);
    QCOMPARE(parentNode.childCount(), 0);
    QCOMPARE(parentNode.currentChildIndex(), m_firstChild);

    parentNode.appendChild(childNode);
    QCOMPARE(parentNode.childCount(), 1);

    parentNode.setCurrentChildIndex(m_secondChild);
    QCOMPARE(parentNode.currentChildIndex(), m_secondChild);
}

void btnodetest::testNextChildIndex()
{
    btNode parentNode(this);
    btNode* childNode = new btNode(this);
    QCOMPARE(parentNode.childCount(), 0);
    QCOMPARE(parentNode.currentChildIndex(), m_firstChild);

    parentNode.appendChild(childNode);
    QCOMPARE(parentNode.childCount(), 1);
    QCOMPARE(parentNode.currentChildStatus(), GluonSmarts::btNode::None);

    parentNode.setCurrentChildStatus(GluonSmarts::btNode::Succeeded);
    QCOMPARE(parentNode.currentChildStatus(), GluonSmarts::btNode::Succeeded);
    QCOMPARE(parentNode.nextChildIndex(), m_secondChild);
}

void btnodetest::testRunChild()
{
    btNode parentNode(this);
    btNode* selectorChild = GluonSmarts::btFactory::instance()->newObject("[selector]");
    QCOMPARE(parentNode.childCount(), 0);

    parentNode.appendChild(selectorChild);
    QCOMPARE(parentNode.childCount(), 1);

    QCOMPARE(parentNode.runChild(m_firstChild), GluonSmarts::btNode::RunningChild);
    QCOMPARE(parentNode.currentChildIndex(), m_firstChild);
    QCOMPARE(parentNode.currentChildStatus(), GluonSmarts::btNode::None);

    parentNode.removeChild(m_firstChild);
    QCOMPARE(parentNode.childCount(), 0);

    btNode* sequenceChild = GluonSmarts::btFactory::instance()->newObject("[sequence]");
    parentNode.appendChild(sequenceChild);
    QCOMPARE(parentNode.childCount(), 1);

    QCOMPARE(parentNode.runChild(m_firstChild), GluonSmarts::btNode::RunningChild);
    QCOMPARE(parentNode.currentChildIndex(), m_firstChild);
    QCOMPARE(parentNode.currentChildStatus(), GluonSmarts::btNode::None);
}

void btnodetest::testSetCurrentChildStatus()
{
    btNode parentNode(this);
    btNode* childNode = new btNode(this);
    QCOMPARE(parentNode.childCount(), 0);
    QCOMPARE(parentNode.currentChildIndex(), m_firstChild);
    QCOMPARE(parentNode.currentChildStatus(), GluonSmarts::btNode::None);

    parentNode.appendChild(childNode);
    QCOMPARE(parentNode.childCount(), 1);

    parentNode.setCurrentChildIndex(m_secondChild);
    QCOMPARE(parentNode.currentChildIndex(), m_secondChild);

    parentNode.setCurrentChildStatus(GluonSmarts::btNode::Succeeded);
    QCOMPARE(parentNode.currentChildStatus(), GluonSmarts::btNode::Succeeded);
}

void btnodetest::testSetParentNode()
{
    btNode* parentNode = new btNode(this);
    btNode* childNode = new btNode(this);
    QVERIFY2( childNode->parentNode() == 0, "The parent of every node should be null when first initialized" );

    childNode->setParentNode(parentNode);
    QCOMPARE(childNode->parentNode(), parentNode);
}


QTEST_MAIN(btnodetest)

#include "btnodetest.moc"

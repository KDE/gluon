/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#include "prefabtest.h"

#include <engine/gameobject.h>
#include <engine/prefabinstance.h>
#include <engine/prefabinstancechild.h>
#include <engine/prefab.h>

#include <QtGui/QVector3D>
#include <QtCore/QDebug>
#include <QtTest/QtTest>

using namespace GluonEngine;

PrefabTest::PrefabTest()
    : m_parent(0)
    , m_instance(0)
    , m_prefab(0)
{
}

PrefabTest::~PrefabTest()
{
}

void PrefabTest::init()
{
    m_parent = new GameObject();
    GameObject* tmpObject = new GameObject();
    tmpObject->setName( "Root Object" );
    tmpObject->setPosition( 0, 0, 0 );
    tmpObject->setScale( 1, 1, 1 );
    GameObject* childObject = new GameObject();
    childObject->setName( "Node Object" );
    childObject->setPosition( 0, 0, 0 );
    childObject->setScale( 1, 1, 1 );
    m_parent->addChild( tmpObject );
    tmpObject->addChild( childObject );
    m_parent->initialize();

    m_prefab = new Prefab();
    m_prefab->setName( tmpObject->name() );
    m_prefab->setGameObject( tmpObject );
    m_instance = qobject_cast<PrefabInstance*>( m_parent->childGameObject(0) );
}

void PrefabTest::cleanup()
{
    m_instance->deleteLater();
    m_prefab->deleteLater();
    m_parent->deleteLater();
    m_instance = 0;
    m_prefab = 0;
    m_parent = 0;
}

void PrefabTest::testInit()
{
    GameObject* gameObject = m_prefab->gameObject();
    QVERIFY( gameObject );
    QCOMPARE( gameObject->name(), QString("Root Object") );
    QCOMPARE( gameObject->parent(), m_prefab );
    QCOMPARE( gameObject->childCount(), 1 );
    QCOMPARE( gameObject->childGameObject(0)->name(), QString("Node Object") );
    QCOMPARE( gameObject->childGameObject(0)->childCount(), 0 );

    QCOMPARE( m_instance->name(), QString("Root Object") );
    QCOMPARE( m_instance->parent(), m_parent );
    QCOMPARE( m_instance->childCount(), 1 );
    QCOMPARE( m_instance->childGameObject(0)->name(), QString("Node Object") );
    QCOMPARE( m_instance->childGameObject(0)->childCount(), 0 );
}

void PrefabTest::testChangeRevert()
{
    m_instance->setPosition( 10, 11, 25.37 );
    m_instance->setScale( 10, 10, 10 );
    GameObject* child = m_instance->childGameObject(0);
    child->setPosition( 55, 66, 77 );
    child->setScale( 12, 12, 15 );

    m_instance->revertChanges();

    QCOMPARE( m_instance->position(), QVector3D( 0, 0, 0 ) );
    QCOMPARE( m_instance->scale(), QVector3D( 1, 1, 1 ) );
    QCOMPARE( m_instance->childGameObject(0)->position(), QVector3D( 0, 0, 0 ) );
    QCOMPARE( m_instance->childGameObject(0)->scale(), QVector3D( 1, 1, 1 ) );
    QCOMPARE( m_instance->childCount(), 1 );
    QCOMPARE( m_instance->childGameObject(0)->childCount(), 0 );
    QCOMPARE( m_prefab->gameObject()->childCount(), 1 );
}

void PrefabTest::testChangeApply()
{
    m_instance->setPosition( 10, 11, 25.37 );
    m_instance->setScale( 10, 10, 10 );
    GameObject* child = m_instance->childGameObject(0);
    child->setPosition( 55, 66, 77 );
    child->setScale( 12, 12, 15 );

    m_instance->storeChanges();

    QCOMPARE( m_instance->position(), QVector3D( 10, 11, 25.37 ) );
    QCOMPARE( m_instance->scale(), QVector3D( 10, 10, 10 ) );
    QCOMPARE( child->position(), QVector3D( 55, 66, 77 ) );
    QCOMPARE( child->scale(), QVector3D( 12, 12, 15 ) );
    QCOMPARE( m_instance->childCount(), 1 );
    QCOMPARE( child->childCount(), 0 );
    QCOMPARE( m_prefab->gameObject()->position(), QVector3D( 10, 11, 25.37 ) );
    QCOMPARE( m_prefab->gameObject()->scale(), QVector3D( 10, 10, 10 ) );
    QCOMPARE( m_prefab->gameObject()->childCount(), 1 );
}

void PrefabTest::testRemoveRevert()
{
    m_instance->removeChild( m_instance->childGameObject(0) );

    m_instance->revertChanges();

    GameObject* gameObject = m_prefab->gameObject();
    QCOMPARE( gameObject->childCount(), 1 );
    QCOMPARE( gameObject->childGameObject(0)->name(), QString("Node Object") );
    QCOMPARE( gameObject->childGameObject(0)->childCount(), 0 );

    QCOMPARE( m_instance->childCount(), 1 );
    QCOMPARE( m_instance->childGameObject(0)->name(), QString("Node Object") );
    QCOMPARE( m_instance->childGameObject(0)->childCount(), 0 );
}

void PrefabTest::testRemoveApply()
{
    m_instance->removeChild( m_instance->childGameObject(0) );

    m_instance->storeChanges();

    GameObject* gameObject = m_prefab->gameObject();
    QCOMPARE( gameObject->childCount(), 0 );
    QCOMPARE( m_instance->childCount(), 0 );
}

void PrefabTest::testAddRevert()
{
    GameObject* child = m_instance->childGameObject(0);
    GameObject* newChild1 = new GameObject();
    newChild1->setName( "New Child 1" );
    child->addChild( newChild1 );
    GameObject* newChild2 = new GameObject();
    newChild2->setName( "New Child 2" );
    m_instance->addChild( newChild2 );

    m_instance->revertChanges();

    GameObject* gameObject = m_prefab->gameObject();
    QCOMPARE( gameObject->childCount(), 1 );
    QCOMPARE( gameObject->childGameObject(0)->childCount(), 0 );

    QCOMPARE( m_instance->childCount(), 1 );
    QCOMPARE( m_instance->childGameObject(0)->childCount(), 0 );
}

void PrefabTest::testAddApply()
{
    GameObject* child = m_instance->childGameObject(0);
    GameObject* newChild1 = new GameObject();
    newChild1->setName( "New Child 1" );
    child->addChild( newChild1 );
    GameObject* newChild2 = new GameObject();
    newChild2->setName( "New Child 2" );
    m_instance->addChild( newChild2 );

    m_instance->storeChanges();

    GameObject* gameObject = m_prefab->gameObject();
    QCOMPARE( gameObject->childCount(), 2 );
    QCOMPARE( gameObject->childGameObject(1)->name(), QString("New Child 2") );
    QCOMPARE( gameObject->childGameObject(0)->childCount(), 1 );
    QCOMPARE( gameObject->childGameObject(0)->childGameObject(0)->name(), QString("New Child 1") );

    QCOMPARE( m_instance->childCount(), 2 );
    QCOMPARE( m_instance->childGameObject(1)->name(), QString("New Child 2") );
    QCOMPARE( m_instance->childGameObject(0)->childCount(), 1 );
    QCOMPARE( m_instance->childGameObject(0)->childGameObject(0)->name(), QString("New Child 1") );
}

void PrefabTest::testInstances()
{
    PrefabInstance* instance = m_prefab->createInstance( m_parent );
    QCOMPARE( m_parent->childCount(), 2 );
    QCOMPARE( instance->prefabLink(), m_prefab );
    QCOMPARE( m_prefab->instances().count(), 2 );
    QCOMPARE( m_instance->parent(), instance->parent() );
    QVERIFY( m_instance->name() != instance->name() );
    QCOMPARE( instance->childCount(), 1 );
    QCOMPARE( instance->childGameObject(0)->name(), QString("Node Object") );
    QCOMPARE( instance->childGameObject(0)->childCount(), 0 );

    m_instance->setPosition( 10, 10, 10 );
    m_instance->storeChanges();
    instance->setScale( 15, 15, 16 );
    instance->storeChanges();

    QCOMPARE( m_instance->position(), QVector3D( 10, 10, 10 ) );
    QCOMPARE( instance->position(), QVector3D( 10, 10, 10 ) );
    QCOMPARE( m_instance->scale(), QVector3D( 15, 15, 16 ) );
}

void PrefabTest::testRevertChild()
{
    PrefabInstanceChild* child = qobject_cast<PrefabInstanceChild*>( m_instance->child(0) );
    QVERIFY( child );
    child->addChild( new GameObject() );
    QCOMPARE( child->children().count(), 1 );
    child->setPosition( QVector3D(12, 13, 14) );

    child->revertChanges();

    QCOMPARE( child->children().count(), 0 );
    QCOMPARE( child->position(), QVector3D(0,0,0) );
}

void PrefabTest::testApplyChild()
{
    PrefabInstance* secondInstance = m_prefab->createInstance();
    PrefabInstanceChild* secondInstanceChild = qobject_cast<PrefabInstanceChild*>( secondInstance->child(0) );

    PrefabInstanceChild* child = qobject_cast<PrefabInstanceChild*>( m_instance->child(0) );
    QVERIFY( child );
    child->addChild( new GameObject() );
    QCOMPARE( child->children().count(), 1 );
    child->setPosition( QVector3D(12, 13, 14) );

    child->storeChanges();

    QCOMPARE( secondInstanceChild->position(), QVector3D(12,13,14) );
    QCOMPARE( secondInstanceChild->children().count(), 1 );
}

QTEST_MAIN( PrefabTest )

 

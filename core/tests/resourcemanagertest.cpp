/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "resourcemanagertest.h"

#include <QtTest>

#include <core/gluonobject.h>
#include <core/resourcemanager.h>

using namespace GluonCore;

QTEST_MAIN( ResourceManagerTest );

#define CHECK_COUNT( count ) \
    QCOMPARE( ResourceManager::instance()->m_resources.size(), (count) )

#define CHECK_CONTAINS( id, obj ) \
    QVERIFY( ResourceManager::instance()->m_resources.contains( (id) ) );\
    QCOMPARE( ResourceManager::instance()->m_resources.value( (id) ), (obj) );

GluonObject* ResourceManagerTest::createObject( const QString& name, QString* internalIdentifier = nullptr )
{
    GluonObject* object = new GluonObject( name );
    if( internalIdentifier )
        *internalIdentifier = ResourceManager::internalID< GluonObject >( name );

    return object;
}

void ResourceManagerTest::initTestCase()
{
    //Ensure the resource manager has been instantiated before accessing private
    //members.
    ResourceManager::instance();
}

void ResourceManagerTest::cleanup()
{
    //Empty the hash of resources after every test so we do not need to handle
    //this in the test.
    qDeleteAll(ResourceManager::instance()->m_resources);
    ResourceManager::instance()->m_resources.clear();
}

void ResourceManagerTest::testAdd()
{
    QString internalId1;
    GluonObject* object1 = createObject( "Test1", &internalId1 );

    //Default state is empty
    CHECK_COUNT( 0 );

    //Adding one object should put it into the hash
    ResourceManager::instance()->addResource< GluonObject >( "Test1", object1 );
    CHECK_COUNT( 1 );
    CHECK_CONTAINS( internalId1, object1 );

    //Adding the same object with the same identifier should do nothing
    ResourceManager::instance()->addResource< GluonObject >( "Test1", object1 );
    CHECK_COUNT( 1 );
    CHECK_CONTAINS( internalId1, object1 );

    //Adding the same object with a different identifier should do nothing
    ResourceManager::instance()->addResource< GluonObject >( "Test2", object1 );
    CHECK_COUNT( 1 );
    CHECK_CONTAINS( internalId1, object1 );

    QString internalId2;
    GluonObject* object2 = createObject( "Test2", &internalId2 );

    //Adding a second object should add it normally
    ResourceManager::instance()->addResource< GluonObject >( "Test2", object2 );
    CHECK_COUNT( 2 );
    CHECK_CONTAINS( internalId2, object2 );

    //Adding a second object should not affect the first object
    CHECK_CONTAINS( internalId1, object1 );

    //This should fail at compile time:
    //ResourceManager::instance()->addResource< void >( "Test3", (void*)0 );
}

void ResourceManagerTest::testGet()
{
    GluonObject* object1 = createObject( "Test1" );
    ResourceManager::instance()->addResource< GluonObject >( "Test1", object1 );

    //Get should return the specified object
    QCOMPARE( ResourceManager::instance()->resource< GluonObject >( "Test1" ), object1 );

    GluonObject* object2 = createObject( "Test2" );
    ResourceManager::instance()->addResource< GluonObject >( "Test2", object2 );

    //Adding a second object should not affect a get for the first
    QCOMPARE( ResourceManager::instance()->resource< GluonObject >( "Test2" ), object2 );
    QCOMPARE( ResourceManager::instance()->resource< GluonObject >( "Test1" ), object1 );
}

void ResourceManagerTest::testRemove()
{
    QString internalId1;
    GluonObject* object1 = createObject( "Test1", &internalId1 );
    ResourceManager::instance()->addResource< GluonObject >( "Test1", object1 );

    ResourceManager::instance()->removeResource< GluonObject >( "Test1" );

    //Removing the single contained item should result in an empty hash
    CHECK_COUNT( 0 );
    QVERIFY( !ResourceManager::instance()->m_resources.contains( internalId1 ) );

    ResourceManager::instance()->addResource< GluonObject >( "Test1", object1 );
    ResourceManager::instance()->removeResource( object1 );

    //Removing through the QObject overload should have the same effect
    CHECK_COUNT( 0 );
    QVERIFY( !ResourceManager::instance()->m_resources.contains( internalId1 ) );

    ResourceManager::instance()->addResource< GluonObject >( "Test1", object1 );

    QString internalId2;
    GluonObject* object2 = createObject( "Test2", &internalId2 );
    ResourceManager::instance()->addResource< GluonObject >( "Test2", object2 );

    ResourceManager::instance()->removeResource< GluonObject >( "Test2" );

    //Removing one resource should have no effect on the other resource
    CHECK_COUNT( 1 );
    QVERIFY( !ResourceManager::instance()->m_resources.contains( internalId2 ) );
    CHECK_CONTAINS( internalId1, object1 );
}

void ResourceManagerTest::testCreate()
{
    GluonObject* object1 = ResourceManager::instance()->createResource< GluonObject >( "Test1" );
    QString internalId1 = ResourceManager::internalID< GluonObject >( "Test1" );

    QVERIFY( object1 );
    CHECK_COUNT( 1 );
    CHECK_CONTAINS( internalId1, object1 );

    //Trying to create an existing object should return the existing object
    QCOMPARE( ResourceManager::instance()->createResource< GluonObject >( "Test1" ), object1 );

    GluonObject* object2 = ResourceManager::instance()->createResource< GluonObject >( "Test2" );
    QString internalId2 = ResourceManager::internalID< GluonObject >( "Test2" );

    //Creating a second object should work the same
    //and have no effect on the first.
    QVERIFY( object2 );
    CHECK_COUNT( 2 );
    CHECK_CONTAINS( internalId2, object2 );
    CHECK_CONTAINS( internalId1, object1 );
}

void ResourceManagerTest::testDestroy()
{
    QString internalId1;
    QPointer< GluonObject > object1 = createObject( "Test1", &internalId1 );

    ResourceManager::instance()->addResource< GluonObject >( "Test1", object1.data() );

    ResourceManager::instance()->destroyResource< GluonObject >( "Test1" );

    CHECK_COUNT( 0 );
    QVERIFY( !ResourceManager::instance()->m_resources.contains( internalId1 ) );
    QVERIFY( object1.isNull() );
}

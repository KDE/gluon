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

#include "gdlhandlertest.h"

#include <core/gdlhandler.h>
#include <core/gluonobject.h>

#include <QtTest/QtTest>
#include <QtCore/QMetaProperty>

#define SANITY_CHECK_POINTERS(a, b) if((a) == NULL || (b) == NULL) return (a) == NULL && (b) == NULL

static bool compare_metaproperties( const QObject* gluonObject1,const QObject* gluonObject2 )
{
    SANITY_CHECK_POINTERS( gluonObject1, gluonObject2 );
    const QMetaObject* metaObject1 = gluonObject1->metaObject();
    const QMetaObject* metaObject2 = gluonObject2->metaObject();

    if( metaObject1->className() != metaObject2->className() )
        return false;

    if( metaObject1->propertyCount() != metaObject2->propertyCount() )
        return false;

    for( int i = 0; i < metaObject1->propertyCount(); ++i )
    {
        QMetaProperty metaProterty1 = metaObject1->property( i );
        QMetaProperty metaProterty2 = metaObject2->property( i );

        if( metaProterty1.type() != metaProterty2.type() )
            return false;

        if( metaProterty1.name() != metaProterty2.name() )
            return false;

        if( metaProterty1.read( gluonObject1 ).toString() != metaProterty2.read( gluonObject2 ).toString() )
            return false;
    }

    return true;
}

static bool compare_dynproperties( const GluonObject* gluonObject1, const GluonObject* gluonObject2 )
{
    SANITY_CHECK_POINTERS( gluonObject1, gluonObject2 );

    const QList<QByteArray> nameList1 = gluonObject1->dynamicPropertyNames();
    const QList<QByteArray> nameList2 = gluonObject2->dynamicPropertyNames();

    if( nameList1.size() != nameList2.size() )
        return false;

    for( int i = 0; i < nameList1.size(); ++i )
    {
        if( nameList1.at(i) != nameList2.at(i) )
            return false;
    }
    return true;
}

static bool compare_objects( const GluonObject* gluonObject1, const GluonObject* gluonObject2 )
{
    SANITY_CHECK_POINTERS( gluonObject1, gluonObject2 );

    if( compare_metaproperties( gluonObject1, gluonObject2 ) == false )
        return false;

    if( compare_dynproperties( gluonObject1, gluonObject2 ) == false )
        return false;

    return true;
}

GDLHandlerTest::GDLHandlerTest( QObject* parent )
    : QObject(parent)
{
}

GDLHandlerTest::~GDLHandlerTest()
{
}

QList<GluonObject*> GDLHandlerTest::gluonObjectList( const QObjectList& objectList)
{
    QList<GluonObject*> gluonObject;
    foreach (QObject * qObject, objectList )
        gluonObject.append( qobject_cast<GluonObject*>( qObject ) );

    return gluonObject;
}

bool GDLHandlerTest::compareTrees( const QList<GluonObject*>& gluonObjectList1, const QList<GluonObject*>& gluonObjectList2 )
{
    if( gluonObjectList1.size() != gluonObjectList2.size() )
        return false;

    for( int i = 0 ; i < gluonObjectList1.size(); ++i )
    {
        QList<GluonObject*> children1 = gluonObjectList( gluonObjectList1.at(i)->children() );
        QList<GluonObject*> children2 = gluonObjectList( gluonObjectList2.at(i)->children() );

        if( compare_objects( gluonObjectList1.at(i), gluonObjectList2.at(i) ) == false )
            return false;

        if( compareTrees( children1, children2 ) == false )
            return false;
    }

    return true;
}

template <typename T> QList<const T*> GDLHandlerTest::constListFromNonConst( const QList<T*>& nonConstTemplateList )
{
    QList<const T*> constTemplateList;

    foreach( T * templateObject, nonConstTemplateList )
        constTemplateList.append( templateObject );

    return constTemplateList;
}

bool GDLHandlerTest::ensureReversible( const QString& gdl )
{
    GDLHandler* gh = GDLHandler::instance();
    QList<GluonObject*> parsedGluonObjectList = gh->parseGDL( gdl, gdl.size() );
    QString serializedString = gh->serializeGDL( constListFromNonConst( parsedGluonObjectList ) );
    bool result = compareTrees( parsedGluonObjectList, gh->parseGDL( serializedString, serializedString.size() ) );
    qDeleteAll(parsedGluonObjectList);
    return result;
}

bool GDLHandlerTest::ensureParsing(const QList<GluonCore::GluonObject *>& gluonObjectList, const QString& gdl)
{
    GDLHandler* gh = GDLHandler::instance();
    QList<GluonObject*> parsedGluonObjectList = gh->parseGDL( gdl, gdl.size() );
    bool result = compareTrees( parsedGluonObjectList, gluonObjectList);
    qDeleteAll(parsedGluonObjectList);
    return result;
}

bool GDLHandlerTest::ensureSerializing(const QList<GluonCore::GluonObject *>& gluonObjectList, const QString& gdl)
{
    GDLHandler* gh = GDLHandler::instance();
    QString serializedString = gh->serializeGDL( constListFromNonConst( gluonObjectList ) );

    if ( serializedString != gdl )
        return false;

    return true;
}

bool GDLHandlerTest::ensureCommenting(const QList<GluonCore::GluonObject *>& gluonObjectList, const QString& gdl)
{
    if( ensureParsing( gluonObjectList, gdl ) == false )
        return false;

    if( ensureSerializing( gluonObjectList, gdl ) == true )
        return false;

    if( ensureReversible( gdl ) == false )
        return false;

    return true;
}

void GDLHandlerTest::testGDLSample()
{
    QString test =
        "{ GluonCore::GluonObject(ParentObjectName)\n"
        "    status bool(true)\n"
        "    { GluonCore::GluonObject(ChildObjectName)\n"
        "    }\n"
        "}";

    QList<GluonObject*> gluonObjectList ;
    GluonObject parentObject( "ParentObjectName" );
    GluonObject childObject( "ChildObjectName" );

    parentObject.addChild(&childObject);
    parentObject.setPropertyFromString( "status", "bool(true)");
    gluonObjectList.append( &parentObject );

    QVERIFY( ensureParsing( gluonObjectList, test ) == true );
    QVERIFY( ensureSerializing( gluonObjectList, test ) == true );
}

void GDLHandlerTest::testCommentAtBegin()
{
    QString test =
        "{ GluonCore::GluonObject(GluonObjectName)\n"
        "status bool(true)\n"
        "# This is a comment\n"
        "number int(5)"
        "}";

    QList<GluonObject*> gluonObjectList ;
    GluonObject gluonObject( "GluonObjectName" );
    gluonObject.setPropertyFromString( "status", "bool(true)");
    gluonObject.setPropertyFromString( "number", "int(5)");
    gluonObjectList.append( &gluonObject );

    QVERIFY( ensureCommenting( gluonObjectList, test ) == true );
}

void GDLHandlerTest::testCommentAtEnd()
{
    QString test =
        "{ GluonCore::GluonObject(GluonObjectName)\n"
        "number int(5) # This is a comment\n"
        "status bool(true)\n"
        "}";

    QList<GluonObject*> gluonObjectList ;
    GluonObject gluonObject( "GluonObjectName" );
    gluonObject.setPropertyFromString( "number", "int(5)");
    gluonObject.setPropertyFromString( "status", "bool(true)");
    gluonObjectList.append( &gluonObject );

    QVERIFY( ensureCommenting( gluonObjectList, test ) == true );
}

void GDLHandlerTest::testDoxygenSample()
{
    QString test =
        "{ GluonCore::GluonObject(GluonObject1)\n"
        // "reference GluonCore::GluonObject(GluonObject2.ChildObject)\n"
        "}\n"
        "{ GluonCore::GluonObject(GluonObject2)\n"
        "{ GluonCore::GluonObject(ChildObject)\n"
        "}\n"
        "}";

    QVERIFY( ensureReversible( test ) == true );
}

void GDLHandlerTest::testInvadersSample()
{
    QString test =
        "{ GluonEngine::GameObject(Game)\n"
        "    enabled bool(true)\n"
        "    position vector3d(0;0;0)\n"
        "    scale vector3d(1;1;1)\n"
        "    orientation quaternion(0;0;0;1)\n"
        "    { GluonEngine::GameObject(Camera)\n"
        "        enabled bool(true)\n"
        "        position vector3d(0;0;50)\n"
        "        scale vector3d(1;1;1)\n"
        "        orientation quaternion(0;0;0;1)\n"
        "        { GluonEngine::CameraControllerComponent(GluonObject)\n"
        "            enabled bool(true)\n"
        "            active bool(true)\n"
        "            visibleArea size2d(90;90)\n"
        "            nearPlane float(1)\n"
        "            farPlane float(99.99)\n"
        "        }\n"
        "        { GluonEngine::SoundListenerComponent(GluonObject 1)\n"
        "            enabled bool(true)\n"
        "            active bool(true)\n"
        "            effectsEnabled bool(true)\n"
        "        }\n"
        "        { GluonEngine::SoundEmitterComponent(GluonObject 2)\n"
        "            enabled bool(true)\n"
        "#            sound GluonEngine::Asset(Invaders/Assets/Sounds/Harmful or Fatal.ogg)\n"
        "            radius float(99.99)\n"
        "            volume float(1)\n"
        "            pitch float(1)\n"
        "            loop bool(true)\n"
        "            autoPlay bool(true)\n"
        "        }\n"
        "    }\n"
        "    { GluonEngine::GameObject(Background)\n"
        "        enabled bool(true)\n"
        "        position vector3d(0;0;0)\n"
        "        scale vector3d(1;1;1)\n"
        "        orientation quaternion(0;0;0;1)\n"
        "        { GluonEngine::SpriteRendererComponent(GluonObject)\n"
        "            enabled bool(true)\n"
        "            size size2d(90;90)\n"
        "#            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Background)\n"
        "            color rgba(255;255;255;255)\n"
        "        }\n"
        "        { GluonEngine::QtScriptComponent(ControllerScript)\n"
        "            enabled bool(true)\n"
        "#            script GluonEngine::Asset(Invaders/Assets/Scripts/controller.js)\n"
        "            paused bool(false)\n"
        "        }\n"
        "        { GluonEngine::KeyboardInputComponent(Continue)\n"
        "            enabled bool(true)\n"
        "            keyCode int(57)\n"
        "        }\n"
        "    }\n"
        "    { GluonEngine::GameObject(Player)\n"
        "        enabled bool(false)\n"
        "        position vector3d(100;0;1)\n"
        "        scale vector3d(1;1;1)\n"
        "        orientation quaternion(0;0;0;1)\n"
        "        { GluonEngine::SpriteRendererComponent(SpriteRenderer)\n"
        "            enabled bool(true)\n"
        "            size size2d(8;8)\n"
        "#            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Player)\n"
        "            color rgba(255;255;255;255)\n"
        "        }\n"
        "        { GluonEngine::GameObject(Reflection)\n"
        "            enabled bool(true)\n"
        "            position vector3d(0;-12;0)\n"
        "            scale vector3d(1;1;1)\n"
        "            orientation quaternion(0;0;0;1)\n"
        "            { GluonEngine::SpriteRendererComponent(GluonObject)\n"
        "                enabled bool(true)\n"
        "                size size2d(8;8)\n"
        "#                material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Player Reflection)\n"
        "                color rgba(255;255;255;255)\n"
        "            }\n"
        "        }\n"
        "        { GluonEngine::QtScriptComponent(GluonObject 1)\n"
        "            enabled bool(true)\n"
        "#            script GluonEngine::Asset(Invaders/Assets/Scripts/player.js)\n"
        "        }\n"
        "        { GluonEngine::KeyboardInputComponent(Key_Left)\n"
        "            enabled bool(true)\n"
        "            keyCode int(105)\n"
        "        }\n"
        "        { GluonEngine::KeyboardInputComponent(Key_Right)\n"
        "            enabled bool(true)\n"
        "            keyCode int(106)\n"
        "        }\n"
        "        { GluonEngine::KeyboardInputComponent(Key_Up)\n"
        "            enabled bool(true)\n"
        "            keyCode int(21)\n"
        "        }\n"
        "        { GluonEngine::KeyboardInputComponent(Key_Down)\n"
        "            enabled bool(true)\n"
        "            keyCode int(31)\n"
        "        }\n"
        "        { GluonEngine::KeyboardInputComponent(Key_Fire)\n"
        "            enabled bool(true)\n"
        "            keyCode int(57)\n"
        "        }\n"
        "        { GluonEngine::SoundEmitterComponent(FireSound)\n"
        "            enabled bool(true)\n"
        "#            sound GluonEngine::Asset(Invaders/Assets/Sounds/laser-pew.ogg)\n"
        "            radius float(99.99)\n"
        "            volume float(1)\n"
        "            pitch float(1)\n"
        "            loop bool(false)\n"
        "            autoPlay bool(false)\n"
        "        }\n"
        "        { GluonEngine::SphereCollisionComponent(BulletCollider)\n"
        "            enabled bool(true)\n"
        "            collisionGroup int(2)\n"
        "            radius float(3)\n"
        "        }\n"
        "        { GluonEngine::SoundEmitterComponent(Kapow)\n"
        "            enabled bool(true)\n"
        "#            sound GluonEngine::Asset(Invaders/Assets/Sounds/quiet-explosion.ogg)\n"
        "            radius float(99.99)\n"
        "            volume float(1)\n"
        "            pitch float(1)\n"
        "            loop bool(false)\n"
        "            autoPlay bool(false)\n"
        "        }\n"
        "        { GluonEngine::SphereCollisionComponent(EnemyCollider)\n"
        "            enabled bool(true)\n"
        "            radius float(3)\n"
        "        }\n"
        "    }\n"
        "    { GluonEngine::GameObject(Enemy)\n"
        "        enabled bool(false)\n"
        "        position vector3d(100;0;1)\n"
        "        scale vector3d(1;1;1)\n"
        "        orientation quaternion(0;0;0;1)\n"
        "        { GluonEngine::SpriteRendererComponent(SpriteRenderer)\n"
        "            enabled bool(true)\n"
        "            size size2d(5;5)\n"
        "#            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Enemy)\n"
        "            color rgba(255;255;255;255)\n"
        "        }\n"
        "        { GluonEngine::QtScriptComponent(GluonObject 1)\n"
        "            enabled bool(true)\n"
        "#            script GluonEngine::Asset(Invaders/Assets/Scripts/enemy.js)\n"
        "        }\n"
        "        { GluonEngine::SphereCollisionComponent(PlayerCollider)\n"
        "            enabled bool(true)\n"
        "            radius float(2)\n"
        "        }\n"
        "        { GluonEngine::SphereCollisionComponent(BulletCollider)\n"
        "            enabled bool(true)\n"
        "            collisionGroup int(1)\n"
        "            radius float(2)\n"
        "        }\n"
        "        { GluonEngine::SoundEmitterComponent(Kapow)\n"
        "            enabled bool(true)\n"
        "#            sound GluonEngine::Asset(Invaders/Assets/Sounds/quiet-explosion.ogg)\n"
        "            radius float(99.99)\n"
        "            volume float(1)\n"
        "            pitch float(1)\n"
        "            loop bool(false)\n"
        "            autoPlay bool(false)\n"
        "        }\n"
        "    }\n"
        "    { GluonEngine::GameObject(Bullet)\n"
        "        enabled bool(false)\n"
        "        position vector3d(100;0;2)\n"
        "        scale vector3d(1;1;1)\n"
        "        orientation quaternion(0;0;0;1)\n"
        "        { GluonEngine::SpriteRendererComponent(GluonObject)\n"
        "            enabled bool(true)\n"
        "            size size2d(1;5)\n"
        "#            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Bullet)\n"
        "            color rgba(255;0;0;255)\n"
        "        }\n"
        "        { GluonEngine::QtScriptComponent(Script)\n"
        "            enabled bool(true)\n"
        "#            script GluonEngine::Asset(Invaders/Assets/Scripts/bullet.js)\n"
        "        }\n"
        "        { GluonEngine::SphereCollisionComponent(Collider)\n"
        "            enabled bool(true)\n"
        "            collisionGroup int(1)\n"
        "            radius float(2)\n"
        "        }\n"
        "        { GluonEngine::SoundEmitterComponent(Pew)\n"
        "            enabled bool(true)\n"
        "#            sound GluonEngine::Asset(Invaders/Assets/Sounds/laser-pew.ogg)\n"
        "            radius float(99.99)\n"
        "            volume float(1)\n"
        "            pitch float(1)\n"
        "            loop bool(false)\n"
        "            autoPlay bool(true)\n"
        "        }\n"
        "    }\n"
        "    { GluonEngine::GameObject(GameOver)\n"
        "        enabled bool(true)\n"
        "        position vector3d(0;50;10)\n"
        "        scale vector3d(1;1;1)\n"
        "        orientation quaternion(0;0;0;1)\n"
        "        { GluonEngine::SpriteRendererComponent(GluonObject)\n"
        "            enabled bool(true)\n"
        "            size size2d(40;7)\n"
        "#            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Game Over)\n"
        "            color rgba(255;255;255;255)\n"
        "        }\n"
        "    }\n"
        "    { GluonEngine::GameObject(GameWon)\n"
        "        enabled bool(true)\n"
        "        position vector3d(0;50;10)\n"
        "        scale vector3d(1;1;1)\n"
        "        orientation quaternion(0;0;0;1)\n"
        "        { GluonEngine::SpriteRendererComponent(GluonObject)\n"
        "            enabled bool(true)\n"
        "            size size2d(40;9)\n"
        "#            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/You Win)\n"
        "            color rgba(255;255;255;255)\n"
        "        }\n"
        "    }\n"
        "}";

    QVERIFY( ensureReversible( test ) == true );
}

QTEST_MAIN(GDLHandlerTest)

 

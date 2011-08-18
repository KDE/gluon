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

using namespace GluonCore;

#define SANITY_CHECK_POINTERS(a, b) if((a) == NULL || (b) == NULL) return (a) == NULL && (b) == NULL

static bool compare_metaproperties( const QMetaObject* a, const QObject* a_parent, const QMetaObject* b, const QObject* b_parent )
{
    SANITY_CHECK_POINTERS( a, b );

    if( a->className() != b->className() )
        return false;

    int a_propcount = a->propertyCount(),
        b_propcount = b->propertyCount();

    if( a_propcount != b_propcount )
        return false;

    for( int i = 0; i < a_propcount; ++i )
    {
        QMetaProperty am = a->property( i ),
                      bm = b->property( i );

        if( am.type() != bm.type() )
            return false;

        if( am.name() != bm.name() )
            return false;

        if( am.read( a_parent ).toString() != bm.read( b_parent ).toString() )
            return false;
    }

    return true;
}

static bool compare_dynproperties( const GluonObject* a, const GluonObject* b )
{
    typedef QList<QByteArray> PropNameList;

    SANITY_CHECK_POINTERS( a, b );

    const PropNameList a_names = a->dynamicPropertyNames(),
                       b_names = b->dynamicPropertyNames();

    if( a_names.size() != b_names.size() )
        return false;

    for( PropNameList::const_iterator p1 = a_names.begin(), p2 = b_names.begin(), e = a_names.end(); p1 != e; ++p1, ++p2 )
    {
        if( QString( *p1 ) != QString( *p2 ) )
            return false;
    }
    return true;
}

static bool compare_objects( const GluonObject* a, const GluonObject* b )
{
    SANITY_CHECK_POINTERS( a, b );

    if( compare_metaproperties( a->metaObject(), a, b->metaObject(), b ) == false )
        return false;

    if( compare_dynproperties( a, b ) == false )
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

bool GDLHandlerTest::compareTrees( const QList<GluonObject*>& t1, const QList<GluonObject*>& t2 )
{
    if(t1.size() == 0 || t2.size() == 0)
        return false;
    if( t1.size() != t2.size() )
        return false;

    QList<GluonObject*>::const_iterator p1 = t1.begin(),
                                                   p2 = t2.begin(),
                                                   end = t1.end();

    for( ; p1 != end; ++p1, ++p2 )
    {
        Q_ASSERT( p2 != t2.end() );

        if( compare_objects( *p1, *p2 ) == false )
            return false;
    }

    return true;
}


bool GDLHandlerTest::ensureReversible( const QString& gdl )
{
    GDLHandler* gh = GDLHandler::instance();
    QList<GluonObject*> parsed = gh->parseGDL( gdl, gdl.size() );
    QString serializedString = gh->serializeGDL( constListFromNonConst( parsed ) );
    return compareTrees( parsed, gh->parseGDL( serializedString, serializedString.size() ) );
}

bool GDLHandlerTest::ensureParsable(const QList<GluonCore::GluonObject *>& t, const QString& gdl)
{
    GDLHandler* gh = GDLHandler::instance();
    QList<GluonObject*> parsed = gh->parseGDL( gdl, gdl.size() );
    return compareTrees( parsed, t);
}

void GDLHandlerTest::testParseGDL()
{
    QString test =
        "{ GluonCore::GluonObject(AnObject)\n"
        "    status bool(true)\n"
        "{ GluonCore::GluonObject(AChildObject)\n"
        "}\n"
        "}"
        ;
    QList<GluonObject*> objectList ;
    GluonObject parentObject( "AnObject" );
    GluonObject childObject( "AChildObject" );

    parentObject.addChild(&childObject);
    parentObject.setPropertyFromString( "status", "bool(true)");
    objectList.append( &parentObject );
    QVERIFY( ensureParsable( objectList, test ) );
}

void GDLHandlerTest::testDoxygenSample()
{
    QString test =
        "{ GluonCore::GluonObject(AnotherObject)\n"
        // "reference GluonCore::GluonObject(AnObject.AChildObject)\n"
        "}\n"
        "{ GluonCore::GluonObject(AnObject)\n"
        "{ GluonCore::GluonObject(AChildObject)\n"
        "}\n"
        "}"
        ;

    QVERIFY( ensureReversible( test ) );
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
        "            sound GluonEngine::Asset(Invaders/Assets/Sounds/Harmful or Fatal.ogg)\n"
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
        "            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Background)\n"
        "            color rgba(255;255;255;255)\n"
        "        }\n"
        "        { GluonEngine::QtScriptComponent(ControllerScript)\n"
        "            enabled bool(true)\n"
        "            script GluonEngine::Asset(Invaders/Assets/Scripts/controller.js)\n"
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
        "            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Player)\n"
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
        "                material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Player Reflection)\n"
        "                color rgba(255;255;255;255)\n"
        "            }\n"
        "        }\n"
        "        { GluonEngine::QtScriptComponent(GluonObject 1)\n"
        "            enabled bool(true)\n"
        "            script GluonEngine::Asset(Invaders/Assets/Scripts/player.js)\n"
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
        "            sound GluonEngine::Asset(Invaders/Assets/Sounds/laser-pew.ogg)\n"
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
        "            sound GluonEngine::Asset(Invaders/Assets/Sounds/quiet-explosion.ogg)\n"
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
        "            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Enemy)\n"
        "            color rgba(255;255;255;255)\n"
        "        }\n"
        "        { GluonEngine::QtScriptComponent(GluonObject 1)\n"
        "            enabled bool(true)\n"
        "            script GluonEngine::Asset(Invaders/Assets/Scripts/enemy.js)\n"
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
        "            sound GluonEngine::Asset(Invaders/Assets/Sounds/quiet-explosion.ogg)\n"
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
        "            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Bullet)\n"
        "            color rgba(255;0;0;255)\n"
        "        }\n"
        "        { GluonEngine::QtScriptComponent(Script)\n"
        "            enabled bool(true)\n"
        "            script GluonEngine::Asset(Invaders/Assets/Scripts/bullet.js)\n"
        "        }\n"
        "        { GluonEngine::SphereCollisionComponent(Collider)\n"
        "            enabled bool(true)\n"
        "            collisionGroup int(1)\n"
        "            radius float(2)\n"
        "        }\n"
        "        { GluonEngine::SoundEmitterComponent(Pew)\n"
        "            enabled bool(true)\n"
        "            sound GluonEngine::Asset(Invaders/Assets/Sounds/laser-pew.ogg)\n"
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
        "            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/Game Over)\n"
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
        "            material GluonGraphics::MaterialInstance(Invaders/Assets/Material/You Win)\n"
        "            color rgba(255;255;255;255)\n"
        "        }\n"
        "    }\n"
        "}";

    QVERIFY( ensureReversible( test ) );
}

QTEST_MAIN(GDLHandlerTest)

#include "gdlhandlertest.moc"

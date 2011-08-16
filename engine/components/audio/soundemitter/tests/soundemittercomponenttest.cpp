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

#include "soundemittercomponenttest.h"

#include <engine/gameobject.h>
#include <engine/components/audio/soundemitter/soundemittercomponent.h>

#include <QtTest/QtTest>

using namespace GluonEngine;

SoundEmitterComponentTest::SoundEmitterComponentTest()
{
}

SoundEmitterComponentTest::~SoundEmitterComponentTest()
{
}

void SoundEmitterComponentTest::testCategory()
{
    SoundEmitterComponent soundEmitterComponent;
    QVERIFY(soundEmitterComponent.category() == "Audio");
}

void SoundEmitterComponentTest::testAsset()
{
}

void SoundEmitterComponentTest::testInitialize()
{
}

void SoundEmitterComponentTest::testStart()
{
}

void SoundEmitterComponentTest::testDraw()
{
}

void SoundEmitterComponentTest::testStop()
{
}

void SoundEmitterComponentTest::testCleanup()
{
}

void SoundEmitterComponentTest::testRadius()
{
    SoundEmitterComponent soundEmitterComponent;
    float radius = 1.0;
    soundEmitterComponent.setRadius(radius);
    QCOMPARE(soundEmitterComponent.radius(), radius);
}

void SoundEmitterComponentTest::testVolume()
{
    SoundEmitterComponent soundEmitterComponent;
    float volume = 1.0;
    soundEmitterComponent.setVolume(volume);
    QCOMPARE(soundEmitterComponent.volume(), volume);
}

void SoundEmitterComponentTest::testPitch()
{
    SoundEmitterComponent soundEmitterComponent;
    float pitch = 1.0;
    soundEmitterComponent.setPitch(pitch);
    QCOMPARE(soundEmitterComponent.pitch(), pitch);
}

void SoundEmitterComponentTest::testIsPlaying()
{
}

void SoundEmitterComponentTest::testIsLooping()
{
    SoundEmitterComponent soundEmitterComponent;
    bool isLooping = true;
    soundEmitterComponent.setLoop(isLooping);
    QCOMPARE(soundEmitterComponent.isLooping(), isLooping);
}

void SoundEmitterComponentTest::testPopulateMetaInfo()
{
}

QTEST_MAIN(SoundEmitterComponentTest)

#include "soundemittercomponenttest.moc"

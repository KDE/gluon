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

#include "soundtest.h"

#include <audio/sound.h>

#include <core/directoryprovider.h>

#include <QtTest/QtTest>

using namespace GluonAudio;

SoundTest::SoundTest()
{
}

SoundTest::~SoundTest()
{
}

void SoundTest::testConstructorMemberInit()
{
    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    Sound sound(this);
    QCOMPARE(sound.isValid(), false);
    QCOMPARE(sound.isPlaying(), false);
    QCOMPARE(sound.isLooping(), false);
    QCOMPARE(sound.pitch(), 1.0f);
    QCOMPARE(sound.radius(), 10000.0f);
    QCOMPARE(sound.duration(), 0.0);
}

void SoundTest::testLoad()
{
    Sound sound(this);
    QCOMPARE(sound.isValid(), false);

    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    sound.load(shareInstallDir + "/gluon/audio/sounds/Front_Left.wav");

    QCOMPARE(sound.isValid(), true);
}

void SoundTest::testLoadInvalidSource()
{
    Sound sound(this);
    QCOMPARE(sound.isValid(), false);
    QCOMPARE(sound.load("non.existing.file"), false);
    QCOMPARE(sound.isValid(), false);
}

void SoundTest::testIsValid()
{
    Sound sound(this);
    QCOMPARE(sound.isValid(), false);

    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    sound.load(shareInstallDir + "/gluon/audio/sounds/Front_Left.wav");

    QCOMPARE(sound.isValid(), true);
}

void SoundTest::testIsPlaying()
{
    Sound sound(this);
    QCOMPARE(sound.isPlaying(), false);
    QCOMPARE(sound.isValid(), false);

    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    sound.load(shareInstallDir + "/gluon/audio/sounds/Front_Left.wav");

    QCOMPARE(sound.isPlaying(), false);
    QCOMPARE(sound.isValid(), true);

    sound.play();
    QCOMPARE(sound.isPlaying(), true);
    sound.stop();
}

void SoundTest::testIsLooping()
{
    Sound sound(this);
    QCOMPARE(sound.isValid(), false);
    QCOMPARE(sound.isLooping(), false);

    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    sound.load(shareInstallDir + "/gluon/audio/sounds/Front_Left.wav");

    QCOMPARE(sound.isValid(), true);

    sound.setLoop(true);
    QCOMPARE(sound.isLooping(), true);

    sound.setLoop(false);
    QCOMPARE(sound.isLooping(), false);
}

void SoundTest::testPosition()
{
    Sound sound(this);
    QCOMPARE(sound.isValid(), false);

    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    sound.load(shareInstallDir + "/gluon/audio/sounds/Front_Left.wav");

    QVector3D vector3D(1.0, 2.0, 3.0);
    sound.setPosition(vector3D);
    QCOMPARE(sound.position(), vector3D);
}

void SoundTest::testVolume()
{
    Sound sound(this);
    QCOMPARE(sound.isValid(), false);
    QCOMPARE(sound.isLooping(), false);

    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    sound.load(shareInstallDir + "/gluon/audio/sounds/Front_Left.wav");

    QCOMPARE(sound.isValid(), true);

    sound.setVolume(0.9f);
    QCOMPARE(sound.volume(), 0.9f);
}

void SoundTest::testPitch()
{
    Sound sound(this);
    QCOMPARE(sound.isValid(), false);

    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    sound.load(shareInstallDir + "/gluon/audio/sounds/Front_Left.wav");

    QCOMPARE(sound.isValid(), true);

    sound.setPitch(1.5f);
    QCOMPARE(sound.pitch(), 1.5f);
}

void SoundTest::testRadius()
{
    Sound sound(this);
    QCOMPARE(sound.isValid(), false);

    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    sound.load(shareInstallDir + "/gluon/audio/sounds/Front_Left.wav");

    QCOMPARE(sound.isValid(), true);

    sound.setRadius(15000.0f);
    QCOMPARE(sound.radius(), 15000.0f);
}

QTEST_MAIN(SoundTest)

#include "soundtest.moc"

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

#include "enginetest.h"

#include <audio/engine.h>

#include <QtTest/QtTest>

using namespace GluonAudio;

EngineTest::EngineTest()
{
}

EngineTest::~EngineTest()
{
}

void EngineTest::testBufferLength()
{
    Engine *engine = Engine::instance();
    QCOMPARE(engine->bufferLength(), 250000);
    engine->setBufferLength(100000);
    QCOMPARE(engine->bufferLength(), 100000);
}

void EngineTest::testBuffersPerStream()
{
    Engine *engine = Engine::instance();
    QCOMPARE(engine->buffersPerStream(), 3);
    engine->setBuffersPerStream(2);
    QCOMPARE(engine->buffersPerStream(), 2);
}

void EngineTest::testListenerPosition()
{
    Engine *engine = Engine::instance();
    QVector3D vector3D(1.0, 2.0, 3.0);
    engine->setListenerPosition(vector3D);
    QCOMPARE(engine->listenerPosition(), vector3D);
}

QTEST_MAIN(EngineTest)

#include "enginetest.moc"

/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011-2012 Laszlo Papp <lpapp@kde.org>
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
    : m_defaultBufferLength(250000)
    , m_defaultBufferPerStream(3)
{
}

EngineTest::~EngineTest()
{
}

void EngineTest::testBufferLength()
{
    Engine *engine = Engine::instance();
    QCOMPARE(engine->bufferLength(), m_defaultBufferLength);

    int bufferLength = 100000;
    engine->setBufferLength(bufferLength);
    QCOMPARE(engine->bufferLength(), bufferLength);
}

void EngineTest::testBuffersPerStream()
{
    Engine *engine = Engine::instance();
    QCOMPARE(engine->buffersPerStream(), m_defaultBufferPerStream);

    int bufferPerStream = 2;
    engine->setBuffersPerStream(bufferPerStream);
    QCOMPARE(engine->buffersPerStream(), bufferPerStream);
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

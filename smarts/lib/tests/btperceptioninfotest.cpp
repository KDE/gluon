/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Laszlo Papp <lpapp@kde.org>
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

#include "btperceptioninfotest.h"

#include <smarts/lib/btperceptioninfo.h>

#include <QtTest/QtTest>

using namespace GluonSmarts;

class MockBtPerceptionInfo : public btPerceptionInfo
{
    public:
        MockBtPerceptionInfo(QObject* parent)
            : btPerceptionInfo(parent)
        {
        }

        ~MockBtPerceptionInfo()
        {
        }

        QVariant getAdjustedValue( qreal precision ) const
        {
            Q_UNUSED(precision)
            return QVariant();
        }
};

btPerceptionInfoTest::btPerceptionInfoTest()
{
}

btPerceptionInfoTest::~btPerceptionInfoTest()
{
}

void btPerceptionInfoTest::testPosition()
{
    MockBtPerceptionInfo perceptionInfo(this);

    QVector3D vector3D(1.0, 2.0, 3.0);
    perceptionInfo.setPosition(vector3D);
    QCOMPARE(perceptionInfo.position(), vector3D);
}

void btPerceptionInfoTest::testRadius()
{
    MockBtPerceptionInfo perceptionInfo(this);

    qreal radius = 15000.0f;

    perceptionInfo.setRadius(radius);
    QCOMPARE(perceptionInfo.radius(), radius);
}

QTEST_MAIN(btPerceptionInfoTest)

 

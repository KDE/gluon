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

#ifndef GLUON_CORE_GLUONOBJECTTEST_H
#define GLUON_CORE_GLUONOBJECTTEST_H

#include <QtCore/QObject>
#include <core/gluonobject.h>

namespace GluonCore
{
    class TestObject : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( TestObject )

    public:
        explicit TestObject(const QString& name = QString(), QObject* parent = 0);
    };
}
Q_DECLARE_METATYPE( GluonCore::TestObject* )

class GluonObjectTest : public QObject
{
        Q_OBJECT

    public:
        GluonObjectTest();
        virtual ~GluonObjectTest();

    private Q_SLOTS:
        void testAddChild();
        void testAddChildAt();
        void testChildAt();
        void testChildByName();
        void testName();
        void testSupportedMimeTypes();
        void testRemoveChild();
        void testMetaInfo();
        void testHasMetaInfo();
        void testQualifiedName();
        void testFullyQualifiedName();
        void testNameToObjectName();
        void testConvertQVariant();
};

#endif // GLUON_CORE_GLUONOBJECTTEST_Hs

/******************************************************************************
 * This file is part of the Gluon Development Platform
 *
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

#ifndef GLUON_CORE_GDLSERIALIZERTEST_H
#define GLUON_CORE_GDLSERIALIZERTEST_H

#include <QtCore/QObject>

namespace GluonCore
{
    class GluonObject;
}

class GDLSerializerTest : public QObject
{
        Q_OBJECT

    public:
        GDLSerializerTest( QObject* parent = 0 );
        virtual ~GDLSerializerTest();

    private Q_SLOTS:
        void initTestCase();
        void testSingleObjectSingleProperty();
        void testSingleObjectMultiProperty();
        void testObjectTree();
        void testMultiRoot();
        void testMultilineString();
        void testList();

    private:
        QByteArray m_singleObjectSingleProperty;
        QByteArray m_singleObjectMultiProperty;
        QByteArray m_objectTree;
        QByteArray m_multiRoot;
        QByteArray m_multiLineString;
        QByteArray m_list;
};

#endif // GLUON_CORE_GDLSERIALIZERTEST_H

/******************************************************************************
 * This file is part of the Gluon Development Platform
 *
 * Copyright (c) 2010 Clark Gaebel <cg.wowus.cg@gmail.com>
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef TEST_GLUON_CORE_H
#define TEST_GLUON_CORE_H

#include <core/gluonobject.h>
#include <core/gdlhandler.h>

#include <QtTest/QTest>
#include <QtCore/QList>

class TestGluonCore : public QObject
{
        Q_OBJECT

    public:
        explicit TestGluonCore();
        virtual ~TestGluonCore();

    private:
        static bool compareTrees( const QList<GluonCore::GluonObject*>& t1, const QList<GluonCore::GluonObject*>& t2 );

        template <typename T>
        static QList<const T*> constListFromNonConst( const QList<T*>& x )
        {
            QList<const T*> r;

            foreach( T * e, x )
            r.push_back( e );

            return r;
        }

        // Returns true if the passed GDL has (parsed -> serialized -> parsed) == parsed
        static bool ensureReversible( const QString& gdl );

    private slots:
        void doxygenSample();
        void invadersSample();
};

#endif

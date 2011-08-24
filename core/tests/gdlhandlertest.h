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

#ifndef GLUON_CORE_GDLHANDLERTEST_H
#define GLUON_CORE_GDLHANDLERTEST_H

#include <QtCore/QObject>
#include <QtCore/QList>

namespace GluonCore
{
    class GluonObject;
}

class GDLHandlerTest : public QObject
{
        Q_OBJECT

    public:
        GDLHandlerTest( QObject* parent = 0 );
        virtual ~GDLHandlerTest();

    private:
        static bool compareTrees( const QList<GluonCore::GluonObject*>& t1, const QList<GluonCore::GluonObject*>& t2 );
        static bool compareChildren( const GluonCore::GluonObject* a, const GluonCore::GluonObject* b  );

        template <typename T>
        static QList<const T*> constListFromNonConst( const QList<T*>& x )
        {
            QList<const T*> r;

            foreach( T * e, x )
            r.push_back( e );

            return r;
        }

        // Return QList<GluonObject*> by casting QList<QObject*>
        static QList<GluonCore::GluonObject*> gluonObjectList( const QObjectList& objectList)
        {
            QList<GluonCore::GluonObject*> r;
            foreach (QObject * object, objectList )
                r.push_back( qobject_cast<GluonCore::GluonObject*>( object ) );

            return r;
        }

        // Returns true if the passed GDL has (parsed -> serialized -> parsed) == parsed
        static bool ensureReversible( const QString& gdl );
        static bool ensureParsing( const QList<GluonCore::GluonObject*>& t, const QString& gdl);
        static bool ensureSerializing( const QList<GluonCore::GluonObject*>& t, const QString& gdl);

    private Q_SLOTS:
        void testGDLSample();
        void testIgnoreComment();
        void testDoxygenSample();
        void testInvadersSample();
};

#endif // GLUON_CORE_GDLHANDLERTEST_H

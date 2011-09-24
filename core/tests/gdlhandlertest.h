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

using namespace GluonCore;

class GDLHandlerTest : public QObject
{
        Q_OBJECT

    public:
        GDLHandlerTest( QObject* parent = 0 );
        virtual ~GDLHandlerTest();

    private:
        bool compareTrees( const QList<GluonObject*>& gluonObjectList1, const QList<GluonObject*>& gluonObjectList2 );
        template <typename T> QList<const T*> constListFromNonConst( const QList<T*>& x );
        QList<GluonObject*> gluonObjectList( const QObjectList& objectList);

        bool ensureReversible( const QString& gdl );
        bool ensureParsing( const QList<GluonObject*>& gluonObjectList, const QString& gdl);
        bool ensureSerializing( const QList<GluonObject*>& gluonObjectList, const QString& gdl);
        bool ensureCommenting( const QList<GluonObject *>& gluonObjectList, const QString& gdl);

    private Q_SLOTS:
        void testGDLSample();
        void testCommentAtBegin();
        void testCommentAtEnd();
        void testDoxygenSample();
        void testInvadersSample();
};

#endif // GLUON_CORE_GDLHANDLERTEST_H

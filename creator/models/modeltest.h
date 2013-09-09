/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef MODELTEST_H
#define MODELTEST_H

#include <QtCore/QObject>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QStack>

#include <creator/lib/gluoncreator_macros.h>

class GLUONCREATOR_EXPORT ModelTest : public QObject
{
        Q_OBJECT

    public:
        explicit ModelTest( QAbstractItemModel* model, QObject* parent = 0 );

    private Q_SLOTS:
        void nonDestructiveBasicTest();
        void rowCount();
        void columnCount();
        void hasIndex();
        void index();
        void parent();
        void data();

    protected Q_SLOTS:
        void runAllTests();
        void layoutAboutToBeChanged();
        void layoutChanged();
        void rowsAboutToBeInserted( const QModelIndex& parent, int start, int end );
        void rowsInserted( const QModelIndex& parent, int start, int end );
        void rowsAboutToBeRemoved( const QModelIndex& parent, int start, int end );
        void rowsRemoved( const QModelIndex& parent, int start, int end );

    private:
        void checkChildren( const QModelIndex& parent, int currentDepth = 0 );

        QAbstractItemModel* model;

        struct Changing
        {
            QModelIndex parent;
            int oldSize;
            QVariant last;
            QVariant next;
        };
        QStack<Changing> insert;
        QStack<Changing> remove;

        bool fetchingMore;

        QList<QPersistentModelIndex> changing;
};

#endif

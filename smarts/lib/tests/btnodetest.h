/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Laszlo Papp <lpapp@kde.org>
 * Copyright (c) 2012 Arnolds Bogdanovs <arnolds.bogdanovs@inbox.lv>
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

#ifndef GLUON_SMARTS_BTNODETEST_H
#define GLUON_SMARTS_BTNODETEST_H

#include <smarts/lib/btnode.h>

class btnodetest : public QObject
{
    Q_OBJECT
    public:
        btnodetest();
        virtual ~btnodetest();

    private Q_SLOTS:
        void testSetName();
        void testSetDescription();
        void testSetClassName();
        void testSetType();
        void testAppendChild();
        void testInsertChild();
        void testRemoveChild();
        void testSetCurrentChildIndex();
        void testNextChildIndex();
        void testRunChild();
        void testSetCurrentChildStatus();
        void testSetParentNode();

    private:
        QString m_testString;
        int m_overRangeValue;
        int m_firstChild;
        int m_secondChild;
};

#endif

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

#ifndef GLUON_CORE_METAINFOTEST_H
#define GLUON_CORE_METAINFOTEST_H

#include <QtCore/QObject>

class MetaInfoTest : public QObject
{
	Q_OBJECT

public:
    MetaInfoTest();
    virtual ~MetaInfoTest();

private Q_SLOTS:
    void testHasPropertyRange();
    void testPropertyRangeMin();
    void testPropertyRangeMax();
    void testRemovePropertyRange();
    void testBoundRange();
    void testHasPropertySteps();
    void testPropertySteps();
    void testRemovePropertySteps();
    void testBoundSteps();
    void testBoundRangeAndSteps();
    void testDefaultExtension();
};

#endif // GLUON_CORE_METAINFOTEST_H

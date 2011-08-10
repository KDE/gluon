/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2000 Stephan Kulow <coolo@kde.org>
                       David Faure <faure@kde.org>
 * Copyright (C) 2006 Kevin Ottens <ervin@kde.org>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef ABSTRACTJOB_P_H
#define ABSTRACTJOB_P_H

#include "abstractjob.h"

#include <QtCore/QMap>

class QTimer;
class QEventLoop;

class AbstractJobPrivate
{
public:
    AbstractJobPrivate();
    ~AbstractJobPrivate();

    int error;
    QString errorText;
    AbstractJob::Unit progressUnit;
    QMap<AbstractJob::Unit, qulonglong> processedAmount;
    QMap<AbstractJob::Unit, qulonglong> totalAmount;
    unsigned long percentage;
    bool suspended;
    AbstractJob::Capabilities capabilities;
    QTimer *speedTimer;
    bool isAutoDelete;
    QEventLoop *eventLoop;


    static bool _k_abstractjobUnitEnumRegistered;

    bool isFinished;

public Q_SLOTS:

    void _k_speedTimeout();

};

#endif

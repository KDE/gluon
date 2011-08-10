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

#include "abstractjob.h"
#include "abstractjob_p.h"

#include <QtCore/QEventLoop>
#include <QtCore/QMap>
#include <QtCore/QMetaType>
#include <QtCore/QTimer>

bool AbstractJobPrivate::_k_abstractjobUnitEnumRegistered = false;

AbstractJobPrivate::AbstractJobPrivate()
    : error(AbstractJob::NoError)
    , progressUnit(AbstractJob::Bytes)
    , percentage(0)
    , suspended(false)
    , capabilities(AbstractJob::NoCapabilities)
    , speedTimer(0)
    , isAutoDelete(true)
    , eventLoop(0)
    , isFinished(false)
{
    if (!_k_abstractjobUnitEnumRegistered) {
        _k_abstractjobUnitEnumRegistered = qRegisterMetaType<AbstractJob::Unit>("AbstractJob::Unit");
    }
}

AbstractJobPrivate::~AbstractJobPrivate()
{
}

AbstractJob::AbstractJob(QObject *parent)
    : QObject(parent)
    , d(new AbstractJobPrivate)
{
    // d->q = this;
}

AbstractJob::~AbstractJob()
{
    delete d->speedTimer;
    delete d;
}

AbstractJob::Capabilities AbstractJob::capabilities() const
{
    return d->capabilities;
}

bool AbstractJob::isSuspended() const
{
    return d->suspended;
}

bool AbstractJob::kill( KillVerbosity verbosity )
{
    if ( doKill() )
    {
        setError( KilledJobError );

        if ( verbosity!=Quietly )
        {
            emitResult();
        }
        else
        {
            // If we are displaying a progress dialog, remove it first.
            emit finished(this);

            if ( isAutoDelete() )
                deleteLater();
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool AbstractJob::suspend()
{
    if ( !d->suspended )
    {
        if ( doSuspend() )
        {
            d->suspended = true;
            emit suspended(this);

            return true;
        }
    }

    return false;
}

bool AbstractJob::resume()
{
    if ( d->suspended )
    {
        if ( doResume() )
        {
            d->suspended = false;
            emit resumed(this);

            return true;
        }
    }

    return false;
}

bool AbstractJob::doKill()
{
    return false;
}

bool AbstractJob::doSuspend()
{
    return false;
}

bool AbstractJob::doResume()
{
    return false;
}

void AbstractJob::setCapabilities( AbstractJob::Capabilities capabilities )
{
    d->capabilities = capabilities;
}

bool AbstractJob::exec()
{
    // Usually this job would delete itself, via deleteLater() just after
    // emitting result() (unless configured otherwise). Since we use an event
    // loop below, that event loop will process the deletion event and we'll
    // have been deleted when exec() returns. This crashes, so temporarily
    // suspend autodeletion and manually do it afterwards.
    const bool autoDeleted = isAutoDelete();
    setAutoDelete( false );

    Q_ASSERT( !d->eventLoop );

    QEventLoop loop( this );
    d->eventLoop = &loop;

    start();
    if( !d->isFinished ) {
        d->eventLoop->exec(QEventLoop::ExcludeUserInputEvents);
    }
    d->eventLoop = 0;

    if ( autoDeleted ) {
        deleteLater();
    }
    return ( d->error == NoError );
}

int AbstractJob::error() const
{
    return d->error;
}

QString AbstractJob::errorText() const
{
    return d->errorText;
}

QString AbstractJob::errorString() const
{
    return d->errorText;
}

qulonglong AbstractJob::processedAmount(Unit unit) const
{
    return d->processedAmount[unit];
}

qulonglong AbstractJob::totalAmount(Unit unit) const
{
    return d->totalAmount[unit];
}

unsigned long AbstractJob::percent() const
{
    return d->percentage;
}

void AbstractJob::setError( int errorCode )
{
    d->error = errorCode;
}

void AbstractJob::setErrorText( const QString &errorText )
{
    d->errorText = errorText;
}

void AbstractJob::setProcessedAmount(Unit unit, qulonglong amount)
{
    bool should_emit = (d->processedAmount[unit] != amount);

    d->processedAmount[unit] = amount;

    if ( should_emit )
    {
        emit processedAmount(this, unit, amount);
        if (unit==d->progressUnit) {
            emit processedSize(this, amount);
            emitPercent(d->processedAmount[unit], d->totalAmount[unit]);
        }
    }
}

void AbstractJob::setTotalAmount(Unit unit, qulonglong amount)
{
    bool should_emit = (d->totalAmount[unit] != amount);

    d->totalAmount[unit] = amount;

    if ( should_emit )
    {
        emit totalAmount(this, unit, amount);
        if (unit==d->progressUnit) {
            emit totalSize(this, amount);
            emitPercent(d->processedAmount[unit], d->totalAmount[unit]);
        }
    }
}

void AbstractJob::setPercent( unsigned long percentage )
{
    if ( d->percentage!=percentage )
    {
        d->percentage = percentage;
        emit percent( this, percentage );
    }
}

void AbstractJob::emitResult()
{
    d->isFinished = true;

    if ( d->eventLoop ) {
        d->eventLoop->quit();
    }

    // If we are displaying a progress dialog, remove it first.
    emit finished( this );

    emit result( this );

    if ( isAutoDelete() )
        deleteLater();
}

void AbstractJob::emitPercent( qulonglong processedAmount, qulonglong totalAmount )
{
    // calculate percents
    if (totalAmount) {
        unsigned long oldPercentage = d->percentage;
        d->percentage = (unsigned long)(( (float)(processedAmount) / (float)(totalAmount) ) * 100.0);
        if ( d->percentage != oldPercentage ) {
            emit percent( this, d->percentage );
        }
    }
}

void AbstractJob::emitSpeed(unsigned long value)
{
    if (!d->speedTimer) {
        d->speedTimer = new QTimer(this);
        connect(d->speedTimer, SIGNAL(timeout()), SLOT(_k_speedTimeout()));
    }

    emit speed(this, value);
    d->speedTimer->start(5000);   // 5 seconds interval should be enough
}

void AbstractJobPrivate::_k_speedTimeout()
{
    // send 0 and stop the timer
    // timer will be restarted only when we receive another speed event
    
    // TODO: make it work
    // emit q->speed(q, 0);
    speedTimer->stop();
}

bool AbstractJob::isAutoDelete() const
{
    return d->isAutoDelete;
}

void AbstractJob::setAutoDelete( bool autodelete )
{
    d->isAutoDelete = autodelete;
}

#include "abstractjob.moc"

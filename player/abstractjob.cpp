/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2000 Stephan Kulow <coolo@kde.org>
                       David Faure <faure@kde.org>
 * Copyright (C) 2006 Kevin Ottens <ervin@kde.org>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#include <QtCore/QEventLoop>
#include <QtCore/QMap>
#include <QtCore/QMetaType>
#include <QtCore/QTimer>
#include <QtCore/QVariant>

class AbstractJob::Private
{
    public:
        Private()
            : percentage( 0 )
            , speedTimer( 0 )
            , isAutoDelete( true )
            , isFinished( false )
        { }
        ~Private() { }
        void _k_speedTimeout();

        QString errorText;
        qulonglong processedAmount;
        qulonglong totalAmount;
        unsigned long percentage;
        QTimer* speedTimer;
        bool isAutoDelete;
        bool isFinished;
};

AbstractJob::AbstractJob( QObject* parent )
    : QObject( parent )
    , d( new Private )
{
}

AbstractJob::~AbstractJob()
{
    delete d->speedTimer;
    delete d;
}

bool AbstractJob::kill()
{
    if( doKill() )
    {
        emit finished();
        emit failed();

        if( isAutoDelete() )
            deleteLater();
        return true;
    }
    else
    {
        return false;
    }
}

bool AbstractJob::doKill()
{
    return false;
}

qulonglong AbstractJob::processedAmount() const
{
    return d->processedAmount;
}

qulonglong AbstractJob::totalAmount() const
{
    return d->totalAmount;
}

unsigned long AbstractJob::percent() const
{
    return d->percentage;
}

QString AbstractJob::errorText() const
{
    return d->errorText;
}

void AbstractJob::setErrorText( const QString& errorText )
{
    d->errorText = errorText;
}

void AbstractJob::setProcessedAmount( qulonglong amount )
{
    bool should_emit = ( d->processedAmount != amount );

    d->processedAmount = amount;

    if( should_emit )
    {
        emit processedAmount( amount );
        emit processedSize( amount );
        setPercent( d->processedAmount, d->totalAmount );
    }
}

void AbstractJob::setTotalAmount( qulonglong amount )
{
    bool should_emit = ( d->totalAmount != amount );

    d->totalAmount = amount;

    if( should_emit )
    {
        emit totalAmount( amount );
        emit totalSize( amount );
        setPercent( d->processedAmount, d->totalAmount );
    }
}

void AbstractJob::setPercent( unsigned long percentage )
{
    if( d->percentage != percentage )
    {
        d->percentage = percentage;
        emit percent( percentage );
    }
}

void AbstractJob::emitSucceeded()
{
    d->isFinished = true;
    emit finished();
    emit succeeded();
    if( isAutoDelete() )
        deleteLater();
}

void AbstractJob::emitFailed()
{
    d->isFinished = true;
    emit finished();
    emit failed();
    if( isAutoDelete() )
        deleteLater();
}

void AbstractJob::setPercent( qulonglong processedAmount, qulonglong totalAmount )
{
    // calculate percents
    if( totalAmount )
    {
        unsigned long oldPercentage = d->percentage;
        d->percentage = ( unsigned long )((( float )( processedAmount ) / ( float )( totalAmount ) ) * 100.0 );
        if( d->percentage != oldPercentage )
        {
            emit percent( d->percentage );
        }
    }
}

void AbstractJob::emitSpeed( unsigned long value )
{
    if( !d->speedTimer )
    {
        d->speedTimer = new QTimer( this );
        connect( d->speedTimer, SIGNAL(timeout()), SLOT(_k_speedTimeout()) );
    }

    emit speed( value );
    d->speedTimer->start( 5000 ); // 5 seconds interval should be enough
}

void AbstractJob::Private::_k_speedTimeout()
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

void AbstractJob::start()
{
    //Do initialization stuff, and then call startImplementation()
    startImplementation();
}

QVariant AbstractJob::data()
{
    return QVariant();  //FIXME: This implementation should not be needed.
}

#include "moc_abstractjob.cpp"

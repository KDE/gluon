/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "metainfo.h"
#include "gluonobject.h"

using namespace GluonCore;

class MetaInfo::MetaInfoPrivate
{
    public:
        MetaInfoPrivate() {};
        ~MetaInfoPrivate() {};

        QHash<QString, qreal> propertyRangeMin;
        QHash<QString, qreal> propertyRangeMax;
        QHash<QString, quint32> propertySteps;
        QString defaultExtension;
};

MetaInfo::MetaInfo( GluonObject* parent )
    : QObject( parent )
    , d( new MetaInfoPrivate )
{
}

MetaInfo::MetaInfo( const GluonCore::MetaInfo& other )
{
    delete d;
}

MetaInfo::~MetaInfo()
{
}

void
MetaInfo::setPropertyRange( const QString& property, qreal min, qreal max )
{
    d->propertyRangeMin.insert( property, min );
    d->propertyRangeMax.insert( property, max );
}

bool
MetaInfo::hasPropertyRange( const QString& property ) const
{
    return d->propertyRangeMin.keys().contains( property );
}

qreal
MetaInfo::propertyRangeMin( const QString& property ) const
{
    // This will return 0 if we do not have a property range for this property
    // name - but anybody using it should have checked beforehand
    return d->propertyRangeMin.value( property );
}

qreal
MetaInfo::propertyRangeMax( const QString& property ) const
{
    // This will return 0 if we do not have a property range for this property
    // name - but anybody using it should have checked beforehand
    return d->propertyRangeMax.value( property );
}

void
MetaInfo::removePropertyRange( const QString& property )
{
    d->propertyRangeMin.remove( property );
    d->propertyRangeMax.remove( property );
}

qreal
MetaInfo::applyRange( const QString& property, qreal newValue ) const
{
    if( !hasPropertyRange( property ) )
        return newValue;
    qBound( d->propertyRangeMin[property], newValue, d->propertyRangeMax[property] );
    return 0;
}

void
MetaInfo::setPropertySteps( const QString& property, quint32 steps )
{
    d->propertySteps.insert( property, steps );
}

bool
MetaInfo::hasPropertySteps( const QString& property ) const
{
    return d->propertySteps.keys().contains( property );
}

quint32
MetaInfo::propertySteps( const QString& property ) const
{
    // This will return 0 if we do not have a property step for this property
    // name - but anybody using it should have checked beforehand
    return d->propertySteps.value( property );
}

void
MetaInfo::removePropertySteps( const QString& property )
{
    d->propertySteps.remove( property );
}

qreal
MetaInfo::applySteps( const QString& property, qreal newValue ) const
{
    if( !hasPropertySteps( property ) || !hasPropertyRange( property ) )
        return newValue;

    // Bit of help from Morten Justesen on this one, nice bit of mathematics ;)
    const qreal step = ( d->propertyRangeMax.value( property ) - d->propertyRangeMin.value( property ) ) / d->propertySteps.value( property );
    return qRound64( newValue / step ) * step;
}

qreal
MetaInfo::applyRangeAndStep( const QString& property, qreal newValue ) const
{
    if( !hasPropertySteps( property ) || !hasPropertyRange( property ) )
        return newValue;

    // Bit of help from Morten Justesen on this one, nice bit of mathematics ;)
    const qreal step = ( d->propertyRangeMax.value( property ) - d->propertyRangeMin.value( property ) ) / d->propertySteps.value( property );
    return qRound64( qBound( d->propertyRangeMin[property], newValue, d->propertyRangeMax[property] ) / step ) * step;
}

QString
MetaInfo::defaultExtension() const
{
    return d->defaultExtension;
}

void
MetaInfo::setDefaultExtension( const QString& extension )
{
    d->defaultExtension = extension;
}


#include "metainfo.moc"

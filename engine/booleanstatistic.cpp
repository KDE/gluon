/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#include "booleanstatistic.h"

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, BooleanStatistic )

class BooleanStatistic::BooleanStatisticPrivate
{
    public:
        BooleanStatisticPrivate() : checked(false) {}
        ~BooleanStatisticPrivate() {}

        bool checked;
};

BooleanStatistic::BooleanStatistic(QObject* parent)
    : AbstractStatistic(parent)
    , d( new BooleanStatisticPrivate() )
{
}

BooleanStatistic::~BooleanStatistic()
{
    delete d;
}

bool BooleanStatistic::isChecked()
{
    return d->checked;
}

void BooleanStatistic::setChecked( bool checked )
{
    d->checked = checked;
}

void BooleanStatistic::check()
{
    d->checked = true;
}

void BooleanStatistic::commit()
{
    if( d->checked )
    {
        setValue( 1 );
        AbstractStatistic::commit();
    }
}

#include "booleanstatistic.moc"

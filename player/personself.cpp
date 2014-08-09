 
/******************************************************************************
 * This file is part of the Gluon Development Platform
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
 
#include "personself.h"
 
#include <QtCore/QStringList>
 
using namespace GluonPlayer;
 
class PersonSelf::Private
{
    public:
        Private()
        {
        }
 
        QString personid;
        QString firstname;
        QString lastname;
};
 
PersonSelf::PersonSelf( const QString& personid, const QString& firstname, const QString& lastname,
                                                QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->personid = personid;
    d->firstname = firstname;
    d->lastname = lastname;
}
 
PersonSelf::~PersonSelf()
{
    delete d;
}
 
QString PersonSelf::id() const
{
    return d->personid;
}
 
QString PersonSelf::firstName() const
{
    return d->firstname;
}
 
QString PersonSelf::lastName() const
{
    return d->lastname;
}
 
/* still not compliant to OCS specs
QString PersonSelf::email() const
{
    return d->email;
}
*/
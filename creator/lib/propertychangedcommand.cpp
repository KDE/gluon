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

#include "propertychangedcommand.h"
#include "objectmanager.h"

#include <QDebug>

#include <core/gluonobject.h>
#include <core/gluonvarianttypes.h>

#include <QtCore/QVariant>

using namespace GluonCreator;

class PropertyChangedCommand::Private
{
    public:
        QString property;
        QVariant oldValue;
        QVariant newValue;

        static QVector< uint > mergeTypes;
        static QVector< int > mergeUserTypes;
};

QVector< uint > PropertyChangedCommand::Private::mergeTypes = QVector< uint >() << QVariant::Char << QMetaType::Float << QVariant::Double << QVariant::Size << QVariant::SizeF << QVariant::String << QVariant::Color << QVariant::UserType;
QVector< int > PropertyChangedCommand::Private::mergeUserTypes = QVector< int >() << GluonCore::VariantType::Vector2f << GluonCore::VariantType::Vector3f << GluonCore::VariantType::Vector4f << GluonCore::VariantType::Quaternionf;

PropertyChangedCommand::PropertyChangedCommand( GluonCore::GluonObject* object, QString property, QVariant oldValue, QVariant newValue )
    : d( new Private )
{
    setObject( object );
    d->property = property;
    d->oldValue = oldValue;
    d->newValue = newValue;

    setCommandName( "PropertyChangedCommand" );
}

PropertyChangedCommand::~PropertyChangedCommand()
{
    delete d;
}

int PropertyChangedCommand::id() const
{
    return 16 + 3 + 3; // P + C + C
}

void PropertyChangedCommand::undo()
{
    setCommandDirection( "undo" );
    object()->setProperty( d->property.toUtf8(), d->oldValue );
    ObjectManager::instance()->notifyPropertyChanged( object(), d->property, d->oldValue );
    AbstractUndoCommand::undo();
}

void PropertyChangedCommand::redo()
{
    setCommandDirection( "redo" );
    object()->setProperty( d->property.toUtf8(), d->newValue );
    ObjectManager::instance()->notifyPropertyChanged( object(), d->property, d->newValue );
    AbstractUndoCommand::redo();
}

bool PropertyChangedCommand::mergeWith( const QUndoCommand* other )
{
    if( other->id() != id() )
        return false;

    const PropertyChangedCommand* pcc = static_cast< const PropertyChangedCommand* >( other );
    if( pcc->d->property != d->property )
        return false;

    if( pcc->d->newValue.type() != d->newValue.type() && pcc->d->newValue.userType() != d->newValue.userType() )
        return false;

    if( ! Private::mergeTypes.contains( d->newValue.type() ) )
        return false;

    if( d->newValue.type() == QVariant::UserType && ! Private::mergeUserTypes.contains( d->newValue.userType() ) )
        return false;

    d->newValue = pcc->d->newValue;

    return true;
}

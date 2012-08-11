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
#include <QDebug>
#include <core/gluonobject.h>
#include <QMetaObject>
#include <QMetaProperty>
#include <QtCore/QVariant>

using namespace GluonCreator;

class PropertyChangedCommand::PropertyChangedCommandPrivate
{
    public:
        QString property;
        QVariant oldValue;
        QVariant newValue;
};

PropertyChangedCommand::PropertyChangedCommand( GluonCore::GluonObject* object, QString property, QVariant oldValue, QVariant newValue )
{
    d = new PropertyChangedCommandPrivate;
    setObject( object );
    d->property = property;
    d->oldValue = oldValue;
    d->newValue = newValue;

    setCommandName( "PropertyChangedCommand" );
}

PropertyChangedCommand::~PropertyChangedCommand()
{
}

void PropertyChangedCommand::undo()
{
    setCommandDirection( "undo" );
    qDebug()<<"On undo, old value is"<<d->oldValue;
    object()->setProperty( d->property.toUtf8(), d->oldValue );
    emit onUndo(object(),d->property,d->oldValue);
 //   AbstractUndoCommand::undo();
}

void PropertyChangedCommand::redo()
{
    qDebug()<<"On redo, new value is"<<d->newValue;
    setCommandDirection( "redo" );
    object()->setProperty( d->property.toUtf8(), d->newValue );
    emit onRedo(object(),d->property,d->newValue);
   // AbstractUndoCommand::redo();
}


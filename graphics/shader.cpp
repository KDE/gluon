/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "shader.h"

#include <QtCore/QString>
#include <QtCore/QHash>

using namespace GluonGraphics;

class Shader::Private
{
    public:
        QHash< Shader::SourceType, QString > sources;
        QHash< QString, int > attributes;
        QString error;
};

Shader::Shader()
    : d( new Private )
{

}

Shader::~Shader()
{
    delete d;
}

QString Shader::source( Shader::SourceType type ) const
{
    return d->sources.value( type );
}

void Shader::setSource( Shader::SourceType type, const QString& source )
{
    d->sources[ type ] = source;
}

QString Shader::error() const
{
    return d->error;
}

QHash< QString, int >
Shader::attributes() const
{
    return d->attributes;
}

int Shader::attributeIndex( const QString& name ) const
{
    return d->attributes.value( name );
}

bool Shader::hasAttribute( const QString& name ) const
{
    return d->attributes.contains( name );
}

void Shader::setError( const QString& error )
{
    d->error = error;
}

void Shader::setAttributes(const QHash< QString, int >& attribs)
{
    d->attributes = attribs;
}

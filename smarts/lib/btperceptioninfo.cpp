/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#include "btperceptioninfo.h"

#include "btbrain.h"

using namespace GluonSmarts;

class btPerceptionInfo::btPerceptionInfoPrivate
{
    public:
        btPerceptionInfoPrivate()
            : radius(0)
        {
        }

        ~btPerceptionInfoPrivate()
        {
        }
        
        QVector3D position;
        qreal radius;
};

btPerceptionInfo::btPerceptionInfo(QObject * parent)
    : QObject(parent)
    , d(new btPerceptionInfoPrivate())
{
    btBrain* potentialBrain = qobject_cast<btBrain*>(parent);

	if(potentialBrain)
		potentialBrain->addPerceptionInfo(this);
}

btPerceptionInfo::~btPerceptionInfo()
{
    delete d;
}

QVector3D btPerceptionInfo::position() const
{
    return d->position;
}

void btPerceptionInfo::setPosition(const QVector3D& newPosition)
{
    d->position = newPosition;
}

qreal btPerceptionInfo::radius() const
{
    return d->radius;
}

void btPerceptionInfo::setRadius(const qreal& newRadius)
{
    d->radius = newRadius;
}

#include "btperceptioninfo.moc"

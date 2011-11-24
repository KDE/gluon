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

#include "btperception.h"

#include "btcharacter.h"

class btPerception::btPerceptionPrivate
{
    public:
        btPerceptionPrivate()
            : character(0)
            , knowledgePrecision(0)
            , perceptionLimit(0)
        {
        }

        ~btPerceptionPrivate()
        {
        }
        
        btCharacter* character;
        qreal knowledgePrecision;
        qreal perceptionLimit;
        QHash<QString, btPerceptionAtom*> perceptionAtoms;
        QList<btPerceptionViewcone*> viewcones;
};

btPerception::btPerception(QObject* parent)
    : QObject(parent)
    , d(new btPerceptionPrivate())
{
    d->character = qobject_cast<btCharacter*>(parent);
}

btPerception::~btPerception()
{
    delete(d);
}

qreal btPerception::knowledgePrecision() const
{
	return d->knowledgePrecision;
}

void btPerception::setKnowledgePrecision(const qreal& newKnowledgePrecision)
{
	d->knowledgePrecision = newKnowledgePrecision;
}

qreal btPerception::perceptionLimit() const
{
    return d->perceptionLimit;
}

void btPerception::setPerceptionLimit(const qreal& newPerceptionLimit)
{
    d->perceptionLimit = newPerceptionLimit;
}

QList< btPerceptionViewcone* > btPerception::viewCones() const
{
    return d->viewcones;
}

void btPerception::setViewCones(const QList< btPerceptionViewcone* > newViewCones)
{
    d->viewcones = newViewCones;
}

void btPerception::addViewCone(btPerceptionViewcone * viewcone)
{
	d->viewcones.append(viewcone);
}

QList< btPerceptionAtom* > btPerception::perceptionAtoms() const
{
    return d->perceptionAtoms.values();
}

btPerceptionAtom* btPerception::perceptionAtom(const QString& name) const
{
    btPerceptionAtom* theAtom = 0;
    if(d->perceptionAtoms.contains(name))
        theAtom = d->perceptionAtoms.value(name);
    else
    {
        
    }
    return theAtom;
}

void btPerception::addPerceptionAtom(btPerceptionAtom * perceptionAtom)
{
	d->perceptionAtoms[perceptionAtom->objectName()] = perceptionAtom;
}

#include "btperception.moc"

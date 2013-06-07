/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "perceptionatom.h"

#include "engine/gameobject.h"

#include "smarts/lib/btperceptionatom.h"

#include "perceptionatomprivate.h"
#include "character.h"

REGISTER_OBJECTTYPE(GluonEngine, PerceptionAtom)

using namespace GluonEngine;

PerceptionAtom::PerceptionAtom(QObject* parent): Component(parent)
{
	d = new PerceptionAtomPrivate();
	d->atom = new GluonSmarts::btPerceptionAtom();
	d->info = 0;
}

PerceptionAtom::PerceptionAtom(const PerceptionAtom& other, QObject* parent)
	: Component(parent)
	, d(other.d)
{

}

void PerceptionAtom::initialize()
{
    GluonEngine::Character * charComponent = 0;
        charComponent = qobject_cast<GluonEngine::Character*>(this->gameObject()->findComponentByType("GluonEngine::Character"));
	if(charComponent)
	{
		charComponent->addPerceptionAtom((GluonSmarts::btPerceptionAtom*)this);
	}
	else
	{
		this->gameObject()->removeComponent(this);
	}
}

PerceptionAtom::~PerceptionAtom()
{

}

QString PerceptionAtom::category() const
{
    return QString(tr("Behavior Tree"));
}

QVariant PerceptionAtom::knowledge() const
{
	return d->atom->knowledge();
}

GluonEngine::PerceptionInfo* PerceptionAtom::perceptionInfo() const
{
	return d->info;
}

void PerceptionAtom::setPerceptionInfo(GluonEngine::PerceptionInfo* info)
{
	d->info = info;
	d->atom->setPerceptionInfo(info->getBtPerceptionInfo());
}

qreal PerceptionAtom::precision() const
{
	return d->atom->precision();
}

void PerceptionAtom::setPrecision(qreal precision)
{
	d->atom->setPrecision(precision);
}

void PerceptionAtom::setShouldUpdate(bool update)
{
	d->atom->setShouldUpdate(update);
}

bool PerceptionAtom::shouldUpdate() const
{
	return d->atom->shouldUpdate();
}



 

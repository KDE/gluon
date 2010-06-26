/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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
#include "gluonbuttonmapper.h"

#include "inputdevice.h"
#include "gluonbuttonmapperprivate.h"

#include <QtCore/QDebug>
#include <QtCore/QStringList>

using namespace GluonInput;

GluonButtonMapper::GluonButtonMapper(QObject * parent)
		: QObject(parent)
{
	d = new GluonButtonMapperPrivate();
}

GluonButtonMapper::~GluonButtonMapper()
{
}

void GluonButtonMapper::setButton(const QString &name, InputDevice* input, int keyCode)
{
	if (!input->buttonCapabilities().contains(keyCode))
	{
		qDebug() << "Cannot find keyCode for this input...";
		return;
	}
	connect(input, SIGNAL(eventSent(InputEvent*)), this, SLOT(inputEvent(InputEvent*)));
	d->m_buttons.insert(name, qMakePair(input, keyCode));

}

void GluonButtonMapper::setButton(const QString &name)
{
	InputDevice * input = new InputDevice();
	d->m_buttons.insert(name, qMakePair(input, 0));
}

void GluonButtonMapper::setAbsAxis(const QString &name, InputDevice * input, int axis)
{
	if (!input->absAxisCapabilities().contains(axis))
	{
		qDebug() << "Cannot find keyCode for this input...";
		return;
	}
	d->m_absAxis.insert(name, qMakePair(input, axis));
	connect(input, SIGNAL(eventSent(InputEvent*)), this, SLOT(inputEvent(InputEvent*)));
}

void GluonButtonMapper::setRelAxis(const QString &name, InputDevice* input, int axis)
{
	if (!input->relAxisCapabilities().contains(axis))
	{
		qDebug() << "Cannot find keyCode for this input...";
		return;
	}
	d->m_absAxis.insert(name, qMakePair(input, axis));
	connect(input, SIGNAL(eventSent(InputEvent*)), this, SLOT(inputEvent(InputEvent*)));

}

void GluonButtonMapper::remButton(const QString &name)
{
	if (d->m_buttons.contains(name))
	{
		disconnect(d->m_buttons[name].first, SIGNAL(eventSent(InputEvent*)), this, SLOT(inputEvent(InputEvent*)));
		d->m_buttons.remove(name);
	}
}

void GluonButtonMapper::remAbsAxis(const QString &name)
{
	if (d->m_absAxis.contains(name))
	{
		disconnect(d->m_buttons[name].first, SIGNAL(eventSent(InputEvent*)), this, SLOT(inputEvent(InputEvent*)));
		d->m_absAxis.remove(name);
	}
}

void GluonButtonMapper::remRelAxis(const QString &name)
{
	if (d->m_relAxis.contains(name))
	{
		disconnect(d->m_buttons[name].first, SIGNAL(eventSent(InputEvent*)), this, SLOT(inputEvent(InputEvent*)));
		d->m_relAxis.remove(name);
	}
}

QStringList GluonButtonMapper::buttonNameList()
{
	QStringList list;
	QMapIterator  <QString, QPair<InputDevice*, int> >  i(d->m_buttons);
	while (i.hasNext())
	{
		i.next();
		list << i.key();
	}
	return list;
}

QStringList GluonButtonMapper::absAxisNameList()
{
	QStringList list;
	QMapIterator  <QString, QPair<InputDevice*, int> >  i(d->m_absAxis);
	while (i.hasNext())
	{
		i.next();
		list << i.key();
	}
	return list;
}

QStringList GluonButtonMapper::relAxisNameList()
{
	QStringList list;
	QMapIterator  <QString, QPair<InputDevice*, int> >  i(d->m_relAxis);
	while (i.hasNext())
	{
		i.next();
		list << i.key();
	}
	return list;
}

#include "gluonbuttonmapper.moc"

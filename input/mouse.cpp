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
#include "mouse.h"
#include "mouseprivate.h"

#include <QtCore/QDebug>

using namespace GluonInput;

Mouse::Mouse(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
{
  qDebug() <<"creating mouse";
	d = new MousePrivate();
	d->originalPosition = d->position = QPoint(0, 0);
	d->sensibility = 1;
	
	
	connect(inputThread, SIGNAL(relAxisMoved(int, int)), this, SLOT(mouseMoved(int, int)), Qt::DirectConnection);
}

QPoint Mouse::position()
{
	return d->position;
}

void Mouse::setSensibility(double s)
{
	d->sensibility = s;
}

void Mouse::setOrigin(const QPoint p)
{
	d->originalPosition = p;
}

int Mouse::wheelPosition() const
{
	return d->wheelPos;//relAxisValue(lastRelAxis());
}

int Mouse::hWheelPosition()const
{
	return d->hWheelPos;//relAxisValue(lastRelAxis());
}

double Mouse::sensibility()const
{
	return d->sensibility;
}

void Mouse::mouseMoved(int axis, int distance)
{
	switch(axis)
	{
		case GluonButtons::X_REL:
			d->position.setX(d->position.x() + distance);
			break;
			
		case GluonButtons::Y_REL:
			d->position.setY(d->position.y() + distance);
			break;
		case GluonButtons::HWHEEL:
			d->hWheelPos = distance;
			break;
		case GluonButtons::WHEEL_REL:
			d->wheelPos = distance;
			break;
	}
}


#include "mouse.moc"

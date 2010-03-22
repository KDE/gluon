#include "mouse.h"
#include "mouseprivate.h"

#include <QtCore/QDebug>

using namespace GluonInput;

Mouse::Mouse(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
{
	d = new MousePrivate();
	d->originalPosition = d->position = QPoint(0, 0);
	d->sensibility = 1;
	
	connect(inputThread, SIGNAL(relAxisMoved(int, int)), this, SLOT(mouseMoved(int, int)));
}

QPoint Mouse::position()
{
	/*if (anyRelMove())
	{
		d->position += QPoint(relAxisValue(lastRelAxis()), relAxisValue(lastRelAxis()));
	}
	return (d->position + d->originalPosition)*d->sensibility;*/
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
	return relAxisValue(lastRelAxis());
}

int Mouse::hWheelPosition()const
{
	return relAxisValue(lastRelAxis());
}

double Mouse::sensibility()const
{
	return d->sensibility;
}

void Mouse::mouseMoved(int axis, int distance)
{
	if(axis == GluonInput::X_AXIS)
	{
		d->position.setX(d->position.x() + distance);
	}
	else if (axis == GluonInput::Y_AXIS)
	{
		d->position.setY(d->position.y() + distance);
	}
}

#include "mouse.moc"

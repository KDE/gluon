#include "mouse.h"
#include "mouseprivate.h"

#include <QtCore/QDebug>

using namespace GluonInput;

Mouse::Mouse(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
{
	d = new MousePrivate();
	d->originalPosition = d->position = QPoint(0, 0);
	d->sensibility = 1;
}

QPoint Mouse::position()
{
	if (anyRelMove())
	{
		d->position += QPoint(relAxisValue(lastRelAxis()), relAxisValue(lastRelAxis()));
	}
	return (d->position + d->originalPosition)*d->sensibility;
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
#include "mouse.moc"

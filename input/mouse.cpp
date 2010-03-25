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

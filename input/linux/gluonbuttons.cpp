#include "gluonbuttons.h"

#include <QtCore/QMetaEnum>

using namespace GluonInput;

template<> GLUON_INPUT_EXPORT GluonButtons *GluonCore::Singleton<GluonButtons>::m_instance = 0;

GluonButtons::GluonButtons()
{
}

GluonButtons::~GluonButtons()
{
}

QString GluonButtons::buttonName(DeviceFlag deviceType, int code)
{
	return this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("Button")).valueToKey(code);
}

QString GluonButtons::axisName(DeviceFlag deviceType,int code)
{
	QString value = "";
	switch (deviceType)
	{
		case MouseDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("Relative")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		case JoystickDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("Absolute")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		default:
			return "Unknown";
	}
}

#include "gluonbuttons.moc"

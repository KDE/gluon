#include "gluonbuttons.h"

#include <QtCore/QMetaEnum>
#include <QtCore/QString>

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
	QString value = "";
	switch (deviceType)
	{
		case KeyboardDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("KeyboardButton")).valueToKey(code);
			return value != "" ? value : "Reserved";
			break;
		case MouseDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("MouseButton")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		case JoystickDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("JoystickButton")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		default:
			return "Unknown";
	}
}

QString GluonButtons::axisName(DeviceFlag deviceType,int code)
{
	QString value = "";
	switch (deviceType)
	{
		case MouseDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("RelAbs")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		case JoystickDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("RelAbs")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		default:
			return "Unknown";
	}
}

#include "gluonbuttons.moc"

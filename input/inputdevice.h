#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QPoint>
#include <QtCore/QThread>
#include <QtCore/QEvent>

#include "code.h"
#include "threadabstract.h"
#include "inputevent.h"

namespace GluonInput
{
	class GLUON_INPUT_EXPORT InputDevice : public QObject
	{
		Q_OBJECT

	public:
		//InputDevice(IOHIDDeviceRef device, QObject * parent = 0);
		InputDevice(ThreadAbstract * inputThread, QObject * parent = 0);
		InputDevice();
		~InputDevice();

		int vendor()const;
		int product()const;
		int version()const;
		int bustype()const;
		//const QString devicePath() const;
		//const IOHIDDeviceRef device() const;
		const QString deviceName() const;
		GluonInput::DeviceFlag deviceType()const;
		bool button(int code)const;
		int anyPress() const;
		bool anyAbsMove();
		bool anyRelMove();
		int lastAbsAxis()const;
		int lastRelAxis()const;
		int relAxisValue(int code)const;
		int absAxisValue(int code)const;
		QList<int> buttonCapabilities()const;
		QList<int> absAxisCapabilities()const;
		QList<int> relAxisCapabilities()const;
		AbsVal axisInfo(int axisCode)const;
		bool error()const;
		QString msgError()const;
		bool isEnabled() const;

	signals:
		void eventSent(InputEvent * event);
		void buttonPressed(int code);
		void buttonReleased(int code);
		void absAxisChanged(int axe, int code);
		void relAxisChanged(int axe, int code);
		void pressed();
		void moved();

	public slots:
		void setEnabled();
		void setDisabled();

	protected:
		//void readInformation();
		bool event(QEvent * evt);

		/*int m_xAbsUsage;
		int m_yAbsUsage;
		int m_zAbsUsage;*/

		int m_lastAbsAxis;
		int m_lastRelAxis;

		ThreadAbstract *inputListener;
	private:
		//ThreadAbstract *inputListener;
		//IOHIDDeviceRef m_device;
		//QString m_deviceName;
		//GluonInput::DeviceFlag m_deviceType;

		QList<int> m_buttons;  //list of button pressed
		QList<int> m_forceFeedBack;
		QMap<int, int> m_relAxis; // list of relatif axis Value .  m_relAxis[REL_X] = -1;
		QMap<int, int> m_absAxis; // list of absolue axis value. m_absAxis[ABS_Rx] = 156
		/*QList<int> m_buttonCapabilities; // list of button capability. BTN_ESC, BTN_F1 etc....
		QList<int> m_relAxisCapabilities; // list of rel Axis capability..
		QList<int> m_absAxisCapabilities; // list of abs Axis capabilty
		QMap<int, AbsVal> m_absAxisInfos; // each Absolute Axis has a sub info called AbsVal. [ABS_RX] = AbsVal.*/
		//QString m_msgError;
		bool m_absMove;
		bool m_relMove;
		//bool m_error;
		//bool m_enable;

		/*int m_vendor;
		int m_product;
		int m_version;
		int m_bustype;*/

		void init();
	};
}
#endif // KCLINPUT_H

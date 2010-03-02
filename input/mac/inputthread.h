#ifndef _INPUTTHREAD_H_
#define _INPUTTHREAD_H_

#include "gluon_input_export.h"
#include "inputdefinitions.h"

#include <QtCore/QThread>
#include <QtCore/QObject>
#include <QtCore/QMap>

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>

namespace GluonInput
{
	class AbsVal;
	
	class GLUON_INPUT_EXPORT InputThread : public QThread
	{
		Q_OBJECT
	public:
		InputThread(IOHIDDeviceRef pDevice, QObject* parent = 0);
		~InputThread();
		
		static void deviceReport(void * inContext, IOReturn inResult, void * inSender, IOHIDValueRef inIOHIDValueRef);
		
		void setEnabled();
		void setDisabled();

		int getJoystickXAxis();
		int getJoystickYAxis();
		int getJoystickZAxis();
		
		void run();
		void stop();
		
		int vendor()const;
		int product()const;
		int version()const;
		int bustype()const;
		
		QList<int> buttonCapabilities()const;
		QList<int> absAxisCapabilities()const;
		QList<int> relAxisCapabilities()const;
		AbsVal axisInfo(int axisCode)const;
		
		const QString deviceName() const;
		GluonInput::DeviceFlag deviceType()const;
		
		bool isEnabled() const;
		
		bool error();
		QString msgError();
		
		QObject * getParent();

	private:
		void readInformation();
		
		int m_vendor;
		int m_product;
		int m_version;
		int m_bustype;
		
		QString m_deviceName;
		QString m_msgError;
		
		bool m_error;
		
		GluonInput::DeviceFlag m_deviceType;
		
		QList<int> m_buttonCapabilities; // list of button capability. BTN_ESC, BTN_F1 etc....
		QList<int> m_relAxisCapabilities; // list of rel Axis capability..
		QList<int> m_absAxisCapabilities; // list of abs Axis capabilty
		QMap<int, AbsVal> m_absAxisInfos; // each Absolute Axis has a sub info called AbsVal. [ABS_RX] = AbsVal.

		int m_xAbsUsage;
		int m_yAbsUsage;
		int m_zAbsUsage;

		IOHIDDeviceRef m_device;
	};
}
#endif
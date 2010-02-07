#ifndef _THREAD_H_
#define _THREAD_H_

#include "gluon_input_export.h"
#include "inputdefinitions.h"

#include "threadabstract.h"

#include <QtCore/QThread>
#include <QtCore/QObject>

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>

namespace GluonInput
{
	class GLUON_INPUT_EXPORT MacThread : public ThreadAbstract
	{
		Q_OBJECT
	public:
		//MacThread(IOHIDDeviceRef pDevice, int deviceUsage , QObject* parent = 0);
		MacThread(IOHIDDeviceRef pDevice, QObject* parent = 0);
		~MacThread();
		static void deviceReport(void * inContext, IOReturn inResult, void * inSender, IOHIDValueRef inIOHIDValueRef);
		//void run();

		//const IOHIDDeviceRef device() const;
		void setEnabled();
		void setDisabled();

		int deviceUsage();
		int getJoystickXAxis();
		int getJoystickYAxis();
		int getJoystickZAxis();

	private:
		void readInformation();


		int m_deviceUsage;
		int m_xAbsUsage;
		int m_yAbsUsage;
		int m_zAbsUsage;

		IOHIDDeviceRef m_device;
	};
}
#endif
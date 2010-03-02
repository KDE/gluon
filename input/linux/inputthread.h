#ifndef _INPUTTHREAD_H_
#define _INPUTTHREAD_H_

#include <QtCore/QThread>
#include <QtCore/QMap>
#include "inputdefinitions.h"
#include "gluon_input_export.h"
#include "absval.h"
/**
 * \defgroup KCL KCL
 */
//@{

namespace GluonInput
{	
	class GLUON_INPUT_EXPORT InputThread : public QThread
	{
		Q_OBJECT

	public:
		InputThread(const QString& devicePath, QObject *parent = 0);
        ~InputThread() {
			close(m_fd);
		}
		void run();

		const QString devicePath() const;
		void setEnabled();
		void setDisabled();
		int getJoystickXAxis();
		int getJoystickYAxis();
		int getJoystickZAxis();
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

		bool openDevice(const QString &devicePath);
		void closeDevice() {
			close(m_fd);
		}

		void readInformation();

	private:
		int m_fd;
		struct input_id m_device_info;
		struct input_event m_currentEvent;
		QString m_devicePath;
	};
}
//@}
#endif // KCLTHREAD_H

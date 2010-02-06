#ifndef THREADABSTRACT_H
#define THREADABSTRACT_H

#include "gluoninput.h"

#include <QtCore/QThread>
#include <QtCore/QObject>
#include <QtCore/QMap>

namespace GluonInput
{
	class GLUONINPUTSHARED_EXPORT AbsVal
	{
	public:
		AbsVal(int v = 0, int m = 0, int M = 0, int f = 0, int F = 0) {
			value = v;
			min = m;
			max = M;
			flat = f;
			fuzz = F;
		}
		int value;
		int min;
		int max;
		int flat;
		int fuzz;
	};
	
	class GLUONINPUTSHARED_EXPORT ThreadAbstract : public QThread
	{
		Q_OBJECT
	public:
		ThreadAbstract(QObject * parent = 0);
		~ThreadAbstract();
		
		virtual void run();
		
		/////
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
		
		virtual void setEnabled();
		virtual void setDisabled();
		bool isEnabled() const;
		
		bool error();
		QString msgError();
		
		QObject * getParent();
		
		virtual int getJoystickXAxis();
		virtual int getJoystickYAxis();
		virtual int getJoystickZAxis();
		
	protected:
		int m_vendor;
		int m_product;
		int m_version;
		int m_bustype;
		
		QString m_deviceName;
		QString m_msgError;
		
		bool m_enabled;
		bool m_error;
		
		GluonInput::DeviceFlag m_deviceType;
		
		QList<int> m_buttonCapabilities; // list of button capability. BTN_ESC, BTN_F1 etc....
		QList<int> m_relAxisCapabilities; // list of rel Axis capability..
		QList<int> m_absAxisCapabilities; // list of abs Axis capabilty
		QMap<int, AbsVal> m_absAxisInfos; // each Absolute Axis has a sub info called AbsVal. [ABS_RX] = AbsVal.
		
		virtual void readInformation();
	};
}

#endif
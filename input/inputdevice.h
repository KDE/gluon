#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QPoint>
#include <QtCore/QThread>
#include <QtCore/QEvent>

#include "code.h"
#include "inputthread.h"
#include "inputevent.h"

namespace GluonInput
{
	class GLUON_INPUT_EXPORT InputDevice : public QObject
	{
		Q_OBJECT

	public:
		InputDevice(InputThread * inputThread, QObject * parent = 0);
		InputDevice();
		~InputDevice();

		int vendor()const;
		int product()const;
		int version()const;
		int bustype()const;

		InputThread *inputListener;

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
		void eventSent(GluonInput::InputEvent * event);
		void buttonPressed(int code);
		void buttonReleased(int code);
		void absAxisChanged(int axe, int code);
		void relAxisChanged(int axe, int code);
		void pressed();
		void moved();

	public slots:
		void setEnabled();
		void setDisabled();

	private:
		bool event(QEvent * evt);

		int m_lastAbsAxis;
		int m_lastRelAxis;

		QList<int> m_buttons;  //list of button pressed
		QList<int> m_forceFeedBack;
		QMap<int, int> m_relAxis; // list of relatif axis Value .  m_relAxis[REL_X] = -1;
		QMap<int, int> m_absAxis; // list of absolue axis value. m_absAxis[ABS_Rx] = 156

		bool m_absMove;
		bool m_relMove;

		void init();
	};
}
#endif // KCLINPUT_H

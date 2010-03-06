#include "inputdetection.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#ifdef Q_WS_X11
#include "detectlinux.h"
#endif

#ifdef Q_WS_MAC
#include "detectmac.h"
#endif

#ifdef Q_WS_WIN
#include "detectwin.h"
#endif

namespace GluonInput
{
	template<> GLUON_INPUT_EXPORT InputDetection *GluonCore::Singleton<InputDetection>::m_instance = 0;
	
	InputDetection::InputDetection()
	{
		this->init();
	}

	InputDetection::~InputDetection()
	{
	}

	void InputDetection::init()
	{
		qDebug() << "Setting parent";
		QObject *parent = QCoreApplication::instance();
		if (!parent) {
			qDebug() << "No QCoreApplication instance found, the KCLDetect instance may be leaked when leaving";
		}
		
#ifdef Q_WS_X11
		qDebug() << "Creating instance: Linux";
		m_instance = new DetectLinux(parent);
#endif
		
#ifdef Q_WS_MAC
		qDebug() << "Creating instance: Mac";
		m_instance = new DetectMac(parent);
#endif
		
#ifdef Q_WS_WIN
		qDebug() << "Creating instance: Win";
		m_instance = new DetectWin(parent);
#endif
		if(m_instance)
		{
			qDebug() << "Instance created, searching devices";
			m_instance->searchDevice();
		}
		else
			qDebug() << "Instance not created, fail!";
	}

	void InputDetection::searchDevice()
	{    
		m_instance->searchDevice();
	}

	void InputDetection::setAllEnable()
	{
		m_instance->setAllEnabled();
	}

	void InputDetection::setAllDisable()
	{
		m_instance->setAllDisabled();
	}   

	unsigned int InputDetection::deviceCount() 
	{
		return inputList().size();
	}

	unsigned int InputDetection::keyboardCount() 
	{
		return m_instance->getKeyboardList().size();
	}

	unsigned int InputDetection::mouseCount() 
	{
		return m_instance->getMouseList().size();
	}

	unsigned int InputDetection::joystickCount() 
	{
		return m_instance->getJoystickList().size();
	}

	unsigned int InputDetection::tabletCount() 
	{
		return m_instance->getTabletList().size();
	}

	unsigned int InputDetection::unknownDeviceCount() 
	{
		return m_instance->getUnknownDeviceList().size();
	}

	QList<KeyBoard*> InputDetection::keyboardList() 
	{
		return m_instance->getKeyboardList();
	}

	QList<Mouse*> InputDetection::mouseList()
	{
		return m_instance->getMouseList();
	}

	QList<Joystick*> InputDetection::joystickList()
	{
		return m_instance->getJoystickList();
	}

	QList<Tablet*> InputDetection::tabletList() 
	{
		return m_instance->getTabletList();
	}

	QList<InputDevice*> InputDetection::unknownDeviceList() 
	{
		return m_instance->getUnknownDeviceList();
	}

	InputList InputDetection::inputList() 
	{
		return m_instance->getInputList();
	}

	KeyBoard* InputDetection::keyboard(int id) 
	{
		return m_instance->getKeyboardList().at(id);
	}

	Mouse* InputDetection::mouse(int id) 
	{
		return m_instance->getMouseList().at(id);
	}

	Joystick* InputDetection::joystick(int id) 
	{
		return m_instance->getJoystickList().at(id);
	}

	Tablet* InputDetection::tablet(int id) 
	{
		return m_instance->getTabletList().at(id);
	}

	InputDevice* InputDetection::input(int id) 
	{
		return m_instance->getInputList().at(id);
	}	
}

#include "inputdetection.moc"

#include "detect.h"

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
	template<> GLUON_INPUT_EXPORT Detect *GluonCore::Singleton<Detect>::m_instance = 0;
	
	Detect::Detect()
	{
		this->init();
	}

	Detect::~Detect()
	{
	}

	void Detect::init()
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
		DetectMac* k = new DetectMac(parent);
		m_instance =(DetectAbstract*)k;
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

	void Detect::searchDevice()
	{    
		m_instance->searchDevice();
	}

	void Detect::setAllEnable()
	{
		m_instance->setAllEnabled();
	}

	void Detect::setAllDisable()
	{
		m_instance->setAllDisabled();
	}   

	unsigned int Detect::deviceCount() 
	{
		return inputList().size();
	}

	unsigned int Detect::keyboardCount() 
	{
		return m_instance->getKeyboardList().size();
	}

	unsigned int Detect::mouseCount() 
	{
		return m_instance->getMouseList().size();
	}

	unsigned int Detect::joystickCount() 
	{
		return m_instance->getJoystickList().size();
	}

	unsigned int Detect::tabletCount() 
	{
		return m_instance->getTabletList().size();
	}

	unsigned int Detect::unknownDeviceCount() 
	{
		return m_instance->getUnknownDeviceList().size();
	}

	QList<KeyBoard*> Detect::keyboardList() 
	{
		return m_instance->getKeyboardList();
	}

	QList<Mouse*> Detect::mouseList()
	{
		return m_instance->getMouseList();
	}

	QList<Joystick*> Detect::joystickList()
	{
		return m_instance->getJoystickList();
	}

	QList<Tablet*> Detect::tabletList() 
	{
		return m_instance->getTabletList();
	}

	QList<InputDevice*> Detect::unknownDeviceList() 
	{
		return m_instance->getUnknownDeviceList();
	}

	InputList Detect::inputList() 
	{
		return m_instance->getInputList();
	}

	KeyBoard* Detect::keyboard(int id) 
	{
		return m_instance->getKeyboardList().at(id);
	}

	Mouse* Detect::mouse(int id) 
	{
		return m_instance->getMouseList().at(id);
	}

	Joystick* Detect::joystick(int id) 
	{
		return m_instance->getJoystickList().at(id);
	}

	Tablet* Detect::tablet(int id) 
	{
		return m_instance->getTabletList().at(id);
	}

	InputDevice* Detect::input(int id) 
	{
		return m_instance->getInputList().at(id);
	}	
}

#include "detect.moc"

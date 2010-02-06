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
	DetectAbstract * Detect::m_instance = NULL;

	Detect::Detect(QObject * parent)
			: QObject(parent)
	{
	}

	Detect::~Detect()
	{
		//    qDebug()<<"clear device...";
		//    foreach ( KCLInput * input, m_inputList)
		//    {
		//        delete input;
		//    }
	}

	void Detect::init()
	{
		if (!m_instance) 
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
	}

	void Detect::searchDevice()
	{    
		if(!m_instance)
		{
			init();
		}
		else
		{
			m_instance->searchDevice();
		}
	}

	void Detect::setAllEnable()
	{
		init();
		m_instance->setAllEnabled();
	}

	void Detect::setAllDisable()
	{
		init();
		m_instance->setAllDisabled();
	}   

	unsigned int Detect::deviceCount() 
	{
		qDebug() << "Checking if instance exists";
		init();
		qDebug() << "Accessing Inputlist";
		return inputList().size();
	}

	unsigned int Detect::keyboardCount() 
	{
		init();
		return m_instance->getKeyboardList().size();
	}

	unsigned int Detect::mouseCount() 
	{
		init();
		return m_instance->getMouseList().size();
	}

	unsigned int Detect::joystickCount() 
	{
		init();
		return m_instance->getJoystickList().size();
	}

	unsigned int Detect::tabletCount() 
	{
		init();
		return m_instance->getTabletList().size();
	}

	unsigned int Detect::unknownDeviceCount() 
	{
		init();
		return m_instance->getUnknownDeviceList().size();
	}

	QList<KeyBoard*> Detect::keyboardList() 
	{
		init();
		return m_instance->getKeyboardList();
	}

	QList<Mouse*> Detect::mouseList()
	{
		init();
		return m_instance->getMouseList();
	}

	QList<Joystick*> Detect::joystickList()
	{
		init();
		return m_instance->getJoystickList();
	}

	QList<Tablet*> Detect::tabletList() 
	{
		init();
		return m_instance->getTabletList();
	}

	QList<InputDevice*> Detect::unknownDeviceList() 
	{
		init();
		return m_instance->getUnknownDeviceList();
	}

	InputList Detect::inputList() 
	{
		init();
		return m_instance->getInputList();
	}

	KeyBoard* Detect::keyboard(int id) 
	{
		init();
		return m_instance->getKeyboardList().at(id);
	}

	Mouse* Detect::mouse(int id) 
	{
		init();
		return m_instance->getMouseList().at(id);
	}

	Joystick* Detect::joystick(int id) 
	{
		init();
		return m_instance->getJoystickList().at(id);
	}

	Tablet* Detect::tablet(int id) 
	{
		init();
		return m_instance->getTabletList().at(id);
	}

	InputDevice* Detect::input(int id) 
	{
		init();
		return m_instance->getInputList().at(id);
	}	
}

#include "detect.moc"

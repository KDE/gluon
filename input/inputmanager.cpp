#include "inputmanager.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include "inputmanagerprivate.h"

#ifdef Q_WS_X11
#include "detectlinux.h"
#endif

#ifdef Q_WS_MAC
#include "detectmac.h"
#endif

#ifdef Q_WS_WIN
#include "detectwin.h"
#endif

using namespace GluonInput;

template<> GLUON_INPUT_EXPORT InputManager *GluonCore::Singleton<InputManager>::m_instance = 0;

InputManager::InputManager()
{
	d = new InputManagerPrivate();
	this->init();
}

InputManager::~InputManager()
{
}

void InputManager::init()
{
	qDebug() << "Setting parent";
	QObject *parent = QCoreApplication::instance();
	if (!parent) {
		qDebug() << "No QCoreApplication instance found, the InputManager instance may be leaked when leaving";
	}

#ifdef Q_WS_X11
	qDebug() << "Creating instance: Linux";
	d->m_instance = new DetectLinux(parent);
#endif

#ifdef Q_WS_MAC
	qDebug() << "Creating instance: Mac";
	d->m_instance = new DetectMac(parent);
#endif

#ifdef Q_WS_WIN
	qDebug() << "Creating instance: Win";
	d->m_instance = new DetectWin(parent);
#endif
	if(d->m_instance)
	{
		qDebug() << "Instance created, searching devices";
		d->m_instance->searchDevice();
	}
	else
		qDebug() << "Instance not created, fail!";
}

void InputManager::searchDevice()
{
	d->m_instance->searchDevice();
}

void InputManager::setAllEnable()
{
	d->m_instance->setAllEnabled();
}

void InputManager::setAllDisable()
{
	d->m_instance->setAllDisabled();
}

unsigned int InputManager::deviceCount()
{
	return inputList().size();
}

unsigned int InputManager::keyboardCount()
{
	return d->m_instance->getKeyboardList().size();
}

unsigned int InputManager::mouseCount()
{
	return d->m_instance->getMouseList().size();
}

unsigned int InputManager::joystickCount()
{
	return d->m_instance->getJoystickList().size();
}

unsigned int InputManager::tabletCount()
{
	return d->m_instance->getTabletList().size();
}

unsigned int InputManager::unknownDeviceCount()
{
	return d->m_instance->getUnknownDeviceList().size();
}

QList<Keyboard*> InputManager::keyboardList()
{
	return d->m_instance->getKeyboardList();
}

QList<Mouse*> InputManager::mouseList()
{
	return d->m_instance->getMouseList();
}

QList<Joystick*> InputManager::joystickList()
{
	return d->m_instance->getJoystickList();
}

QList<Tablet*> InputManager::tabletList()
{
	return d->m_instance->getTabletList();
}

QList<InputDevice*> InputManager::unknownDeviceList()
{
	return d->m_instance->getUnknownDeviceList();
}

InputList InputManager::inputList()
{
	return d->m_instance->getInputList();
}

Keyboard* InputManager::keyboard(int id)
{
	return d->m_instance->getKeyboardList().at(id);
}

Mouse* InputManager::mouse(int id)
{
	return d->m_instance->getMouseList().at(id);
}

Joystick* InputManager::joystick(int id)
{
	return d->m_instance->getJoystickList().at(id);
}

Tablet* InputManager::tablet(int id)
{
	return d->m_instance->getTabletList().at(id);
}

InputDevice* InputManager::input(int id)
{
	return d->m_instance->getInputList().at(id);
}

#include "inputmanager.moc"


#include "linuxthread.h"

#include "inputevent.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QEvent>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>

#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array) ((array[LONG(bit)] >> OFF(bit)) & 1)

namespace GluonInput
{
	LinuxThread::LinuxThread(const QString &devicePath, QObject * parent)
		: ThreadAbstract(parent)
	{
		m_devicePath = devicePath;
		openDevice(devicePath);
	}

	void LinuxThread::run()
	{
		while (1) {
			struct input_event ev;
			int rd = read(m_fd, &ev, sizeof(struct input_event));
			if (rd < (int) sizeof(struct input_event)) {
				qDebug() << "Could not read input";
			} else {
				InputEvent *event = new InputEvent(ev.code, ev.value, QEvent::Type(QEvent::User+ev.type));
				QCoreApplication::sendEvent(parent(),event);
			}
		}
	}

	bool LinuxThread::openDevice(const QString& devicePath)
	{
		m_fd = -1;
		if ((m_fd = open(devicePath.toUtf8(), O_RDONLY)) < 0) {
			qDebug() << "Could not read device";
			return false;
		}
		return true;
	}
	
	void LinuxThread::setEnabled()
	{
		if(!m_enabled)
		{
			this->run();
			m_enabled = true;
		}
	}
	
	void LinuxThread::setDisabled()
	{
		if(m_enabled)
		{
			this->stop();
			m_enabled = false;
		}
	}
	
	void LinuxThread::readInformation()
	{
		if (!QFile::exists(m_devicePath)) {
			qDebug() << "m_devicePath does not exist";
			m_error = true;
			m_msgError += "device url does not exist \n";
			return;
		}
		
		int m_fd = -1;
		if ((m_fd = open(m_devicePath.toUtf8(), O_RDONLY)) < 0) {
			qDebug() << "Could not open device" << m_devicePath;
			m_error = true;
			m_msgError += "could not open the device \n";
			return;
		}
		
		if (ioctl(m_fd, EVIOCGID, &m_device_info)) {
			qDebug() << "Could not retrieve information of device" << m_devicePath;
			m_msgError += "could not retrieve information of device\n";
			m_error = true;
			return;
		}
		
		char name[256] = "Unknown";
		if (ioctl(m_fd, EVIOCGNAME(sizeof(name)), name) < 0) {
			qDebug() << "could not retrieve name of device" << m_devicePath;
			//        m_msgError += "cannot retrieve name of device\n";
			//        m_error = true;
		}
		
		m_deviceName = QString(name);
		///this next bit can be shared across platform
		unsigned long bit[EV_MAX][NBITS(KEY_MAX)];
		int abs[5];
		memset(bit, 0, sizeof(bit));
		ioctl(m_fd, EVIOCGBIT(0, EV_MAX), bit[0]);
		
		m_buttonCapabilities.clear();
		m_absAxisInfos.clear();
		
		for (int i = 0; i < EV_MAX; i++) {
			if (test_bit(i, bit[0])) {
				if (!i) {
					continue;
				}
				
				ioctl(m_fd, EVIOCGBIT(i, KEY_MAX), bit[i]);
				for (int j = 0; j < KEY_MAX; j++) {
					if (test_bit(j, bit[i])) {
						if (i == EV_KEY) {
							m_buttonCapabilities.append(j);
						}
						
						if (i == EV_REL) {
							m_relAxisCapabilities.append(j);
						}
						
						if (i == EV_ABS) {
							ioctl(m_fd, EVIOCGABS(j), abs);
							AbsVal cabs(0, 0, 0, 0);
							for (int k = 0; k < 5; k++) {
								if ((k < 3) || abs[k]) {
									switch (k) {
										case 0:
											cabs.value = abs[k];
											break;
										case 1:
											cabs.min = abs[k];
											break;
										case 2:
											cabs.max = abs[k];
											break;
										case 3:
											cabs.fuzz = abs[k];
											break;
										case 4:
											cabs.flat = abs[k];
											break;
									}
								}
							}
							m_absAxisCapabilities.append(j);
							m_absAxisInfos[j] = cabs;
						}
					}
				}
			}
		}
		
		//===============Find Force feedback ?? ===============
		
		close(m_fd);
		
		m_deviceType = GluonInput::UnknownDevice;
		
		if (m_buttonCapabilities.contains(BTN_STYLUS)) {
			m_deviceType  = GluonInput::TabletDevice;
		}
		
		if (m_buttonCapabilities.contains(BTN_STYLUS)
			|| m_buttonCapabilities.contains(ABS_PRESSURE)) {
			m_deviceType  = GluonInput::MouseDevice;
		}
		
		if (m_buttonCapabilities.contains(BTN_TRIGGER)) {
			m_deviceType  = GluonInput::JoystickDevice;
		}
		
		if (m_buttonCapabilities.contains(BTN_MOUSE)) {
			m_deviceType  = GluonInput::MouseDevice;
		}
		
		if (m_buttonCapabilities.contains(KEY_ESC)) {
			m_deviceType  = GluonInput::KeyBoardDevice;
		}
	}
	
	int LinuxThread::getJoystickXAxis()
	{
		return ABS_X;
	}
	
	int LinuxThread::getJoystickYAxis()
	{
		return ABS_Y;
	}
	
	int LinuxThread::getJoystickZAxis()
	{
		return ABS_Z;
	}
}
#include "linuxthread.moc"

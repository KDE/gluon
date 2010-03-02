#include "threadabstract.h"

namespace GluonInput
{
	ThreadAbstract::ThreadAbstract(QObject * parent) : QThread(parent)
	{
		m_error = false;
		m_enabled = false;
		m_msgError = QString();
		m_deviceName = "Unknown";
	}
	
	ThreadAbstract::~ThreadAbstract()
	{
	}
	
	void ThreadAbstract::run()
	{
		this->exec();
	}
	
	void ThreadAbstract::stop()
	{
		this->quit();
	}
	
	int ThreadAbstract::vendor()const
	{
		return m_vendor;
	}
	
	int ThreadAbstract::product()const
	{
		return m_product;
	}
	
	int ThreadAbstract::version()const
	{
		return m_version;
	}
	
	int ThreadAbstract::bustype()const
	{
		return m_bustype;
	}
	
	QList<int> ThreadAbstract::buttonCapabilities()const
	{
		return m_buttonCapabilities;
	}
	
	QList<int> ThreadAbstract::absAxisCapabilities()const
	{
		return m_absAxisCapabilities;
	}
	
	QList<int> ThreadAbstract::relAxisCapabilities()const
	{
		return m_relAxisCapabilities;
	}
	
	AbsVal ThreadAbstract::axisInfo(int axisCode)const
	{
		return m_absAxisInfos[axisCode];
	}
	
	const QString ThreadAbstract::deviceName() const
	{
		return m_deviceName;
	}
	
	GluonInput::DeviceFlag ThreadAbstract::deviceType()const
	{
		return m_deviceType;
	}
	
	void ThreadAbstract::setEnabled()
	{
	}
	
	void ThreadAbstract::setDisabled()
	{
	}
	
	bool ThreadAbstract::isEnabled() const
	{
		return m_enabled;
	}
	
	bool ThreadAbstract::error()
	{
		return m_error;
	}
	
	
	QString ThreadAbstract::msgError()
	{
		return m_msgError;
	}
	
	void ThreadAbstract::readInformation()
	{
	}
	
	int ThreadAbstract::getJoystickXAxis()
	{
	}
	
	int ThreadAbstract::getJoystickYAxis()
	{
	}
	
	int ThreadAbstract::getJoystickZAxis()
	{
	}
}

#include "threadabstract.moc"
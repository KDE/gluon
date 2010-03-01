#ifndef LINUXTHREAD_H
#define LINUXTHREAD_H

#include <QtCore/QThread>

#include "gluon_input_export.h"
#include "threadabstract.h"
/**
 * \defgroup KCL KCL
 */
//@{

namespace GluonInput
{
	class GLUON_INPUT_EXPORT LinuxThread : public ThreadAbstract
	{
		Q_OBJECT

	public:
		LinuxThread(const QString& devicePath, QObject *parent = 0);
        ~LinuxThread() {
			close(m_fd);
		}
		void run();

		///
		const QString devicePath() const;
		void setEnabled();
		void setDisabled();
		int getJoystickXAxis();
		int getJoystickYAxis();
		int getJoystickZAxis();
		///

	protected:
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

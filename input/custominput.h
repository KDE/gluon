#ifndef CUSTOMINPUT_H
#define CUSTOMINPUT_H

#include "gluoninput.h"

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QPair>

namespace GluonInput
{
	class InputDevice;
	class InputEvent;

	class GLUONINPUTSHARED_EXPORT CustomInput : public QObject
	{
		Q_OBJECT
	public:
		CustomInput(QObject * parent=0);
		void setButton(const QString &name, InputDevice* input, int keyCode);
		void setButton(const QString &name);
		void remButton(const QString &name);
		void setAbsAxis(const QString &name, InputDevice * input, int axis);
		void setRelAxis(const QString &name, InputDevice* input, int axis);
		void remAbsAxis(const QString &name);
		void remRelAxis(const QString &name);

		QStringList buttonNameList();
		QStringList absAxisNameList();
		QStringList relAxisNameList();

		InputDevice * inputAt(const QString& name, GluonInput::InputTypeFlag type);
		int codeAt(const QString& name, GluonInput::InputTypeFlag type);

		bool button(const QString& name);
		int relAxisValue(const QString &name);
		int absAxisValue(const QString &name);

	signals:
		void buttonPressed(QString name);
		void buttonReleased(QString name);
		void absAxisChanged(QString name,int value);
		void relAxisChanged(QString name,int value);

	protected slots:
		 void inputEvent(InputEvent * event);


	private:
		QMap <QString,QPair<InputDevice*,int> > m_buttons;
		QMap <QString,QPair<InputDevice*,int> > m_absAxis;
		QMap <QString,QPair<InputDevice*,int> > m_relAxis;


	};
}

#endif // KCLCUSTOMINPUT_H

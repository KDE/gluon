#include "custominput.h"

#include "inputdevice.h"
#include <QtCore/QDebug>
#include <QtCore/QStringList>

namespace GluonInput
{
	CustomInput::CustomInput(QObject * parent)
				:QObject(parent)
	{


	}

	void CustomInput::setButton(const QString &name, InputDevice* input, int keyCode)
	{
		if (!input->buttonCapabilities().contains(keyCode))
		{
			qDebug()<<"Cannot find keyCode for this input...";
			return;
		}
		connect(input,SIGNAL(eventSent(InputEvent*)),this,SLOT(inputEvent(InputEvent*)));
		m_buttons.insert(name,qMakePair(input,keyCode));

	}

	void CustomInput::setButton(const QString &name)
	{
		InputDevice * input = new InputDevice();
		m_buttons.insert(name,qMakePair(input,0));
	}

	void CustomInput::setAbsAxis(const QString &name, InputDevice * input, int axis)
	{
	 if (!input->absAxisCapabilities().contains(axis))
		{
			qDebug()<<"Cannot find keyCode for this input...";
			return;
		}
		m_absAxis.insert(name,qMakePair(input,axis));
		connect(input,SIGNAL(eventSent(InputEvent*)),this,SLOT(inputEvent(InputEvent*)));
	}

	void CustomInput::setRelAxis(const QString &name, InputDevice* input, int axis)
	{
	 if (!input->relAxisCapabilities().contains(axis))
		{
			qDebug()<<"Cannot find keyCode for this input...";
			return;
		}
		m_absAxis.insert(name,qMakePair(input,axis));
		connect(input,SIGNAL(eventSent(InputEvent*)),this,SLOT(inputEvent(InputEvent*)));

	}
	
	void CustomInput::remButton(const QString &name)
	{
		if ( m_buttons.contains(name))
		{
			disconnect(m_buttons[name].first,SIGNAL(eventSent(InputEvent*)),this,SLOT(inputEvent(InputEvent*)));
			m_buttons.remove(name);
		}
	}
	
	void CustomInput::remAbsAxis(const QString &name)
	{
		if ( m_absAxis.contains(name))
		{
			disconnect(m_buttons[name].first,SIGNAL(eventSent(InputEvent*)),this,SLOT(inputEvent(InputEvent*)));
			m_absAxis.remove(name);
		}
	}
	
	void CustomInput::remRelAxis(const QString &name)
	{
		if ( m_relAxis.contains(name))
		{
			disconnect(m_buttons[name].first,SIGNAL(eventSent(InputEvent*)),this,SLOT(inputEvent(InputEvent*)));
			m_relAxis.remove(name);
		}
	}

	void CustomInput::inputEvent(InputEvent * event)
	{

		//-------------IF BUTTON------------
		if ( event->type() ==  QEvent::Type(GluonInput::Key))
		{
			QMapIterator  <QString,QPair<InputDevice*,int> >  i(m_buttons);
			while (i.hasNext())
			{
				i.next();
				if (( i.value().second == event->code()) && (i.value().first == qobject_cast<InputDevice*>(sender())))
				{
					if ( event->value() == 1)
						emit buttonPressed(i.key());

					if ( event->value() == 0)
						emit buttonReleased(i.key());
				}
			}
			return;
		}

		//-------------IF ABS AXIS-----------

		if ( event->type() ==  QEvent::Type(GluonInput::AbsoluAxis))
		{
			QMapIterator  <QString,QPair<InputDevice*,int> >  i(m_absAxis);
			while (i.hasNext())
			{
				i.next();
				if (( i.value().second == event->code()) && (i.value().first == qobject_cast<InputDevice*>(sender())))
				{
					emit absAxisChanged(i.key(),event->value());
				}
			}
			return;
		}

		//-------------IF REL AXIS------------
		if ( event->type() ==  QEvent::Type(GluonInput::RelativeAxis))
		{
			QMapIterator  <QString,QPair<InputDevice*,int> >  i(m_relAxis);
			while (i.hasNext())
			{
				i.next();
				if (( i.value().second == event->code()) && (i.value().first == qobject_cast<InputDevice*>(sender())))
				{
					emit relAxisChanged(i.key(),event->value());
				}
			}
		}
		return;
	}


	bool CustomInput::button(const QString& name)
	{
		if (m_buttons.contains(name))
			return m_buttons[name].first->button(m_buttons[name].second);
		else return false;
	}

	int CustomInput::relAxisValue(const QString &name)
	{
		if ( m_relAxis.contains(name))
			return m_relAxis[name].first->relAxisValue(m_relAxis[name].second);
		else return -1;


	}
	
	int CustomInput::absAxisValue(const QString &name)
	{
		if ( m_absAxis.contains(name))
			return m_absAxis[name].first->absAxisValue(m_absAxis[name].second);
		else return -1;
	}

	InputDevice* CustomInput::inputAt(const QString& name, GluonInput::InputTypeFlag type)
	{
		if ( type == GluonInput::Key)
			return m_buttons[name].first;

		if ( type == GluonInput::AbsoluAxis)
			return m_absAxis[name].first;

		if ( type == GluonInput::RelativeAxis)
			return m_relAxis[name].first;

		return NULL;
	}
	
	int CustomInput::codeAt(const QString& name, GluonInput::InputTypeFlag type)
	{

		if ( type == GluonInput::Key)
			return m_buttons[name].second;

		if ( type == GluonInput::AbsoluAxis)
			return m_absAxis[name].second;

		if ( type == GluonInput::RelativeAxis)
			return m_relAxis[name].second;

		return -1;

	}
	
	QStringList CustomInput::buttonNameList()
	{
		QStringList list;
		QMapIterator  <QString,QPair<InputDevice*,int> >  i(m_buttons);
		while (i.hasNext())
		{
			i.next();
			list<<i.key();
		}
		return list;
	}
	
	QStringList CustomInput::absAxisNameList()
	{
		QStringList list;
		QMapIterator  <QString,QPair<InputDevice*,int> >  i(m_absAxis);
		while (i.hasNext())
		{
			i.next();
			list<<i.key();
		}
		return list;
	}
	
	QStringList CustomInput::relAxisNameList()
	{
		QStringList list;
		QMapIterator  <QString,QPair<InputDevice*,int> >  i(m_relAxis);
		while (i.hasNext())
		{
			i.next();
			list<<i.key();
		}
		return list;
	}
}
#include "custominput.moc"
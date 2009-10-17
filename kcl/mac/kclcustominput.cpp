#include "kclcustominput.h"

#include <QDebug>
#include <QStringlist>

KCLCustomInput::KCLCustomInput(QObject * parent)
            :QObject(parent)
{


}


void KCLCustomInput::setButton(const QString &name, KCLInput* input, int keyCode)
{
    if (!input->buttonCapabilities().contains(keyCode))
    {
        qDebug()<<"Cannot find keyCode for this input...";
        return;
    }
    connect(input,SIGNAL(eventSent(KCLInputEvent*)),this,SLOT(inputEvent(KCLInputEvent*)));
    m_buttons.insert(name,qMakePair(input,keyCode));

}

void KCLCustomInput::setButton(const QString &name)
{
    KCLInput * input = new KCLInput();
    m_buttons.insert(name,qMakePair(input,0));
}

void KCLCustomInput::setAbsAxis(const QString &name, KCLInput * input, int axis)
{
 if (!input->absAxisCapabilities().contains(axis))
    {
        qDebug()<<"Cannot find keyCode for this input...";
        return;
    }
    m_absAxis.insert(name,qMakePair(input,axis));
    connect(input,SIGNAL(eventSent(KCLInputEvent*)),this,SLOT(inputEvent(KCLInputEvent*)));
}

void KCLCustomInput::setRelAxis(const QString &name,KCLInput* input, int axis)
{
 if (!input->relAxisCapabilities().contains(axis))
    {
        qDebug()<<"Cannot find keyCode for this input...";
        return;
    }
    m_absAxis.insert(name,qMakePair(input,axis));
    connect(input,SIGNAL(eventSent(KCLInputEvent*)),this,SLOT(inputEvent(KCLInputEvent*)));

}
void KCLCustomInput::remButton(const QString &name)
{
    if ( m_buttons.contains(name))
    {
        disconnect(m_buttons[name].first,SIGNAL(eventSent(KCLInputEvent*)),this,SLOT(inputEvent(KCLInputEvent*)));
        m_buttons.remove(name);
    }
}
void KCLCustomInput::remAbsAxis(const QString &name)
{
    if ( m_absAxis.contains(name))
    {
        disconnect(m_buttons[name].first,SIGNAL(eventSent(KCLInputEvent*)),this,SLOT(inputEvent(KCLInputEvent*)));
        m_absAxis.remove(name);
    }
}
void KCLCustomInput::remRelAxis(const QString &name)
{
    if ( m_relAxis.contains(name))
    {
        disconnect(m_buttons[name].first,SIGNAL(eventSent(KCLInputEvent*)),this,SLOT(inputEvent(KCLInputEvent*)));
        m_relAxis.remove(name);
    }
}

void KCLCustomInput::inputEvent(KCLInputEvent * event)
{

    //-------------IF BUTTON------------
    if ( event->type() ==  QEvent::Type(KCL::Key))
    {
        QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_buttons);
        while (i.hasNext())
        {
            i.next();
            if (( i.value().second == event->code()) && (i.value().first == qobject_cast<KCLInput*>(sender())))
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

    if ( event->type() ==  QEvent::Type(KCL::AbsoluAxis))
    {
        QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_absAxis);
        while (i.hasNext())
        {
            i.next();
            if (( i.value().second == event->code()) && (i.value().first == qobject_cast<KCLInput*>(sender())))
            {
                emit absAxisChanged(i.key(),event->value());
            }
        }
        return;
    }

    //-------------IF REL AXIS------------
    if ( event->type() ==  QEvent::Type(KCL::RelativeAxis))
    {
        QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_relAxis);
        while (i.hasNext())
        {
            i.next();
            if (( i.value().second == event->code()) && (i.value().first == qobject_cast<KCLInput*>(sender())))
            {
                emit relAxisChanged(i.key(),event->value());
            }
        }
    }
    return;
}


bool KCLCustomInput::button(const QString& name)
{
    if (m_buttons.contains(name))
        return m_buttons[name].first->button(m_buttons[name].second);
    else return false;
}

int KCLCustomInput::relAxisValue(const QString &name)
{
    if ( m_relAxis.contains(name))
        return m_relAxis[name].first->relAxisValue(m_relAxis[name].second);
    else return -1;


}
int KCLCustomInput::absAxisValue(const QString &name)
{
    if ( m_absAxis.contains(name))
        return m_absAxis[name].first->absAxisValue(m_absAxis[name].second);
    else return -1;
}

KCLInput *KCLCustomInput::inputAt(const QString& name, KCL::InputTypeFlag type)
{
    if ( type == KCL::Key)
        return m_buttons[name].first;

    if ( type == KCL::AbsoluAxis)
        return m_absAxis[name].first;

    if ( type == KCL::RelativeAxis)
        return m_relAxis[name].first;

    return NULL;
}
int KCLCustomInput::codeAt(const QString& name, KCL::InputTypeFlag type)
{

    if ( type == KCL::Key)
        return m_buttons[name].second;

    if ( type == KCL::AbsoluAxis)
        return m_absAxis[name].second;

    if ( type == KCL::RelativeAxis)
        return m_relAxis[name].second;

    return -1;

}
QStringList KCLCustomInput::buttonNameList()
{
    QStringList list;
    QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_buttons);
    while (i.hasNext())
    {
        i.next();
        list<<i.key();
    }
    return list;
}
QStringList KCLCustomInput::absAxisNameList()
{
    QStringList list;
    QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_absAxis);
    while (i.hasNext())
    {
        i.next();
        list<<i.key();
    }
    return list;
}
QStringList KCLCustomInput::relAxisNameList()
{
    QStringList list;
    QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_relAxis);
    while (i.hasNext())
    {
        i.next();
        list<<i.key();
    }
    return list;
}

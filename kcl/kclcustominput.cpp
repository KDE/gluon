#include "kclcustominput.h"
KCLCustomInput::KCLCustomInput(QObject * parent)
            :QObject(parent)
{


}
void KCLCustomInput::addButton(QString name, KCLInput* input, int keyCode)
{
    input->setEnable();
    connect(input,SIGNAL(buttonPressed(int)),this,SLOT(emitButtonPressed(int)));
    connect(input,SIGNAL(buttonPressed(int)),this,SLOT(emitButtonReleased(int)));

    m_buttons.insert(name,qMakePair(input,keyCode));

}
void KCLCustomInput::addButton(QString name)
{
    KCLInput * input = new KCLInput();
    m_buttons.insert(name,qMakePair(input,0));
}

void KCLCustomInput::addAbsAxis(QString name, KCLInput * input, int axis)
{
    input->setEnable();
    m_absAxis.insert(name,qMakePair(input,axis));
    connect(input,SIGNAL(absAxisChanged(int,int)),this,SLOT(emitAbsAxisChanged(int,int)));
}
void KCLCustomInput::addRelAxis(QString name,KCLInput* input, int axis)
{
    input->setEnable();
    m_absAxis.insert(name,qMakePair(input,axis));
    connect(input,SIGNAL(relAxisChanged(int,int)),this,SLOT(emitRelAxisChanged(int,int)));

}
void KCLCustomInput::emitButtonPressed(int code)
{
    kDebug()<<"click : "<<code;
    QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_buttons);
    while (i.hasNext())
    {
        i.next();
        if (( i.value().second == code) && (i.value().first == qobject_cast<KCLInput*>(sender())))
        {
            emit buttonPressed(i.key());
        }
    }
}
void KCLCustomInput::emitButtonReleased(int code)
{
    QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_buttons);
    while (i.hasNext())
    {
        i.next();
        if (( i.value().second == code) && (i.value().first == qobject_cast<KCLInput*>(sender())))
        {
            emit buttonReleased(i.key());
        }
    }
}

void KCLCustomInput::remButton(QString name)
{
    if ( m_buttons.contains(name))
    {
        disconnect(m_buttons[name].first,SIGNAL(buttonPressed(int)),this,SLOT(emitButtonPressed(int)));
        disconnect(m_buttons[name].first,SIGNAL(buttonReleased(int)),this,SLOT(emitButtonReleased(int)));
        m_buttons.remove(name);
    }
}
void KCLCustomInput::remAbsAxis(QString name)
{
    if ( m_absAxis.contains(name))
    {
        disconnect(m_absAxis[name].first,SIGNAL(absAxisChanged(int,int)),this,SLOT(emitAbsAxisChanged(int,int)));
        m_absAxis.remove(name);
    }
}
void KCLCustomInput::remRelAxis(QString name)
{
  if ( m_relAxis.contains(name))
    {
        disconnect(m_relAxis[name].first,SIGNAL(relAxisChanged(int,int)),this,SLOT(emitRelAxisChanged(int,int)));
        m_relAxis.remove(name);
    }
}
void KCLCustomInput::emitAbsAxisChanged(int axis, int value)
{
    QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_absAxis);
    while (i.hasNext())
    {
        i.next();
        if (( i.value().second == axis) && (i.value().first == qobject_cast<KCLInput*>(sender())))
        {
            emit absAxisChanged(i.key(),value);
        }
    }
}
void KCLCustomInput::emitRelAxisChanged(int axis, int value)
{
    QMapIterator  <QString,QPair<KCLInput*,int> >  i(m_relAxis);
    while (i.hasNext())
    {
        i.next();
        if (( i.value().second == axis) && (i.value().first == qobject_cast<KCLInput*>(sender())))
        {
            emit relAxisChanged(i.key(),value);
        }
    }
}

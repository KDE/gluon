#include "kclcustominput.h"
KCLCustomInput::KCLCustomInput(QObject * parent)
            :QObject(parent)
{


}
void KCLCustomInput::addButton(QString name, KCLInput* input, int keyCode)
{
    input->setEnable();
    connect(input,SIGNAL(buttonPressed(int)),this,SLOT(emitButtonPressed(int)));
    connect(input,SIGNAL(buttonPressed(int)),this,SLOT(test(int)));
    kDebug()<<input->deviceName();
    m_buttons.insert(name,qMakePair(input,keyCode));

}
void KCLCustomInput::addButton(QString name)
{
    KCLInput * input = new KCLInput();
    m_buttons.insert(name,qMakePair(input,0));
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
    kDebug()<<"click : "<<code;
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

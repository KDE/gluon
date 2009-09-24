#include "kclpressbutton.h"

KCLPressButton::KCLPressButton( QWidget * parent)
           :QPushButton(parent)
{
    m_detection=false;

    connect(this,SIGNAL(clicked()),this,SLOT(startDetection()));

    foreach ( KCLInput * input, KCLDetect::inputList())
    {
        connect(input,SIGNAL(eventSent(KCLInputEvent*)),this,SLOT(inputEvent(KCLInputEvent*)));
    }

    setText("press...");
}

void KCLPressButton::inputEvent(KCLInputEvent * event)
{
    if ( m_detection==true)
    {
        m_currentInput  = qobject_cast<KCLInput*>(sender());
        setIcon(KCLCode::iconDevice(m_currentInput->deviceType()));


        if ( event->type() == QEvent::Type(KCL::Key))
        {
            setText(KCLCode::buttonName(event->code()));
            m_detection = false;
            setEnabled(true);
            return;
        }

        if ( event->type() == QEvent::Type(KCL::AbsoluAxis))
        {
            setText(KCLCode::absAxisName(event->code()) + " (axis)");
            m_detection = false;
            setEnabled(true);
            return;
        }

        if ( event->type() == QEvent::Type(KCL::RelatifAxis))
        {
            setText(KCLCode::relAxisName(event->code())+ " (axis)");
            m_detection = false;
            setEnabled(true);
            return;
        }

    }

}
void KCLPressButton::startDetection()
{
    m_detection=true;
    setEnabled(false);
    setText("press...");

}

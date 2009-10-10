#include "kclpressbutton.h"

#include "kclcode.h"
#include "kcldetect.h"
#include "kclinputevent.h"

KCLPressButton::KCLPressButton( QWidget * parent)
           :QPushButton(parent)
{
    m_detection=false;
    m_buttonMode=false;
    m_absAxisMode=false;
    m_relAxisMode=false;
    m_code=-1;
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


        if ( m_buttonMode)
        {

            if ( event->type() == QEvent::Type(KCL::Key))
            {
                m_currentInput  = qobject_cast<KCLInput*>(sender());
                setIcon(KCLCode::iconDevice(m_currentInput->deviceType()));
                setText(KCLCode::buttonName(event->code()));
                m_detection = false;
                setEnabled(true);
                m_code=event->code();
                emit changed();
                return;
            }
        }

        if ( m_absAxisMode)
        {

            if ( event->type() == QEvent::Type(KCL::AbsoluAxis))
            {
                m_currentInput  = qobject_cast<KCLInput*>(sender());
                setIcon(KCLCode::iconDevice(m_currentInput->deviceType()));
                setText(KCLCode::absAxisName(event->code()) );
                m_detection = false;
                setEnabled(true);
                m_code=event->code();
                emit changed();
                return;
            }
        }

        if ( m_relAxisMode)
        {

            if ( event->type() == QEvent::Type(KCL::RelativeAxis))
            {
                m_currentInput  = qobject_cast<KCLInput*>(sender());
                setIcon(KCLCode::iconDevice(m_currentInput->deviceType()));
                setText(KCLCode::relAxisName(event->code()));
                m_detection = false;
                setEnabled(true);
                m_code=event->code();
                emit changed();
                return;
            }
        }
    }
}
void KCLPressButton::startDetection()
{
    m_detection=true;
    setEnabled(false);
    setText("press...");


}

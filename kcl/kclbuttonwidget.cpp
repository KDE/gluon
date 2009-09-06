#include "kclbuttonwidget.h"
#include <QHBoxLayout>
#include <KDebug>

KCLButtonWidget::KCLButtonWidget(QWidget * parent)
    :QWidget(parent)
{
    m_currentCode = 0;
    m_timer= new QTimer;
    m_timer->setInterval(20);
    m_detect = new KCLDetect(this);
    QHBoxLayout * layout = new QHBoxLayout;
    m_button = new KPushButton();
    m_changeButton = new KPushButton(KIcon("edit-clear-locationbar-rtl.png"),"");
    layout->addWidget(m_button);
    layout->addWidget(m_changeButton);
    setLayout(layout);

    clear();

    connect(m_timer,SIGNAL(timeout()),this,SLOT(waitButton()));
    connect(m_button,SIGNAL(clicked()),this,SLOT(startWaiting()));
    connect(m_changeButton,SIGNAL(clicked()),this,SLOT(clear()));
}

void KCLButtonWidget::waitButton()
{
    foreach ( KCLInput * input, m_detect->deviceList())
    {        int code  = input->anyPress();
        if ( code != 0)
        {

            m_button->setText(KCLCode::keyName(code));
            m_button->setToolTip(input->name());

            switch (input->deviceType())
            {
            case KCL_MOUSE: m_currentIcon = KIcon("input-mouse.png");break;
            case KCL_TOUCHPAD: m_currentIcon = KIcon("input-mouse.png");break;
            case KCL_KEYBOARD: m_currentIcon = KIcon("input-keyboard.png");break;
            case KCL_JOYSTICK: m_currentIcon = KIcon("input-gaming.png");break;
            case KCL_TABLET: m_currentIcon = KIcon("input-tablet.png");break;
            case KCL_UNKNOWN: m_currentIcon = KIcon("system-help.png");break;
            }
            m_button->setIcon(m_currentIcon);
            m_currentCode = code;
            m_currentInput = input;
            emit changed();
            endWaiting();
        }
    }
}

void KCLButtonWidget::startWaiting()
{
    m_timer->start();
    setEnabled(false);
    kDebug()<<"start wating...";
    foreach ( KCLInput * input, m_detect->deviceList())
        input->listen();
}
void KCLButtonWidget::endWaiting()
{
    m_timer->stop();
    setEnabled(true);
    kDebug()<<"end wating...";
    foreach ( KCLInput * input, m_detect->deviceList())
        input->unlisten();

}

void KCLButtonWidget::clear()
{
    m_currentIcon =KIcon("fork.png");
    m_button->setIcon(KIcon("fork.png"));
    m_button->setText("press a key");
}

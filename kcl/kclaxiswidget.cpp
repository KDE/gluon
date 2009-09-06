#include "kclaxiswidget.h"
#include <KPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QProgressBar>

KCLAxisWidget::KCLAxisWidget(QWidget *parent)
    :QWidget(parent)
{


    m_detect = new KCLDetect(this);
    m_currentInput = new KCLInput("");
    m_timer = new QTimer;
    m_timer->setInterval(20);
    m_currentAxis = 0;

    QHBoxLayout * layout = new QHBoxLayout;
    m_button = new SlidePushButton;
    QToolButton* m_changeButton = new QToolButton;
    m_changeButton->setIcon(KIcon("edit-clear-locationbar-rtl.png"));
    layout->addWidget(m_button);
    layout->addWidget(m_changeButton);
    setLayout(layout);
    clear();
    foreach ( KCLInput * input, m_detect->deviceList())
        input->listen();

    connect(m_timer,SIGNAL(timeout()),this,SLOT(waitButton()));
    connect(m_button,SIGNAL(clicked()),this,SLOT(startWaiting()));
    connect(m_changeButton,SIGNAL(clicked()),this,SLOT(clear()));
}


void KCLAxisWidget::waitButton()
{
    foreach ( KCLInput * input, m_detect->deviceList())
    {

        if (input->anyAbsMove())
        {
            int axis = input->lastAbsAxis();
            kDebug()<<"setAxis";
            m_currentInput = input;
            m_currentAxis = axis;
            m_button->setText(KCLCode::absoluName(axis));
            endWaiting();
        }
    }
}
void KCLAxisWidget::changeSlide(int axes,int value)
{
    if ( axes!=m_currentAxis)
        return;
    m_button->setRange(m_currentInput->axisInfo(m_currentAxis).min, m_currentInput->axisInfo(m_currentAxis).max);
    m_button->setValue(m_currentInput->absAxis(m_currentAxis));
    QString txt = KCLCode::absoluName(m_currentAxis)+"-"+ QString::number(m_currentInput->absAxis(m_currentAxis));
    m_button->setText(txt);
}
void KCLAxisWidget::startWaiting()
{

    m_timer->start();
    setEnabled(false);
    kDebug()<<"start wating...";
}

void KCLAxisWidget::endWaiting()
{
    m_timer->stop();
    setEnabled(true);
    m_button->setToolTip(m_currentInput->name());

    disconnect(m_currentInput,SIGNAL(absAxisChanged(int,int)),this,SLOT(changeSlide(int,int)));
    connect(m_currentInput,SIGNAL(absAxisChanged(int,int)),this,SLOT(changeSlide(int,int)));
    kDebug()<<"end wating...";
}

void KCLAxisWidget::clear()
{
    endWaiting();
    m_button->setValue(0);
    m_button->setIcon(KIcon("fork.png"));;
    m_button->setText("move any axis");


}

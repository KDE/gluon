#include "kclaxiswidget.h"
#include <KPushButton>
#include <QHBoxLayout>
KCLAxisWidget::KCLAxisWidget(QWidget *parent)
    :QWidget(parent)
{


    m_detect = new KCLDetect(this);
    m_timer = new QTimer;
    m_timer->setInterval(20);
    m_currentAxis = 0;
    QVBoxLayout * layout = new QVBoxLayout;
    QHBoxLayout * subLayout = new QHBoxLayout;


    m_valueLabel = new QLabel;
    m_valueLabel->setText("unknown");
    m_valueLabel->setAlignment(Qt::AlignHCenter);

    m_button = new KPushButton();
    m_slider = new QSlider(Qt::Horizontal);
    m_testButton = new KPushButton(KIcon(""),"test");
    KPushButton* m_changeButton = new KPushButton(KIcon("edit-clear-locationbar-rtl.png"),"");
    m_slider->setEnabled(false);
    subLayout->addWidget(m_button);
    subLayout->addWidget(m_changeButton);
    layout->addLayout(subLayout);
    layout->addWidget(m_slider);
    layout->addWidget(m_valueLabel);
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
        if ( input->anyMove())
        {
            kDebug()<<"setAxis";
            m_currentInput = input;
            m_button->setText(KCLCode::absoluName(input->lastAxisMove()));
            m_currentAxis = input->lastAxisMove();
            endWaiting();
        }
   }
}
void KCLAxisWidget::changeSlide(int axes,int value)
{

    m_slider->setRange(m_currentInput->axisCapability(m_currentAxis).min, m_currentInput->axisCapability(m_currentAxis).max);
    m_slider->setValue(m_currentInput->axisAbsolu(m_currentAxis));
    m_valueLabel->setText(QString::number(m_currentInput->axisAbsolu(m_currentAxis)));

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

    m_slider->disconnect(this,SLOT(changeSlide(int,int)));
    connect(m_currentInput,SIGNAL(absoluteAxisChanged(int,int)),this,SLOT(changeSlide(int,int)));
    kDebug()<<"end wating...";
}

void KCLAxisWidget::clear()
{
  m_button->setIcon(KIcon("transform-move.png"));;
    m_button->setText("press and move");
}

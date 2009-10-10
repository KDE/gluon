#include "kclinputwidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <KTitleWidget>
#include <KLocale>
KCLInputWidget::KCLInputWidget(KCLInput * input,QWidget * parent)
    :QWidget(parent)
{
    m_input=input;
    m_tableWidget=new QTableWidget;
    QVBoxLayout * layout = new QVBoxLayout;

    KTitleWidget * title = new KTitleWidget;
    title->setText(m_input->deviceName());
    title->setComment(m_input->devicePath());
    title->setPixmap(KIcon(KCLCode::iconDevice(m_input->deviceType())).pixmap(64,64));

    layout->addWidget(title);
    layout->addWidget(m_tableWidget);
    setLayout(layout);
    setupTable();
    connect(m_input,SIGNAL(eventSent(KCLInputEvent*)),this,SLOT(inputEvent(KCLInputEvent*)));
    setWindowIcon(KIcon(KCLCode::iconDevice(m_input->deviceType())));
    setWindowTitle(i18n("input seetings"));
}
void KCLInputWidget::setupTable()
{

    m_tableWidget->setColumnCount(2);
    m_tableWidget->setRowCount(m_input->absAxisCapabilities().size() + m_input->relAxisCapabilities().size() + 1);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_tableWidget->setAlternatingRowColors(true);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    m_tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("code"));
    m_tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("value"));
    m_tableWidget->verticalHeader()->hide();
    m_tableWidget->setItem(0,0,new QTableWidgetItem("button"));
    m_tableWidget->setItem(0,1,new QTableWidgetItem("?"));


    int row = 1;
    foreach ( int axis, m_input->absAxisCapabilities())
    {
        QTableWidgetItem * item = new QTableWidgetItem(KCLCode::absAxisName(axis));
        m_tableWidget->setItem(row,0,item);
        QSlider * slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(m_input->axisInfo(axis).min);
        slider->setMaximum(m_input->axisInfo(axis).max);
        slider->setValue(m_input->axisInfo(axis).value);
        m_tableWidget->setCellWidget(row,1,slider);
        row++;
    }

    foreach ( int axis, m_input->relAxisCapabilities())
    {
        QTableWidgetItem * item = new QTableWidgetItem(KCLCode::absAxisName(axis));
        m_tableWidget->setItem(row,0,item);
        QSlider * slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(0);
        slider->setMaximum(100);
        slider->setValue(50);
        m_tableWidget->setCellWidget(row,1,slider);
        row++;
    }

}

void KCLInputWidget::inputEvent(KCLInputEvent * event)
{

    switch (event->type())
    {

    case KCL::Key :
        m_tableWidget->item(0,1)->setText(KCLCode::buttonName(event->code()))   ;
        if ( event->value() == 1)
            m_tableWidget->item(0,1)->setBackgroundColor(QColor(0,0,255,100));
        else
            m_tableWidget->item(0,1)->setBackgroundColor(Qt::white);
        break;



    case KCL::AbsoluAxis :
        for ( int row = 1; row < m_tableWidget->rowCount(); ++row)
        {

            if ( m_tableWidget->item(row, 0)->text() == KCLCode::absAxisName(event->code()))
            {

                QSlider * slider =qobject_cast<QSlider*>( m_tableWidget->cellWidget(row,1));
                slider->setValue(event->value());
            }
        }
        break;

    case KCL::RelativeAxis:
        for ( int row = 1; row < m_tableWidget->rowCount(); ++row)
        {

            if ( m_tableWidget->item(row, 0)->text() == KCLCode::relAxisName(event->code()))
            {

                QSlider * slider =qobject_cast<QSlider*>( m_tableWidget->cellWidget(row,1));
                slider->setValue(slider->value()+event->value());
            }
        }
        break;

    default :break;




}




}

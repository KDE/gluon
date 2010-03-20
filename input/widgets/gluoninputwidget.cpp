#include "gluoninputwidget.h"

#include "input/code.h"
#include "input/absval.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHeaderView>
#include <QtCore/QDebug>

GluonInputWidget::GluonInputWidget(GluonInput::InputDevice * input, QWidget * parent)
        : QWidget(parent)
{
    m_input = input;
    m_tableWidget = new QTableWidget;
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(m_tableWidget);
    setLayout(layout);
    setupTable();
    connect(m_input, SIGNAL(eventSent(GluonInput::InputEvent*)), this, SLOT(inputEvent(GluonInput::InputEvent*)));

    m_input->setEnabled();
    setWindowTitle(tr("input settings"));
}
void GluonInputWidget::setupTable()
{

    m_tableWidget->setColumnCount(2);
    int nRows = m_input->absAxisCapabilities().size() + m_input->relAxisCapabilities().size();
    if (m_input->buttonCapabilities().size() > 0) nRows += 1;
    m_tableWidget->setRowCount(nRows);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_tableWidget->setAlternatingRowColors(true);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    m_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("code"));
    m_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("value"));
    m_tableWidget->verticalHeader()->hide();

    int row = 0;
    if (m_input->buttonCapabilities().size() > 0)
    {
        m_tableWidget->setItem(row, 0, new QTableWidgetItem(tr("Button")));
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(tr("?")));
        row++;
    }

    foreach(int axis, m_input->absAxisCapabilities())
    {
        QTableWidgetItem * item = new QTableWidgetItem(GluonInput::Code::absAxisName(axis));
        m_tableWidget->setItem(row, 0, item);
        QSlider * slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(m_input->axisInfo(axis).min);
        slider->setMaximum(m_input->axisInfo(axis).max);
        slider->setValue(m_input->axisInfo(axis).value);
        slider->setEnabled(false);
        m_tableWidget->setCellWidget(row, 1, slider);
        row++;
    }

    foreach(int axis, m_input->relAxisCapabilities())
    {
        QTableWidgetItem * item = new QTableWidgetItem(GluonInput::Code::absAxisName(axis));
        m_tableWidget->setItem(row, 0, item);
        QSlider * slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(0);
        slider->setMaximum(100);
        slider->setValue(50);
        slider->setEnabled(false);
        m_tableWidget->setCellWidget(row, 1, slider);
        row++;
    }

}

void GluonInputWidget::inputEvent(GluonInput::InputEvent * event)
{
    switch (event->type())
    {

        case GluonInput::Key :
            m_tableWidget->item(0, 1)->setText(GluonInput::Code::buttonName(event->code()))   ;
            if (event->value() == 1)
                m_tableWidget->item(0, 1)->setBackgroundColor(QColor(0, 0, 255, 100));
            else
                m_tableWidget->item(0, 1)->setBackgroundColor(Qt::white);
            break;



        case GluonInput::AbsoluAxis :
            for (int row = 1; row < m_tableWidget->rowCount(); ++row)
            {

                if (m_tableWidget->item(row, 0)->text() == GluonInput::Code::absAxisName(event->code()))
                {

                    QSlider * slider = qobject_cast<QSlider*>(m_tableWidget->cellWidget(row, 1));
                    slider->setValue(event->value());
                }
            }
            break;

        case GluonInput::RelativeAxis:
            for (int row = 1; row < m_tableWidget->rowCount(); ++row)
            {

                if (m_tableWidget->item(row, 0)->text() == GluonInput::Code::relAxisName(event->code()))
                {

                    QSlider * slider = qobject_cast<QSlider*>(m_tableWidget->cellWidget(row, 1));
                    slider->setValue(slider->value() + event->value());
                }
            }
            break;

        default :
            break;
    }
}

#include "gluoninputwidget.moc"

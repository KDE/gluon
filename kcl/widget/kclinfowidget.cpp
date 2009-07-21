#include "kclinfowidget.h"
#include <QVBoxLayout>
KCLInfoWidget::KCLInfoWidget(QWidget * parent)
        :QWidget(parent)
{


    QVBoxLayout * layout = new QVBoxLayout;

QLabel * label = new QLabel;
label->setText("KCL");

layout->addWidget(label);

    setLayout(layout);


}

#include "optionwidget.h"
#include <QVBoxLayout>
OptionWidget::OptionWidget(QWidget * parent)
    :QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;

    spriteRequester = new KUrlRequester;

    numberSpin = new QSpinBox;
    sizeSpin = new QSpinBox;
  angleSpin = new QSpinBox;
    speedSpin= new QDoubleSpinBox;
    alphaSpin= new QDoubleSpinBox;


    numberSpin->setRange(0,1000);
    sizeSpin->setRange(1,50);
    angleSpin->setRange(0,360);
    speedSpin->setRange(0.001,1);
    alphaSpin->setRange(0.001,1);

    numberSpin->setValue(10);
    sizeSpin->setValue(10);
    angleSpin->setValue(360);
    speedSpin->setValue(0.01);
    alphaSpin->setValue(0.01);





startButton = new QPushButton("Start");

    layout->addWidget(spriteRequester);
    layout->addWidget(numberSpin);
    layout->addWidget(sizeSpin);
    layout->addWidget(angleSpin);
    layout->addWidget(speedSpin);
    layout->addWidget(alphaSpin);

    layout->addWidget(startButton);

    setLayout(layout);


}

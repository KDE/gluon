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
typeCheckBox = new QCheckBox("Explose type ? ");

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



    speedSpin->setSingleStep(0.001);
    alphaSpin->setSingleStep(0.001);




startButton = new QPushButton("Start");

    layout->addWidget(spriteRequester);
        layout->addWidget(typeCheckBox);


        QLabel * n1= new QLabel("particles number...");
        layout->addWidget(n1);
    layout->addWidget(numberSpin);

       QLabel * n2= new QLabel("particules size...");
        layout->addWidget(n2);
    layout->addWidget(sizeSpin);

       QLabel * n3= new QLabel("angle ...");
        layout->addWidget(n3);
    layout->addWidget(angleSpin);

       QLabel * n4= new QLabel("particles speed...");
        layout->addWidget(n4);
    layout->addWidget(speedSpin);

       QLabel * n5= new QLabel("particles alpha step...");
        layout->addWidget(n5);
    layout->addWidget(alphaSpin);

    layout->addWidget(startButton);

    setLayout(layout);


}

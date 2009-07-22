
#ifndef OPTION_WIDGET_H
#define OPTION_WIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <KUrlRequester>
#include <QDoubleSpinBox>
#include <QSpinBox>

class OptionWidget : public QWidget
{
public : 
OptionWidget(QWidget * parent=0);


KUrlRequester * spriteRequester;

QSpinBox * numberSpin;
QSpinBox * sizeSpin;
QSpinBox *angleSpin;
QDoubleSpinBox *speedSpin;
QDoubleSpinBox  *alphaSpin;

QPushButton * startButton ;
};


#endif

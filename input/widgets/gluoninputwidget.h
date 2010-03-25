#ifndef KCLINPUTWIDGET_H
#define KCLINPUTWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QSlider>
#include <QtGui/QTableWidget>
#include <QtCore/QTimer>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>

#include "input/inputdevice.h"

class GluonInputWidget : public QWidget
{
        Q_OBJECT
    public:
        GluonInputWidget(GluonInput::InputDevice * input, QWidget * parent = 0);
	  
	void stuff();
    signals:
	void startTheLoop();
	
    protected:
        void setupTable();
	
    private slots:
	void startLoop();
	
    private:
        GluonInput::InputDevice * m_input;
        QTableWidget * m_tableWidget;
};

#endif // KCLINPUTWIDGET_H

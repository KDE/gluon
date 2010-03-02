#ifndef KCLINPUTWIDGET_H
#define KCLINPUTWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QSlider>
#include <QtGui/QTableWidget>
#include <QtCore/QTimer>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <gluon/input/inputdevice.h>
#include <gluon/input/inputevent.h>

class KCLInputWidget : public QWidget
{
    Q_OBJECT
public:
    KCLInputWidget(GluonInput::InputDevice * input, QWidget * parent=0);

protected:
    void setupTable();
    protected slots:
    void inputEvent(GluonInput::InputEvent * event);
private:
    GluonInput::InputDevice * m_input;
    QTableWidget * m_tableWidget;



};

#endif // KCLINPUTWIDGET_H

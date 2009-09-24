#ifndef KCLINPUTWIDGET_H
#define KCLINPUTWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QTableWidget>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "../kclinput.h"
class KCLInputWidget : public QWidget
{
    Q_OBJECT
public:
    KCLInputWidget(KCLInput * input, QWidget * parent=0);

protected:
    void setupTable();
    protected slots:
    void inputEvent(KCLInputEvent * event);
private:
    KCLInput * m_input;
    QTableWidget * m_tableWidget;



};

#endif // KCLINPUTWIDGET_H

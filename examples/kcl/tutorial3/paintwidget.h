#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPaintEvent>
#include <QPainter>
class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget * parent=0);

    protected slots:
    void mainLoop();

protected:
void paintEvent(QPaintEvent * event);
private:

    QTimer *timer;


};

#endif // PAINTWIDGET_H

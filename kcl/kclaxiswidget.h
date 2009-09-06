#ifndef KCLAXISWIDGET_H
#define KCLAXISWIDGET_H

#include <QWidget>
#include <KPushButton>
#include <QSlider>
#include <QLabel>
#include <QTimer>
#include "kcldetect.h"
class KCLAxisWidget : public QWidget
{
    Q_OBJECT
public:
    KCLAxisWidget(QWidget * parent=0);
public slots:
    void startWaiting();
    void clear();
private slots:
    void waitButton();
    void changeSlide(int axes,int value);
protected:
    void endWaiting();

private:
    KCLDetect * m_detect;
    KCLInput * m_currentInput;
    int m_currentAxis;
    KPushButton * m_button;
    KPushButton * m_testButton;
    QLabel * m_valueLabel;
    QSlider * m_slider;
    QTimer *m_timer;

};

#endif // KCLAXISWIDGET_H

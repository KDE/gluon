#ifndef KCLBUTTONWIDGET_H
#define KCLBUTTONWIDGET_H
#include <KPushButton>
#include <KIcon>
#include <QWidget>
#include <QTimer>
#include "kcldetect.h"
#include "kclcode.h"
class KCLButtonWidget : public QWidget
{
    Q_OBJECT
public:
    KCLButtonWidget(QWidget * parent=0);
    KCLInput * input(){return m_currentInput;}
    KIcon icon(){return m_currentIcon;}
    int buttonCode(){return m_currentCode;}
public slots:
    void startWaiting();
    void clear();
private slots:
    void waitButton();
    protected:
    void endWaiting();
    signals:
    void changed();
private:
    KPushButton * m_button;
KPushButton *m_changeButton;
    KCLDetect * m_detect;
    KCLInput * m_currentInput;
    KIcon  m_currentIcon;
    int m_currentCode;
    QTimer *m_timer;

};

#endif // KCLBUTTONWIDGET_H

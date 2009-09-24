#ifndef KCLPRESSBUTTON_H
#define KCLPRESSBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include "../kclinput.h"
#include "../kcldetect.h"
class KCLPressButton : public QPushButton
{
    Q_OBJECT
public:
    KCLPressButton(QWidget * parent=0);
    KCLInput * input(){return m_currentInput;}
    int code(){return m_code;}
    void setButtonDetect(bool v){
        m_buttonMode=v;
    }
    void setAbsAxisDetect(bool v){
        m_absAxisMode=v;
    }
    void setRelAxisDetect(bool v){
        m_relAxisMode=v;
    }

public slots:
    void startDetection();

    signals:
    void changed();
protected slots:
    void inputEvent(KCLInputEvent * event);



private:
    KCLInput * m_currentInput;
    bool m_detection;
    bool m_buttonMode;
    bool m_absAxisMode;
    bool m_relAxisMode;
    int m_code;
};

#endif // KCLPRESSBUTTON_H

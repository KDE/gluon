#ifndef KCLPRESSBUTTON_H
#define KCLPRESSBUTTON_H

#include <QPushButton>
#include "../kclinput.h"
#include "../kcldetect.h"
class KCLPressButton : public QPushButton
{
    Q_OBJECT
public:
    KCLPressButton(QWidget * parent=0);
   KCLInput * input(){return m_currentInput;}

    protected slots:
    void inputEvent(KCLInputEvent * event);
    void startDetection();
private:
    KCLInput * m_currentInput;
    bool m_detection;
};

#endif // KCLPRESSBUTTON_H

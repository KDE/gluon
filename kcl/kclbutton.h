#ifndef KCLRELAXISWIDGET_H
#define KCLRELAXISWIDGET_H

#include <QWidget>
#include <KIcon>
#include "slidepushbutton.h"
#include "kcl.h"
#include "kcldetect.h"
class KCLButton : public QWidget
{
    Q_OBJECT
public:

    KCLButton(KCL::InputTypeFlag inputType, QWidget * parent = 0);
    KIcon icon() {
        return m_currentIcon;
    }
    KCLInput * input() {
        if (m_inputType != NULL)return m_currentInput;else return NULL;
    }
    int code() {
        return m_currentCode;
    }




private slots:
    void clear();
    void changeButtonName(int axis, int value); //for axis
    void changeButtonName(int button); // for button
    void changeButtonValue(int axis, int value);
    void startDetect();

signals:
    void changed();

protected:
    void setDeviceIcon(KCL::DeviceFlag device);

private:
    SlidePushButton * m_button;
    KCLInput * m_currentInput;
    int m_value;
    int m_currentCode;
    KIcon m_currentIcon;
    KCL::InputTypeFlag m_inputType;


};

#endif // KCLRELAXISWIDGET_H

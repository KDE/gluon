#ifndef KCLINPUT_H
#define KCLINPUT_H

#include "kcl.h"
#include "kcl_export.h"
#include <QDebug>

#include <QMap>

class KCLInputEvent;
class KCLThread;

/**
 * \defgroup KCL KCL
 */
//@{

class KCLInput;
class KCL_EXPORT AbsVal
{
public:
    AbsVal(int v = 0, int m = 0, int M = 0, int f = 0, int F = 0) {
        value = v;
        min = m;
        max = M;
        flat = f;
        fuzz = F;
    }
    int value;
    int min;
    int max;
    int flat;
    int fuzz;
};

/**
 * @class KCLInput gluon/kcl/kclinput.h <Gluon/KCL/KCLInput>
 *
 * @short provide an object that represent an input.
 * This class represents an input device.
 * Use it to get information about an input and its current status
 * @author Sacha schutz <istdasklar@gmail.com>

 * @section creating Creating a KCLInput
 * The easiest way to create a usable KCLInput is to set it by the evdev file name.
 * @code
 * KCLInput *myInput = new KCLInput("/dev/input/event2");
 * qDebug() << myInput->name();
 * @endcode
 */

class KCL_EXPORT KCLInput : public QObject
{
    Q_OBJECT

public:
    KCLInput(const QString& devicePath=QString(), QObject * parent = 0);
    ~KCLInput();
    /**
    * @return the id of vendor
    */
    unsigned int vendor()const {
        return m_device_info.vendor;
    }

    /**
    * @return the id of product
    */

    unsigned int product()const {
        return m_device_info.product;
    }

    /**
    * @return the version driver of the device
    */
    unsigned int version()const {
        return m_device_info.version;
    }

    /**
    * @return the bus of the device
    */
    unsigned int bustype()const {
        return m_device_info.bustype;
    }

    const QString &devicePath()const {
        return m_devicePath;
    }

    /**
    * @return the name of the device
    */
    const QString &deviceName() const{
        return m_deviceName;
    }

    /**
    * @return the device type. KCL_KEYBOARD, KCL_MOUSE, KCL_JOYSTICK, KCL_TABLET, KCL_TOUCHPAD, KCL_UNKNOWN;
    * @see DEVICE
    */

   KCL::DeviceFlag deviceType()const {
        return m_deviceType;
    }

    /**
    * @return true if the button with code is pressed. Otherwise false
    * @code
    * KCLInput *myInput = new KCLInput("/dev/input/event3");
    * if (myInput->button(LeftBtn)) {
    *     qDebug() << "clicked";
    * }
    * @endcode
    * @see KCLInputEvent
    */
    bool button(int code)const {
        return m_buttons.contains(code);
    }

    /**
    * @return button code if a button is pressed. Otherwise 0
    * @code
    * KCLInput *myInput = new KCLInput("/dev/input/event3");
    * int pressedButton = myInput->anyPress();
    * if (pressedButton) {
    *     qDebug() << "button" << pressedButton << "was pressed.";
    * }
    * @endcode
    * @see KCLInputEvent
    */
    int anyPress() const {
        if (m_buttons.size() > 0) {
            return m_buttons.last();
        } else {
            return 0;
        }
    }

    /**
    * @return true if a motion is done by a motion input(mouse, joystick, ...)
    * @code
    * KCLInput *myInput = new KCLInput("/dev/input/event3");
    * if (myInput->anyMove()) {
    *     qDebug() << "Input was moved";
    * }
    * @endcode
    * @see KCLInputEvent
    */
//    bool anyMove(AXIS_TYPE a){if (a==KCL_ABSOLU) return anyAbsMove(); if (a==KCL_RELATIF) return anyRelMove();}

    bool anyAbsMove() {
        if (m_absMove) {
            m_absMove = false;
            return true;
        }
        return false;
    }

    bool anyRelMove() {
        if (m_relMove) {
            m_relMove = false;
            return true;
        }
        return false;
    }

    int lastAbsAxis()const {
        return m_lastAbsAxis;
    }

    int lastRelAxis()const {
        return m_lastRelAxis;
    }


    /**
    * @return the axis relative position. This is a relative value. For example the mouse return a relative position.
    * @see KCLInputEvent
    */
    int relAxisValue(int code)const {
        if (m_relAxis.contains(code)) {
            return m_relAxis[code];
        } else {
            return 0;
        }
    }

    /**
    * @return the axis absolute value. This is an absolue value. For example the Joystick return an absolu position.
    * @see KCLInputEvent
    */
    int absAxisValue(int code)const{
        if (m_absAxis.contains(code)) {
            return m_absAxis[code];
        } else {
            return 0;
        }
    }

    /**
    * @return a list of capability button input. For example the mouse will return a list with LeftBtn, RightBtn, etc.
    * @see KCLInputEvent
    */
    QList<int> buttonCapabilities()const {
        return m_buttonCapabilities;
    }

    QList<int> absAxisCapabilities()const {
        return m_absAxisCapabilities;
    }

    QList<int> relAxisCapabilities()const {
        return m_relAxisCapabilities;
    }

    /**
    * @return the axis capability. This is useful to know the capability of a joystick.
    * @see KCLInputEvent
    */
    AbsVal axisInfo(int axisCode)const {
        return m_absAxisInfos[axisCode];
    }

    bool error()const {
        return m_error;
    }

    QString msgError()const {
        return m_msgError;
    }




    bool isEnable() const{
        return m_enable;
    }
signals:
    void eventSent(KCLInputEvent * event);
    void buttonPressed(int code);
    void buttonReleased(int code);
    void absAxisChanged(int axe, int code);
    void relAxisChanged(int axe, int code);
    void pressed();
    void moved();

public slots:
    void setEnable();
    void setDisable();

protected:
    void readInformation();
    bool event(QEvent * evt);
private:    
    KCLThread *inputListener;
    struct input_id m_device_info;
    struct input_event m_currentEvent;
    QString m_devicePath;
    QString m_deviceName;
    KCL::DeviceFlag m_deviceType;

    QList<int> m_buttons;  //list of button pressed
    QList<int> m_forceFeedBack;
    QMap<int, int> m_relAxis; // list of relatif axis Value .  m_relAxis[REL_X] = -1;
    QMap<int, int> m_absAxis; // list of absolue axis value. m_absAxis[ABS_Rx] = 156
    QList<int> m_buttonCapabilities; // list of button capability. BTN_ESC, BTN_F1 etc....
    QList<int> m_relAxisCapabilities; // list of rel Axis capability..
    QList<int> m_absAxisCapabilities; // list of abs Axis capabilty
    QMap<int, AbsVal> m_absAxisInfos; // each Absolute Axis has a sub info called AbsVal. [ABS_RX] = AbsVal.
    QString m_msgError;
    bool m_absMove;
    bool m_relMove;
    bool m_error;
    int m_lastAbsAxis;
    int m_lastRelAxis;
    bool m_enable;
};

//@}
#endif // KCLINPUT_H

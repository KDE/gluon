#ifndef KCLINPUT_H
#define KCLINPUT_H

#include "kclcode.h"
#include "kcl.h"

#include <KDebug>

#include <QMap>
#include <QPair>
#include <QPoint>
#include <QThread>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/input.h>

class KCLInput;
class KCLThread;
class KCLInputEvent;

class AbsVal
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
 * @class KCLInputEvent gluon/kcl/kclinput.h <Gluon/KCL/KCLInput>
 *
 * @short Provides input events
 *
 * This class provide an event like QEvent ( but it's not a QEvent child) which contains all information of an input status
 *
 * @author Sacha Schutz <istdasklar@gmail.com>
 */

class KCLInputEvent
{
public:
    KCLInputEvent(unsigned long tvSec_, unsigned long tvUsec_, unsigned short type_, unsigned short code_, unsigned short value_);
    KCLInputEvent(struct input_event ev);

    unsigned long tvSec() {
        return m_inputEvent.time.tv_sec;
    }

    unsigned long tvUsec() {
        return m_inputEvent.time.tv_usec;
    }

    /**
    * For example, if you press a button, it will return EV_KEY.
    *If you move your mouse, it will return EV_REL. If you move your joystick it will return EV_ABS.
    * Please look in evdev type for more information
    * @return the type of the input status .
    */
    unsigned short type() {
        return m_inputEvent.type;
    }

    /**
    * For example the code of Mouse button left is : LeftBtn. Look on this page to see the code list.
    * @return  the code of the input status.
    */
    unsigned short code() {
        return m_inputEvent.code;
    }

    /**
    * For example the value after press a button is 1.
    * If you move an axis, the value will return the axis value.
    * @return the value of the input status.
    */
    unsigned int value() {
        return m_inputEvent.value;
    }

    /**
    * convert KCLInputEvent into a standard C input_event
    * @return an input_event
    */
    struct input_event inputEvent() {
        return m_inputEvent;
    }

private:
    struct input_event m_inputEvent;
};

/**
 * @class KCLThread gluon/kcl/kclinput.h <Gluon/KCL/KCLInput>
 *
 * @short Provides a QThread which listen to inputs status.
 * @author Sacha Schutz <istdasklar@gmail.com>
 */

class KCLThread : public QThread
{
    Q_OBJECT

public:
    KCLThread(const QString& devicePath, QObject *parent = 0);

    ~KCLThread() {
        close(m_fd);
    }

    virtual void run();

signals:
    /**
    * Emit a KCLInput. This signal is emited when somthing happens on a device.
    */
    void emitInputEvent(KCLInputEvent * event);

protected:
    bool openDevice(const QString &devicePath);
    void closeDevice() {
        close(m_fd);
    }

private:
    int m_fd;
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
 * kDebug() << myInput->name();
 * @endcode
 */

class KCLInput : public QObject
{
    Q_OBJECT

public:
    KCLInput(const QString& devicePath, QObject * parent = 0);
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
    unsigned int version() {
        return m_device_info.version;
    }

    /**
    * @return the bus of the device
    */
    unsigned int bustype()const {
        return m_device_info.bustype;
    }

    const QString &devicePath() {
        return m_devicePath;
    }

    /**
    * @return the name of the device
    */
    const QString &deviceName() {
        return m_deviceName;
    }

    /**
    * @return the device type. KCL_KEYBOARD, KCL_MOUSE, KCL_JOYSTICK, KCL_TABLET, KCL_TOUCHPAD, KCL_UNKNOWN;
    * @see DEVICE
    */
    const KCL::DeviceFlag &deviceType() {
        return m_deviceType;
    }

    /**
    * @return true if the button with code is pressed. Otherwise false
    * @code
    * KCLInput *myInput = new KCLInput("/dev/input/event3");
    * if (myInput->button(LeftBtn)) {
    *     kDebug() << "clicked";
    * }
    * @endcode
    * @see KCLInputEvent
    */
    bool button(int code) {
        return m_buttons.contains(code);
    }

    /**
    * @return button code if a button is pressed. Otherwise 0
    * @code
    * KCLInput *myInput = new KCLInput("/dev/input/event3");
    * int pressedButton = myInput->anyPress();
    * if (pressedButton) {
    *     kDebug() << "button" << pressedButton << "was pressed.";
    * }
    * @endcode
    * @see KCLInputEvent
    */
    int anyPress() {
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
    *     kDebug() << "Input was moved";
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

    int lastAbsAxis() {
        return m_lastAbsAxis;
    }

    int lastRelAxis() {
        return m_lastRelAxis;
    }


    /**
    * @return the axis relative position. This is a relative value. For example the mouse return a relative position.
    * @see KCLInputEvent
    */
    int relAxisValue(int code) {
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
    int absAxisValue(int code) {
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
    AbsVal axisInfo(int axisCode) {
        return m_absAxisInfos[axisCode];
    }

    bool error() {
        return m_error;
    }

    QString msgError() {
        return m_msgError;
    }

    /**
    * this function can be reimplemented to customize the event Loop.
     * @code
    * void MyInput::inputEventFilter(KCLInputEvent * event)
    * {
    *     switch (event->type())
    *     {
    *     case EV_KEY:
    *         //do something
    *         break;
    *     }
    * }
    * @endcode
    * @see KCLInputEvent
    */
    virtual void inputEventFilter(KCLInputEvent * event);

    bool isEnable() {
        return m_enable;
    }

signals:
    void buttonPressed(int code);
    void buttonReleased(int code);
    void absAxisChanged(int axe, int code);
    void relAxisChanged(int axe, int code);

public slots:
    void slotInputEvent(KCLInputEvent *event);
    void setEnable();
    void setDisable();

protected:
    void readInformation();

private:
    KCLThread *inputListener;
    struct input_id m_device_info;
    struct input_event m_currentEvent;
    QString m_devicePath;
    QString m_deviceName;
    KCL::DeviceFlag m_deviceType;

    QList<int> m_buttons;  //list of button pressed
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

#endif // KCLINPUT_H

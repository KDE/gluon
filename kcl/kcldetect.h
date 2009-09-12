#ifndef KCLDETECT_H
#define KCLDETECT_H
#include <QObject>
#include <QList>
#include <QCoreApplication>
#include "kclinput.h"
#include "kclkeyboard.h"
#include "kcljoystick.h"
#include "kclmouse.h"
#include "kcltablet.h"
#include "kclcode.h"

typedef QList<KCLInput*> KCLInputList;

class KCLDetect : public QObject
{
    Q_OBJECT
private:
    KCLDetect(QObject * parent);
    ~KCLDetect();

public:
    static KCLDetect * instance();
    static void searchDevice();
    static void setAllEnable();
    static void setAllDisable();

    static unsigned int deviceCount() {
        return allInputs().size();
    }
    static unsigned int keyboardCount() {
        return instance()->getKeyboardList().size();
    }
    static unsigned int mouseCount() {
        return instance()->getMouseList().size();
    }
    static unsigned int joystickCount() {
        return instance()->getJoystickList().size();
    }
    static unsigned int tabletCount() {
        return instance()->getTabletList().size();
    }
    static unsigned int unknownDeviceCount() {
        return instance()->getUnknownList().size();
    }



    static KCLKeyBoard * keyboard(int id = 0) {
        return instance()->getKeyboardList().at(id);
    }
    static KCLMouse * mouse(int id = 0) {
        return instance()->getMouseList().at(id);
    }
    static KCLJoystick * joystick(int id = 0) {
        return instance()->getJoystickList().at(id);
    }
    static KCLTablet * tablet(int id = 0) {
        return instance()->getTabletList().at(id);
    }

    static KCLInputList allInputs() {
        return instance()->getInputList();
    }


    //accesseur read only
    QList<KCLInput * > getInputList() {
        return m_inputList;
    }
    QList<KCLKeyBoard * > getKeyboardList() {
        return m_keyboardList;
    }
    QList<KCLMouse * > getMouseList() {
        return m_mouseList;
    }
    QList<KCLJoystick * > getJoystickList() {
        return m_joystickList;
    }
    QList<KCLTablet * > getTabletList() {
        return m_tabletList;
    }
    QList<KCLInput * > getUnknownList() {
        return m_unknownList;
    }

    void addInput(KCLInput * i) {
        m_inputList.append(i);
    }
    void addKeyboard(KCLKeyBoard* i) {
        m_keyboardList.append(i);
    }
    void addMouse(KCLMouse *i) {
        m_mouseList.append(i);
    }
    void addJoystick(KCLJoystick *i) {
        m_joystickList.append(i);
    }
    void addTablet(KCLTablet *i) {
        m_tabletList.append(i);
    }
    void addUnkwnown(KCLInput * i) {
        m_unknownList.append(i);
    }

    void clear();

private:
    static  KCLDetect * m_instance;
    QList<KCLInput * > m_inputList;
    QList<KCLKeyBoard * > m_keyboardList;
    QList<KCLMouse * > m_mouseList;
    QList<KCLJoystick * > m_joystickList;
    QList<KCLTablet * > m_tabletList;
    QList<KCLInput * > m_unknownList;


};

#endif // KCLDETECT_H

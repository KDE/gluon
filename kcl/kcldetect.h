#ifndef KCLDETECT_H
#define KCLDETECT_H

#include "kclcode.h"
#include "kclinput.h"
#include "kcljoystick.h"
#include "kclkeyboard.h"
#include "kclmouse.h"
#include "kcltablet.h"

#include <QObject>
#include <QList>

/**
 * \defgroup KCL KCL
 */
//@{

typedef QList<KCLInput *> KCLInputList;

class KCLDetect : public QObject
{
    Q_OBJECT

private:
    KCLDetect(QObject * parent);
    ~KCLDetect();

public:
    static KCLDetect *instance();
    static void searchDevice();
    static void setAllEnable();
    static void setAllDisable();

    static unsigned int deviceCount() {
        return inputList().size();
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
        return instance()->getUnknownDeviceList().size();
    }

    static QList <KCLKeyBoard*> keyboardList() {
        return instance()->getKeyboardList();
    }

    static QList <KCLMouse*> mouseList(){
        return instance()->getMouseList();
    }

    static QList <KCLJoystick*> joystickList(){
        return instance()->getJoystickList();
    }

    static QList <KCLTablet*> tabletList() {
        return instance()->getTabletList();
    }

    static QList <KCLInput*> unknownDeviceList() {
        return instance()->getUnknownDeviceList();
    }

    static KCLInputList inputList() {
        return instance()->getInputList();
    }

    static KCLKeyBoard *keyboard(int id = 0) {
        return instance()->getKeyboardList().at(id);
    }

    static KCLMouse *mouse(int id = 0) {
        return instance()->getMouseList().at(id);
    }

    static KCLJoystick *joystick(int id = 0) {
        return instance()->getJoystickList().at(id);
    }

    static KCLTablet *tablet(int id = 0) {
        return instance()->getTabletList().at(id);
    }

    static KCLInput * input(int id = 0){
    return instance()->getInputList().at(id);
    }


    //accesseur read only
    QList<KCLInput *> getInputList() {
        return m_inputList;
    }

    QList<KCLKeyBoard *> getKeyboardList() {
        return m_keyboardList;
    }

    QList<KCLMouse *> getMouseList() {
        return m_mouseList;
    }

    QList<KCLJoystick *> getJoystickList() {
        return m_joystickList;
    }

    QList<KCLTablet *> getTabletList() {
        return m_tabletList;
    }

    QList<KCLInput *> getUnknownDeviceList() {
        return m_unknownList;
    }

    void addInput(KCLInput *i) {
        m_inputList.append(i);
    }

    void addKeyboard(KCLInput *i) {
        KCLKeyBoard * keybd = new KCLKeyBoard(i->devicePath());
        keybd->setEnable();
        m_keyboardList.append(keybd);
    }

    void addMouse(KCLInput *i) {
        KCLMouse * mouse = new KCLMouse(i->devicePath());
        mouse->setEnable();
        m_mouseList.append(mouse);
    }

    void addJoystick(KCLInput *i) {
        KCLJoystick * joy = new KCLJoystick(i->devicePath());
        joy->setEnable();
        m_joystickList.append(joy);

    }

    void addTablet(KCLInput *i) {
        KCLTablet * tablet = new KCLTablet(i->devicePath());
        tablet->setEnable();
        m_tabletList.append(tablet);
    }

    void addUnknown(KCLInput *i) {
        m_unknownList.append(i);
    }

    void clear();

private:
    static  KCLDetect *m_instance;
    QList<KCLInput *> m_inputList;
    QList<KCLKeyBoard *> m_keyboardList;
    QList<KCLMouse *> m_mouseList;
    QList<KCLJoystick *> m_joystickList;
    QList<KCLTablet *> m_tabletList;
    QList<KCLInput *> m_unknownList;
};

//@}
#endif // KCLDETECT_H

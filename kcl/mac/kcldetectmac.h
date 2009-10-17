#ifndef KCLDETECTMAC_H
#define KCLDETECTMAC_H

#include "kclcode.h"
#include "kclinput.h"
#include "kcljoystick.h"
#include "../common/kcldetectabstract.h"

#include "kclkeyboard.h"
#include "kclmouse.h"
#include "kcltablet.h"

#include <QObject>
#include <QList>

class KCLDetectMac : public KCLDetectAbstract
{
    Q_OBJECT
    
private:
    KCLDetectMac(QObject * parent);
    ~KCLDetectMac();
    
public:
    void searchDevice();
    
    QList<KCLInput *> getInputList();    
    QList<KCLKeyBoard *> getKeyboardList();
    QList<KCLMouse *> getMouseList();
    QList<KCLJoystick *> getJoystickList();
    QList<KCLTablet *> getTabletList();
    QList<KCLInput *> getUnknownDeviceList();    
    
    void addInput(KCLInput *i);
    void addKeyboard(KCLInput *i);
    void addMouse(KCLInput *i);
    void addJoystick(KCLInput *i);
    void addTablet(KCLInput *i);
    void addUnknown(KCLInput *i);
    void clear();
    
private:
 /*   QList<KCLInput *> m_inputList;
    QList<KCLKeyBoard *> m_keyboardList;
    QList<KCLMouse *> m_mouseList;
    QList<KCLJoystick *> m_joystickList;
    QList<KCLTablet *> m_tabletList;
    QList<KCLInput *> m_unknownList;*/
};

#endif

#ifndef KCLDETECTABSTRACT_H
#define KCLDETECTABSTRACT_H

#include <QtCore/QObject>

#include "kcl_export.h"

class KCLJoystick;
class KCLMouse;
class KCLTablet;
class KCLKeyBoard;
class KCLInput;

class KCL_EXPORT KCLDetectAbstract : public QObject 
{
    Q_OBJECT

public:
    KCLDetectAbstract(QObject * parent = 0);
    
    virtual void searchDevice() = 0;
    virtual void setAllEnabled() = 0;
    virtual void setAllDisabled() = 0;
    
    virtual QList<KCLInput *> getInputList() = 0;    
    virtual QList<KCLKeyBoard *> getKeyboardList() = 0;
    virtual QList<KCLMouse *> getMouseList() = 0;
    virtual QList<KCLJoystick *> getJoystickList() = 0;
    virtual QList<KCLTablet *> getTabletList() = 0;
    virtual QList<KCLInput *> getUnknownDeviceList() = 0;    
    
    virtual void addInput(KCLInput *i) = 0;
    virtual void addKeyboard(KCLInput *i) = 0;
    virtual void addMouse(KCLInput *i) = 0;
    virtual void addJoystick(KCLInput *i) = 0;
    virtual void addTablet(KCLInput *i) = 0;
    virtual void addUnknown(KCLInput *i) = 0;
    virtual void clear() = 0;
    
protected:
    QList<KCLInput *> m_inputList;
    QList<KCLKeyBoard *> m_keyboardList;
    QList<KCLMouse *> m_mouseList;
    QList<KCLJoystick *> m_joystickList;
    QList<KCLTablet *> m_tabletList;
    QList<KCLInput *> m_unknownList;
    
};

#endif 
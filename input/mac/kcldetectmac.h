#ifndef KCLDETECTMAC_H
#define KCLDETECTMAC_H

#include "kclcode.h"
#include "kclinput.h"
#include "kcljoystick.h"
#include "kcldetectabstract.h"
#include "kclkeyboard.h"
#include "kclmouse.h"
#include "kcltablet.h"

#include <QtCore/QObject>
#include <QtCore/QList>

class KCL_EXPORT KCLDetectMac : public KCLDetectAbstract
{
    Q_OBJECT
    
public:
    KCLDetectMac(QObject * parent);
    ~KCLDetectMac();
    
    void searchDevice();
    void setAllEnabled();
    void setAllDisabled();
    
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
    static void createDevices(const void *value, void *context);
    CFMutableDictionaryRef createMatchingDictionary(UInt32 pUsagePage, UInt32 pUsage);
    
    IOHIDManagerRef deviceManager;
    CFSetRef devices;
};

#endif

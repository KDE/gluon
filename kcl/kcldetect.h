#ifndef KCLDETECT_H
#define KCLDETECT_H

#include "common/kcldetectabstract.h"
/*#ifdef _LINUX_
#include "linux/kcldetectlinux.h"
#elseifdef _APPLE_
#include "mac/kcldetectmac.h"
#elseifdef _WIN32
#include "win/kcldetectwin.h"
#endif*/

#include <QObject>
#include <QList>

class KCLInput;
class KCLJoystick;
class KCLKeyBoard;
class KCLMouse;
class KCLTablet;

typedef QList<KCLInput *> KCLInputList;

class KCLDetect : public QObject
{
    Q_OBJECT

private:
    KCLDetect(QObject * parent);
    ~KCLDetect();

public:
    static void searchDevice();
    static void setAllEnable();
    static void setAllDisable();

    static unsigned int deviceCount();

    static unsigned int keyboardCount();

    static unsigned int mouseCount();

    static unsigned int joystickCount();

    static unsigned int tabletCount();

    static unsigned int unknownDeviceCount();

    static QList <KCLKeyBoard*> keyboardList();

    static QList <KCLMouse*> mouseList();

    static QList <KCLJoystick*> joystickList();

    static QList <KCLTablet*> tabletList();

    static QList <KCLInput*> unknownDeviceList();

    static KCLInputList inputList();

    static KCLKeyBoard* keyboard(int id = 0);

    static KCLMouse* mouse(int id = 0);

    static KCLJoystick* joystick(int id = 0);

    static KCLTablet* tablet(int id = 0);

    static KCLInput* input(int id = 0);

private:
    static KCLDetectAbstract * m_instance;
    static void init();
    
/*#ifdef _LINUX_
    static  KCLDetectLinux *m_instance;
#endif
    
#ifdef _APPLE_
    static  KCLDetectMac *m_instance;
#endif
    
#ifdef _WIN32
    static  KCLDetectWin *m_instance;
#endif*/
};

#endif

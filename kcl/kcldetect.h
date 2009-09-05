#ifndef KCLDETECT_H
#define KCLDETECT_H
#include <QObject>
#include <QList>
#include "kclinput.h"
#include "kclkeyboard.h"
#include "kcljoystick.h"
#include "kclmouse.h"
#include "kcltablet.h"
#include "kclcode.h"
class KCLDetect : public QObject
{
    Q_OBJECT
public:
    KCLDetect(QObject * parent);
    ~KCLDetect();
    void searchDevice();
    unsigned int deviceNumber(){return m_inputList.size();}
    unsigned int keyboardNumber(){return m_keyboardList.size();}
    unsigned int mouseNumber(){return m_mouseList.size();}
    unsigned int joystickNumber(){return m_joystickList.size();}
    unsigned int tabletNumber(){return m_tabletList.size();}
    unsigned int unknownDeviceNumber(){return m_unknownList.size();}

    KCLKeyBoard * keyboard(int id=0)
    {
        if (m_keyboardList.size()<=0) return NULL;
        return dynamic_cast<KCLKeyBoard*>(m_keyboardList.at(id));
    }
    KCLMouse * mouse(int id=0)
    {
        if (m_mouseList.size()<=0) return NULL;
        return dynamic_cast<KCLMouse*>(m_mouseList.at(id));
    }
    KCLJoystick * joystick(int id=0)
    {
        if (m_joystickList.size()<=0) return NULL;
        return dynamic_cast<KCLJoystick*>(m_joystickList.at(id));
    }
    KCLTablet * tablet(int id=0)
    {
        if (m_tabletList.size()<=0) return NULL;
        return dynamic_cast<KCLTablet*>(m_tabletList.at(id));
    }

    QList<KCLInput * > deviceList(){return m_inputList;}

private:
    QList<KCLInput * > m_inputList;
    QList<KCLInput * > m_keyboardList;
    QList<KCLInput * > m_mouseList;
    QList<KCLInput * > m_joystickList;
    QList<KCLInput * > m_tabletList;
    QList<KCLInput * > m_unknownList;

};

#endif // KCLDETECT_H

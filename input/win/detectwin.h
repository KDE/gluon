#ifndef KCLDETECTWIN_H
#define KCLDETECTWIN_H

#include "kclcode.h"
#include "kclinput.h"
#include "kcljoystick.h"
#include "kclkeyboard.h"
#include "kclmouse.h"
#include "kcltablet.h"

#include <QObject>
#include <QList>

class KCL_EXPORT KCLDetectWin : public QObject
{
        Q_OBJECT

    private:
        KCLDetectWin(QObject * parent);
        ~KCLDetectWin();

    public:
        void searchDevice();

        QList<KCLInput *> getInputList()
        {
            return m_inputList;
        }

        QList<KCLKeyBoard *> getKeyboardList()
        {
            return m_keyboardList;
        }

        QList<KCLMouse *> getMouseList()
        {
            return m_mouseList;
        }

        QList<KCLJoystick *> getJoystickList()
        {
            return m_joystickList;
        }

        QList<KCLTablet *> getTabletList()
        {
            return m_tabletList;
        }

        QList<KCLInput *> getUnknownDeviceList()
        {
            return m_unknownList;
        }


        void addInput(KCLInput *i)
        {
            m_inputList.append(i);
        }

        void addKeyboard(KCLInput *i)
        {
            KCLKeyBoard * keybd = new KCLKeyBoard(i->devicePath());
            keybd->setEnable();
            m_keyboardList.append(keybd);
        }

        void addMouse(KCLInput *i)
        {
            KCLMouse * mouse = new KCLMouse(i->devicePath());
            mouse->setEnable();
            m_mouseList.append(mouse);
        }

        void addJoystick(KCLInput *i)
        {
            KCLJoystick * joy = new KCLJoystick(i->devicePath());
            joy->setEnable();
            m_joystickList.append(joy);

        }

        void addTablet(KCLInput *i)
        {
            KCLTablet * tablet = new KCLTablet(i->devicePath());
            tablet->setEnable();
            m_tabletList.append(tablet);
        }

        void addUnknown(KCLInput *i)
        {
            m_unknownList.append(i);
        }

        void clear();

    private:
        QList<KCLInput *> m_inputList;
        QList<KCLKeyBoard *> m_keyboardList;
        QList<KCLMouse *> m_mouseList;
        QList<KCLJoystick *> m_joystickList;
        QList<KCLTablet *> m_tabletList;
        QList<KCLInput *> m_unknownList;
};

#endif

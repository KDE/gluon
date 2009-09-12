#include "kclvirtualinput.h"

VirtualButton::VirtualButton(QString name, int buttonCode, KCLInput *input)
{
    m_name = name;
    m_buttonCode = buttonCode;
    m_input = input;
}

KCLVirtualInput::KCLVirtualInput(QObject *parent)
        : QObject(parent)
{
}

void KCLVirtualInput::setButton(QString name)
{
    kDebug() << "New virtual button:" << name;
    VirtualButton *button = new VirtualButton;
    button->setName(name);
    m_primaryButtonList.append(button);

    kDebug() << m_primaryButtonList.size();
}

#include "kclbutton.h"

#include <KDebug>


#include <QVBoxLayout>
#include <QToolButton>

KCLButton::KCLButton(KCL::InputTypeFlag inputType, QWidget * parent)
        : QWidget(parent)
{
    m_inputType = inputType;
    m_currentCode = -1;
    m_currentIcon = KIcon();
    m_value = 0;
    QHBoxLayout * layout = new QHBoxLayout;
    m_button = new SlidePushButton;
    QToolButton* m_changeButton = new QToolButton;
    m_changeButton->setIcon(KIcon("edit-clear-locationbar-rtl.png"));
    layout->addWidget(m_button);
    layout->addWidget(m_changeButton);
    setLayout(layout);
    KCLDetect::searchDevice();
    clear();
 
    if (m_inputType == KCL::RelatifAxis) {
        foreach(KCLInput *input, KCLDetect::allInputs()) {
            connect(input, SIGNAL(relAxisChanged(int, int)), this, SLOT(changeButtonValue(int, int)));
        }
    }

    if (m_inputType == KCL::AbsoluAxis) {
        foreach(KCLInput *input, KCLDetect::allInputs()) {
            connect(input, SIGNAL(absAxisChanged(int, int)), this, SLOT(changeButtonValue(int, int)));
        }
    }

    connect(m_button, SIGNAL(clicked()), this, SLOT(startDetect()));
    connect(m_changeButton, SIGNAL(clicked()), this, SLOT(clear()));
}

void KCLButton::changeButtonName(int axis, int value)
{
    kDebug() << "Button from axis changed";

    setEnabled(true);
    m_currentCode = axis;
    m_currentInput = qobject_cast<KCLInput*>(sender());
    m_button->setToolTip(m_currentInput->deviceName());
    setDeviceIcon(m_currentInput->deviceType());

    if (m_inputType == KCL::RelatifAxis) {
        m_button->setText(KCLCode::relAxisName(axis));
        foreach(KCLInput *input, KCLDetect::allInputs()) {
            disconnect(input, SIGNAL(relAxisChanged(int, int)), this, SLOT(changeButtonName(int, int)));
        }
    }

    if (m_inputType == KCL::AbsoluAxis) {
        m_button->setText(KCLCode::absAxisName(axis));
        foreach(KCLInput *input, KCLDetect::allInputs()) {
            disconnect(input, SIGNAL(absAxisChanged(int, int)), this, SLOT(changeButtonName(int, int)));
        }
    }

    emit changed();
}

void KCLButton::changeButtonName(int button)
{
    kDebug() << "Button changed";

    setEnabled(true);
    m_currentCode = button;
    m_currentInput = qobject_cast<KCLInput*>(sender());
    m_button->setToolTip(m_currentInput->deviceName());
    setDeviceIcon(m_currentInput->deviceType());
    m_button->setText(KCLCode::buttonName(button));

    foreach(KCLInput *input, KCLDetect::allInputs()) {
        disconnect(input, SIGNAL(buttonPressed(int)), this, SLOT(changeButtonName(int)));
    }

    emit changed();
}

void KCLButton::changeButtonValue(int axis, int value)
{
    if (m_currentCode == axis) {
        kDebug() << "rel axis changed";

        if (m_inputType == KCL::AbsoluAxis) {
            m_value = value;
            m_button->setRange(m_currentInput->axisInfo(m_currentCode).min, m_currentInput->axisInfo(m_currentCode).max);
            m_button->setValue(m_value);
        }

        if (m_inputType == KCL::RelatifAxis) {
            m_button->setRange(-50, 50);

            m_value += value;
            if ((m_value <= 50) && (m_value >= -50)) {
                m_button->setValue(m_value);
            }
        }
    }
}

void KCLButton::startDetect()
{
    kDebug() << "Detection started";

    setEnabled(false);

    if (m_inputType == KCL::AbsoluAxis) {
        foreach(KCLInput * input, KCLDetect::allInputs()) {
            connect(input, SIGNAL(absAxisChanged(int, int)), this, SLOT(changeButtonName(int, int)));
        }
    }

    if (m_inputType == KCL::RelatifAxis) {
        foreach(KCLInput *input, KCLDetect::allInputs()) {
            connect(input, SIGNAL(relAxisChanged(int, int)), this, SLOT(changeButtonName(int, int)));
        }
    }

    if (m_inputType == KCL::Key) {
        foreach(KCLInput *input, KCLDetect::allInputs()) {
            connect(input, SIGNAL(buttonPressed(int)), this, SLOT(changeButtonName(int)));
        }
    }

}

void KCLButton::setDeviceIcon(KCL::DeviceFlag device)
{
    switch (device) {
    case KCL::Mouse:
        m_currentIcon = KIcon("input-mouse.png");
        break;
    case KCL::Touchpad:
        m_currentIcon = KIcon("input-mouse.png");
        break;
    case KCL::KeyBoard:
        m_currentIcon = KIcon("input-keyboard.png");
        break;
    case KCL::Joystick:
        m_currentIcon = KIcon("input-gaming.png");
        break;
    case KCL::Tablet:
        m_currentIcon = KIcon("input-tablet.png");
        break;
    case KCL::Unknown:
        m_currentIcon = KIcon("system-help.png");
        break;
    }

    m_button->setIcon(m_currentIcon);
}

void KCLButton::clear()
{
    m_currentCode = -1;
    m_button->setEnabled(true);
    m_button->setIcon(KIcon("fork.png"));
    m_button->setValue(0);
    m_button->setText("Press..");
    disconnect(0, 0, this, SLOT(changeButtonName(int)));
    disconnect(0, 0, this, SLOT(changeButtonName(int, int)));
}

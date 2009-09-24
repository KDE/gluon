#include "kcldevicemodel.h"

#include <KIcon>
#include <KDebug>

#include <QMessageBox>

KCLDeviceModel::KCLDeviceModel(QObject *parent)
        : QStandardItemModel(parent)
{
    setColumnCount(2);
    setupList();
}

void KCLDeviceModel::setupList()
{
    clear();

    foreach(KCLInput *input, KCLDetect::inputList()) {
        QStandardItem *deviceItem = new QStandardItem;

        switch (input->deviceType()) {
        case KCL::KeyBoard :
            deviceItem = new QStandardItem(KIcon("input-keyboard.png"), input->deviceName());
            break;
        case KCL::Mouse:
            deviceItem = new QStandardItem(KIcon("input-mouse.png"), input->deviceName());
            break;
        case KCL::Touchpad:
            deviceItem = new QStandardItem(KIcon("input-mouse.png"), input->deviceName());
            break;
        case KCL::Joystick:
            deviceItem = new QStandardItem(KIcon("input-gaming.png"), input->deviceName());
            break;
        case KCL::Tablet :
            deviceItem = new QStandardItem(KIcon("input-tablet.png"), input->deviceName());
            break;
        case KCL::Unknown :
            deviceItem = new QStandardItem(KIcon("system-help.png"), input->deviceName());
            break;
        }

        appendRow(deviceItem);

        QStandardItem *info = new QStandardItem(KIcon("help-about.png"), input->devicePath());
        info->appendRow(new QStandardItem("Bus Type:" + QString::number(input->bustype())));
        info->appendRow(new QStandardItem("Product:" + QString::number(input->product())));
        info->appendRow(new QStandardItem("Version:" + QString::number(input->version())));
        info->appendRow(new QStandardItem("Vendor:" + QString::number(input->vendor())));
        deviceItem->appendRow(info);

        QStandardItem *button = new QStandardItem("Button");
        foreach(int code, input->buttonCapabilities()) {
            button->appendRow(new QStandardItem(KCLCode::buttonName(code)));
        }

        QStandardItem *absAxis = new QStandardItem("Absolute axis");
        foreach(int code, input->absAxisCapabilities()) {
            absAxis->appendRow(new QStandardItem(KCLCode::absAxisName(code)));
        }

        QStandardItem *relAxis = new QStandardItem("Relative axis");
        foreach(int code, input->relAxisCapabilities()) {
            relAxis->appendRow(new QStandardItem(KCLCode::relAxisName(code)));
        }

        QStandardItem *capab = new QStandardItem(KIcon("view-pim-tasks.png"), "Capability");

        if (input->buttonCapabilities().size() > 0)capab->appendRow(button);
        if (input->absAxisCapabilities().size() > 0)capab->appendRow(absAxis);
        if (input->relAxisCapabilities().size() > 0)capab->appendRow(relAxis);

        deviceItem->appendRow(capab);
    }

    //    addLine("mouse",KIcon("input-mouse.png"),KCL_MOUSE);
    //    addLine("keyboard",KIcon("input-keyboard.png"),KCL_KEYBOARD);
    //    addLine("joy/pad",KIcon("input-gaming.png"),KCL_JOYSTICK);
    //    addLine("tablet",KIcon("input-tablet.png"),KCL_TABLET);
    //    addLine("unknown",KIcon("system-help.png"),KCL_UNKNOWN);

}

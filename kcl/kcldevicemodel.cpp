#include "kcldevicemodel.h"
#include <KIcon>
#include <KDebug>
#include <QMessageBox>
KCLDeviceModel::KCLDeviceModel(QObject * parent)
    :QStandardItemModel(parent)
{

    setColumnCount(2);
    setupList();

}

void KCLDeviceModel::setupList()
{
    clear();
    m_detect = new KCLDetect(this);
    addLine("mouse",KIcon("input-mouse.png"),KCL_MOUSE);
    addLine("keyboard",KIcon("input-keyboard.png"),KCL_KEYBOARD);
    addLine("joy/pad",KIcon("input-gaming.png"),KCL_JOYSTICK);
    addLine("tablet",KIcon("input-tablet.png"),KCL_TABLET);
    addLine("unknown",KIcon("system-help.png"),KCL_UNKNOWN);

}

void KCLDeviceModel::addLine(QString text, KIcon icon, DEVICE device)
{

    QStandardItem * deviceItem= new QStandardItem(icon,text);
    appendRow(deviceItem);

    foreach ( KCLInput * input, m_detect->deviceList())
    {
        if (input->deviceType() == device)
        {
            QStandardItem * info = new QStandardItem(KIcon("help-about.png"),input->name());
            info->appendRow(new QStandardItem(input->device()));
            info->appendRow(new QStandardItem("busttype:"+QString::number(input->bustype())));
            info->appendRow(new QStandardItem("product:"+QString::number(input->product())));
            info->appendRow(new QStandardItem("version:"+QString::number(input->version())));
            info->appendRow(new QStandardItem("vendor:"+QString::number(input->vendor())));
            deviceItem->appendRow(info);

            QStandardItem * capab = new QStandardItem(KIcon("view-pim-tasks.png"),"capability");

            foreach ( int button, input->buttonCapabilities())
            {
                capab->appendRow(new QStandardItem(KCLCode::keyName(button)));
            }


            deviceItem->appendRow(capab);






        }
    }
}

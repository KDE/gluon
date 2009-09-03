#include "kcldevicemodel.h"
#include <KIcon>
#include <KDebug>
KCLDeviceModel::KCLDeviceModel(QObject * parent)
        :QStandardItemModel(parent)
{


setupList();

}

void KCLDeviceModel::setupList()
{

  m_kcl = new KCLEngine;


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
for ( int i=0; i<m_kcl->deviceList(device).size(); ++i)
{
    KCLInput * input = new KCLInput(m_kcl->deviceList(device).at(i));
QStandardItem * item = new QStandardItem(KIcon("go-next.png"),input->name());
deviceItem->appendRow(item);
}


}

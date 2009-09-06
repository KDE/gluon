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


    foreach ( KCLInput * input, m_detect->deviceList())
    {

        
        QStandardItem * deviceItem;

        switch ( input->deviceType())
        {

        case KCL_KEYBOARD :deviceItem = new QStandardItem(KIcon("input-keyboard.png"),input->name());break;
        case KCL_MOUSE:deviceItem = new QStandardItem(KIcon("input-mouse.png"),input->name());break;
        case KCL_TOUCHPAD:deviceItem = new QStandardItem(KIcon("input-mouse.png"),input->name());break;
        case KCL_JOYSTICK :deviceItem = new QStandardItem(KIcon("input-gaming.png"),input->name());break;
        case KCL_TABLET :deviceItem = new QStandardItem(KIcon("input-tablet.png"),input->name());break;
        case KCL_UNKNOWN :deviceItem = new QStandardItem(KIcon("system-help.png"),input->name());break;


        }

        appendRow(deviceItem);


        QStandardItem * info = new QStandardItem(KIcon("help-about.png"),input->device());
        info->appendRow(new QStandardItem("busttype:"+QString::number(input->bustype())));
        info->appendRow(new QStandardItem("product:"+QString::number(input->product())));
        info->appendRow(new QStandardItem("version:"+QString::number(input->version())));
        info->appendRow(new QStandardItem("vendor:"+QString::number(input->vendor())));
        deviceItem->appendRow(info);

        QStandardItem * button = new QStandardItem("button");
        foreach ( int code, input->buttonCapabilities())
            button->appendRow(new QStandardItem(KCLCode::keyName(code)));

        QStandardItem * absAxis = new QStandardItem("absolute axis");
        foreach ( int code, input->absAxisCapabilities())
            absAxis->appendRow(new QStandardItem(KCLCode::absoluName(code)));

        QStandardItem * relAxis = new QStandardItem("relativ axis");
        foreach ( int code, input->relAxisCapabilities())
            relAxis->appendRow(new QStandardItem(KCLCode::relativName(code)));

        QStandardItem * capab = new QStandardItem(KIcon("view-pim-tasks.png"),"capability");

        if ( input->buttonCapabilities().size()>0)capab->appendRow(button);
        if ( input->absAxisCapabilities().size()>0)capab->appendRow(absAxis);
        if ( input->relAxisCapabilities().size()>0)capab->appendRow(relAxis);

        deviceItem->appendRow(capab);






    }



    //    addLine("mouse",KIcon("input-mouse.png"),KCL_MOUSE);
    //    addLine("keyboard",KIcon("input-keyboard.png"),KCL_KEYBOARD);
    //    addLine("joy/pad",KIcon("input-gaming.png"),KCL_JOYSTICK);
    //    addLine("tablet",KIcon("input-tablet.png"),KCL_TABLET);
    //    addLine("unknown",KIcon("system-help.png"),KCL_UNKNOWN);

}

void KCLDeviceModel::addLine(QString text, KIcon icon, DEVICE device)
{

    QStandardItem * deviceItem= new QStandardItem(icon,text);
    appendRow(deviceItem);

    foreach ( KCLInput * input, m_detect->deviceList())
    {
        if (input->deviceType() == device)
        {
            QStandardItem * info = new QStandardItem(KIcon("go-next-view.png"),input->name());
            info->appendRow(new QStandardItem(input->device()));
            info->appendRow(new QStandardItem("busttype:"+QString::number(input->bustype())));
            info->appendRow(new QStandardItem("product:"+QString::number(input->product())));
            info->appendRow(new QStandardItem("version:"+QString::number(input->version())));
            info->appendRow(new QStandardItem("vendor:"+QString::number(input->vendor())));
            deviceItem->appendRow(info);

            QStandardItem * button = new QStandardItem("button");
            foreach ( int code, input->buttonCapabilities())
                button->appendRow(new QStandardItem(KCLCode::keyName(code)));

            QStandardItem * absAxis = new QStandardItem("absolute axis");
            foreach ( int code, input->absAxisCapabilities())
                absAxis->appendRow(new QStandardItem(KCLCode::absoluName(code)));

            QStandardItem * relAxis = new QStandardItem("relativ axis");
            foreach ( int code, input->relAxisCapabilities())
                relAxis->appendRow(new QStandardItem(KCLCode::relativName(code)));

            QStandardItem * capab = new QStandardItem(KIcon("view-pim-tasks.png"),"capability");

            if ( input->buttonCapabilities().size()>0)capab->appendRow(button);
            if ( input->absAxisCapabilities().size()>0)capab->appendRow(absAxis);
            if ( input->relAxisCapabilities().size()>0)capab->appendRow(relAxis);

            info->appendRow(capab);





        }
    }
}

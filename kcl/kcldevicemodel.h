#ifndef KCLDEVICEMODEL_H
#define KCLDEVICEMODEL_H

#include <QStandardItemModel>
#include <KIcon>
#include "kcldetect.h"

class KCLDeviceModel : public QStandardItemModel
{
public:
    KCLDeviceModel(QObject * parent=0);
    void setupList();


};

#endif // KCLDEVICEMODEL_H

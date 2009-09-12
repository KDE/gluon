#ifndef KCLDEVICEMODEL_H
#define KCLDEVICEMODEL_H

#include "kcldetect.h"

#include <KIcon>

#include <QStandardItemModel>

class KCLDeviceModel : public QStandardItemModel
{
public:
    KCLDeviceModel(QObject * parent = 0);
    void setupList();
};

#endif // KCLDEVICEMODEL_H

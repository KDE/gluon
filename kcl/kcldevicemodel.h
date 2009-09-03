#ifndef KCLDEVICEMODEL_H
#define KCLDEVICEMODEL_H

#include <QStandardItemModel>
#include <KIcon>
#include "kclengine.h"

class KCLDeviceModel : public QStandardItemModel
{
public:
    KCLDeviceModel(QObject * parent=0);
    void setupList();
void addLine(QString text, KIcon icon, DEVICE device);

    private:
    KCLEngine * m_kcl;
};

#endif // KCLDEVICEMODEL_H

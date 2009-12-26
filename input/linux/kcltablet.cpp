#include "kcltablet.h"

#include <QDebug>

KCLTablet::KCLTablet(const QString& device, QObject *parent)
        : KCLInput(device, parent)
{
}


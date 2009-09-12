#include "kcltablet.h"

#include <KDebug>

KCLTablet::KCLTablet(const QString& device, QObject *parent)
        : KCLInput(device, parent)
{
}


#include "kclkeyboard.h"

#include <QDebug>

KCLKeyBoard::KCLKeyBoard(const QString& device, QObject * parent)
        : KCLInput(device, parent)
{
}


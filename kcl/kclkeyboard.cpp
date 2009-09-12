#include "kclkeyboard.h"
#include <KDebug>
KCLKeyBoard::KCLKeyBoard(const QString& device, QObject * parent)
        : KCLInput(device, parent)
{
}


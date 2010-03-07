#include "tablet.h"
#include "tabletprivate.h"

using namespace GluonInput;

Tablet::Tablet(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
{
    d = new TabletPrivate();
}

#include "tablet.moc"

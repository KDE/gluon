#include "detectlinuxprivate.h"

using namespace GluonInput;

DetectLinuxPrivate::DetectLinuxPrivate()
{
}

DetectLinuxPrivate::DetectLinuxPrivate(DetectLinuxPrivate &other)
        : QSharedData(other),
        inputList(other.inputList),
        keyboardList(other.keyboardList),
        mouseList(other.mouseList),
        joystickList(other.joystickList),
        tabletList(other.tabletList),
        unknownList(other.unknownList)
{
}

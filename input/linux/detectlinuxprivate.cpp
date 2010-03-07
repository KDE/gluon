#include "detectlinuxprivate.h"

using namespace GluonInput;

DetectLinuxPrivate::DetectLinuxPrivate()
{
}

DetectLinuxPrivate::DetectLinuxPrivate(DetectLinuxPrivate &other)
  :QSharedData(other),
  m_inputList(other.m_inputList),
  m_keyboardList(other.m_keyboardList),
  m_mouseList(other.m_mouseList),
  m_joystickList(other.m_joystickList),
  m_tabletList(other.m_tabletList),
  m_unknownList(other.m_unknownList)
{
}
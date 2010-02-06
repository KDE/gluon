#ifndef KCLCODE_H
#define KCLCODE_H

#include <QtCore/QString>
#include <QtGui/QIcon>
#include <QtCore/QEvent>

#include "gluoninput.h"
/**
 * \defgroup KCL KCL
 */
//@{

namespace GluonInput
{
  class GLUONINPUTSHARED_EXPORT Code
  {
  public:
      static QString buttonName(int code);
      static QString eventName(int code);
      static QString relAxisName(int code);
      static QString absAxisName(int code);
      static QIcon iconDevice(GluonInput::DeviceFlag device);
  };
}
//@}
#endif // KCLCODE_H

#ifndef KCLKEYBOARD_H
#define KCLKEYBOARD_H

#include "kclinput.h"

/**
 * \defgroup KCL KCL
 */
//@{

class KCL_EXPORT KCLKeyBoard : public KCLInput
{
public:
    KCLKeyBoard(const QString& device, QObject * parent = 0);
};

//@}
#endif // KCLKEYBOARD_H

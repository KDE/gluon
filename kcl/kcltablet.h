#ifndef KCLTABLET_H
#define KCLTABLET_H

#include "kclinput.h"

/**
 * \defgroup KCL KCL
 */
//@{

class KCL_EXPORT KCLTablet : public KCLInput
{
public:
    KCLTablet(const QString& device, QObject * parent = 0);
};

//@}
#endif // KCLTABLET_H

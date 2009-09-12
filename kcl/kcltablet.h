#ifndef KCLTABLET_H
#define KCLTABLET_H
#include "kclinput.h"
class KCLTablet : public KCLInput
{
public:
    KCLTablet(const QString& device, QObject * parent = 0);


};

#endif // KCLTABLET_H

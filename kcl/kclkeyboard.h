#ifndef KCLKEYBOARD_H
#define KCLKEYBOARD_H
#include "kclinput.h"
class KCLKeyBoard : public KCLInput
{
public:
    KCLKeyBoard(const QString& device, QObject * parent=0);

virtual void inputEventFilter(KCLInputEvent * event);

};

#endif // KCLKEYBOARD_H

#ifndef BTSELECTORNODE_H
#define BTSELECTORNODE_H

#include <QObject>

#include "btnode.h"
#include "btfactory.h"
#include "btcharacter.h"
#include "btlib_export.h"

class BT_LIB_EXPORT btSelectorNode : public btNode
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btSelectorNode();
	status run(btCharacter *self);
};

#endif //BTSELECTORNODE_H

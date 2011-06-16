#ifndef BTSEQUENCENODE_H
#define BTSEQUENCENODE_H

#include <QObject>

#include "btfactory.h"
#include "btcharacter.h"
#include "btlib_export.h"

class btNode;

class BT_LIB_EXPORT btSequenceNode : public btNode
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btSequenceNode();
    status run(btCharacter *self);
};

#endif

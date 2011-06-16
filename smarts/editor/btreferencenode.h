#ifndef _BTREFERENCENODE_H_
#define _BTREFERENCENODE_H_

#include "bteditornodetype.h"
#include "bttreemodel.h"

class btReferenceNode :public btEditorNodeType
{
    Q_OBJECT

public:
    btReferenceNode();
    ~btReferenceNode();

    bool run();

    btTreeModel * referenceBehaviorTree();
    void setReferenceBehaviorTree(btTreeModel * treeModel);

private:
    btTreeModel * m_reference;
};

#endif

#ifndef _BTACTIONNODE_H_
#define _BTACTIONNODE_H_

#include "bteditornodetype.h"

class btActionNode : public btEditorNodeType
{
	Q_OBJECT
	
public:
	btActionNode(QObject* parent = 0);	
	~btActionNode();
	
	bool run();
};

#endif

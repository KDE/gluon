#ifndef _BTCONDITIONNODE_H_
#define _BTCONDITIONNODE_H_

#include "bteditornodetype.h"

class btConditionNode : public btEditorNodeType
{
	Q_OBJECT
		
public:
	btConditionNode();	
	~btConditionNode();
	
	bool run();
};

#endif
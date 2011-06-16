#ifndef _BTUNUSABLENODE_H_
#define _BTUNUSABLENODE_H_

#include "bteditornodetype.h"

class btUnusableNode : public btEditorNodeType
{
	Q_OBJECT
		
public:
	btUnusableNode();	
	~btUnusableNode();
	
	bool run();
};

#endif
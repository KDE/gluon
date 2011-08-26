#ifndef _BTCOMPOSITNODE_H_
#define _BTCOMPOSITNODE_H_

#include "bteditornodetype.h"

class btCompositeNode : public btEditorNodeType
{
	Q_OBJECT
	
public:
	btCompositeNode();	
	~btCompositeNode();
	
	bool run();
};

#endif
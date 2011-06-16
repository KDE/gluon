#ifndef STATNODE_H
#define STATNODE_H

#include "btlib_export.h"

struct BT_LIB_EXPORT ProbNode
{
    ProbNode()
	{
        probability = 0.5;
        visited = false;
    }
	
    float probability;
    bool visited;
};

#endif // STATNODE_H

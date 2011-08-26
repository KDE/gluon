#ifndef STATNODE_H
#define STATNODE_H

#include <smarts/lib/btlib_export.h>

struct BT_LIB_EXPORT StatNode
{
    StatNode(){
        fail = 1;
        succes = 1;
        p = 0.5;
        visits = 0;
        wp = 0.5;
        visited = false;
    }
    float p;
    float wp;
    int succes;
    int fail;
    int visits;
    float old_p;
    bool visited;
};

#endif // STATNODE_H

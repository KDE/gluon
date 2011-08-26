// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_VISITOR_H_INCLUDED
#define GDL_VISITOR_H_INCLUDED

#include "gdlast.h"

namespace GDL
{

class  Visitor
{
public:
    virtual ~Visitor() {}
    virtual void visitNode(AstNode *node);
    virtual void visitObject(ObjectAst *) {}
    virtual void visitObject_list(Object_listAst *) {}
    virtual void visitProperty(PropertyAst *) {}
    virtual void visitStart(StartAst *) {}
};

} // end of namespace GDL

#endif


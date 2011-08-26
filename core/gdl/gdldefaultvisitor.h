// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_DEFAULT_VISITOR_H_INCLUDED
#define GDL_DEFAULT_VISITOR_H_INCLUDED

#include "gdlvisitor.h"

namespace GDL
{

class  DefaultVisitor: public Visitor
{
public:
    virtual void visitObject(ObjectAst *node);
    virtual void visitObject_list(Object_listAst *node);
    virtual void visitProperty(PropertyAst *node);
    virtual void visitStart(StartAst *node);
};

} // end of namespace GDL

#endif


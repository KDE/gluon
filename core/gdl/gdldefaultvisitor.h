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
    virtual void visitBoolean_type(Boolean_typeAst *node);
    virtual void visitFloat_type(Float_typeAst *node);
    virtual void visitInteger_type(Integer_typeAst *node);
    virtual void visitList_type(List_typeAst *node);
    virtual void visitLong_long_type(Long_long_typeAst *node);
    virtual void visitObject(ObjectAst *node);
    virtual void visitObject_type(Object_typeAst *node);
    virtual void visitProperty(PropertyAst *node);
    virtual void visitProperty_type(Property_typeAst *node);
    virtual void visitQuaternion_type(Quaternion_typeAst *node);
    virtual void visitRgba_type(Rgba_typeAst *node);
    virtual void visitSize2d_type(Size2d_typeAst *node);
    virtual void visitStart(StartAst *node);
    virtual void visitString_type(String_typeAst *node);
    virtual void visitUnsigned_int_type(Unsigned_int_typeAst *node);
    virtual void visitUrl_type(Url_typeAst *node);
    virtual void visitVector2d_type(Vector2d_typeAst *node);
    virtual void visitVector3d_type(Vector3d_typeAst *node);
    virtual void visitVector4d_type(Vector4d_typeAst *node);
};

} // end of namespace GDL

#endif


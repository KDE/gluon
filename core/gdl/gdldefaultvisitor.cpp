// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "gdldefaultvisitor.h"

namespace GDL
{

void DefaultVisitor::visitBoolean_type(Boolean_typeAst *)
{
}

void DefaultVisitor::visitFloat_type(Float_typeAst *)
{
}

void DefaultVisitor::visitInteger_type(Integer_typeAst *)
{
}

void DefaultVisitor::visitList_type(List_typeAst *)
{
}

void DefaultVisitor::visitLong_long_type(Long_long_typeAst *)
{
}

void DefaultVisitor::visitObject(ObjectAst *node)
{
    if (node->propertiesSequence)
    {
        const KDevPG::ListNode<PropertyAst*> *__it = node->propertiesSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->objectsSequence)
    {
        const KDevPG::ListNode<ObjectAst*> *__it = node->objectsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitObject_type(Object_typeAst *)
{
}

void DefaultVisitor::visitProperty(PropertyAst *node)
{
    visitNode(node->boolean_type);
    visitNode(node->integer_type);
    visitNode(node->unsigned_int_type);
    visitNode(node->long_long_type);
    visitNode(node->float_type);
    visitNode(node->string_type);
    visitNode(node->rgba_type);
    visitNode(node->vector2d_type);
    visitNode(node->vector3d_type);
    visitNode(node->vector4d_type);
    visitNode(node->quaternion_type);
    visitNode(node->size2d_type);
    visitNode(node->list_type);
    visitNode(node->url_type);
    visitNode(node->object_type);
}

void DefaultVisitor::visitQuaternion_type(Quaternion_typeAst *)
{
}

void DefaultVisitor::visitRgba_type(Rgba_typeAst *)
{
}

void DefaultVisitor::visitSize2d_type(Size2d_typeAst *)
{
}

void DefaultVisitor::visitStart(StartAst *node)
{
    if (node->objectsSequence)
    {
        const KDevPG::ListNode<ObjectAst*> *__it = node->objectsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitString_type(String_typeAst *)
{
}

void DefaultVisitor::visitUnsigned_int_type(Unsigned_int_typeAst *)
{
}

void DefaultVisitor::visitUrl_type(Url_typeAst *)
{
}

void DefaultVisitor::visitVector2d_type(Vector2d_typeAst *)
{
}

void DefaultVisitor::visitVector3d_type(Vector3d_typeAst *)
{
}

void DefaultVisitor::visitVector4d_type(Vector4d_typeAst *)
{
}


} // end of namespace GDL


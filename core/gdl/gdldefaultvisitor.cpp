// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "gdldefaultvisitor.h"

namespace GDL
{

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
        const KDevPG::ListNode<Object_listAst*> *__it = node->objectsSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitObject_list(Object_listAst *node)
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

void DefaultVisitor::visitProperty(PropertyAst *)
{
}

void DefaultVisitor::visitStart(StartAst *node)
{
    visitNode(node->list);
}


} // end of namespace GDL


// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "gdlvisitor.h"

namespace GDL
{

void Visitor::visitNode(AstNode *node)
{
    if (node)
    {
        switch (node->kind)
        {
        case AstNode::ObjectKind:
            visitObject(reinterpret_cast<ObjectAst*>(node));
            break;
        case AstNode::Object_listKind:
            visitObject_list(reinterpret_cast<Object_listAst*>(node));
            break;
        case AstNode::PropertyKind:
            visitProperty(reinterpret_cast<PropertyAst*>(node));
            break;
        case AstNode::StartKind:
            visitStart(reinterpret_cast<StartAst*>(node));
            break;
        default:
            Q_ASSERT(false);
        }
    }
}

} // end of namespace GDL


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
        case AstNode::Boolean_typeKind:
            visitBoolean_type(reinterpret_cast<Boolean_typeAst*>(node));
            break;
        case AstNode::Float_typeKind:
            visitFloat_type(reinterpret_cast<Float_typeAst*>(node));
            break;
        case AstNode::Integer_typeKind:
            visitInteger_type(reinterpret_cast<Integer_typeAst*>(node));
            break;
        case AstNode::List_typeKind:
            visitList_type(reinterpret_cast<List_typeAst*>(node));
            break;
        case AstNode::Long_long_typeKind:
            visitLong_long_type(reinterpret_cast<Long_long_typeAst*>(node));
            break;
        case AstNode::ObjectKind:
            visitObject(reinterpret_cast<ObjectAst*>(node));
            break;
        case AstNode::Object_typeKind:
            visitObject_type(reinterpret_cast<Object_typeAst*>(node));
            break;
        case AstNode::PropertyKind:
            visitProperty(reinterpret_cast<PropertyAst*>(node));
            break;
        case AstNode::Quaternion_typeKind:
            visitQuaternion_type(reinterpret_cast<Quaternion_typeAst*>(node));
            break;
        case AstNode::Rgba_typeKind:
            visitRgba_type(reinterpret_cast<Rgba_typeAst*>(node));
            break;
        case AstNode::Size2d_typeKind:
            visitSize2d_type(reinterpret_cast<Size2d_typeAst*>(node));
            break;
        case AstNode::StartKind:
            visitStart(reinterpret_cast<StartAst*>(node));
            break;
        case AstNode::String_typeKind:
            visitString_type(reinterpret_cast<String_typeAst*>(node));
            break;
        case AstNode::Unsigned_int_typeKind:
            visitUnsigned_int_type(reinterpret_cast<Unsigned_int_typeAst*>(node));
            break;
        case AstNode::Url_typeKind:
            visitUrl_type(reinterpret_cast<Url_typeAst*>(node));
            break;
        case AstNode::Vector2d_typeKind:
            visitVector2d_type(reinterpret_cast<Vector2d_typeAst*>(node));
            break;
        case AstNode::Vector3d_typeKind:
            visitVector3d_type(reinterpret_cast<Vector3d_typeAst*>(node));
            break;
        case AstNode::Vector4d_typeKind:
            visitVector4d_type(reinterpret_cast<Vector4d_typeAst*>(node));
            break;
        default:
            Q_ASSERT(false);
        }
    }
}

} // end of namespace GDL


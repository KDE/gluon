// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_AST_H_INCLUDED
#define GDL_AST_H_INCLUDED

#include "gdlast-fwd.h"

#include <QtCore/QList>
#include <kdev-pg-list.h>

namespace GDL
{


    struct  AstNode
    {
        enum AstNodeKind
        {
            Boolean_typeKind = 1000,
            Float_typeKind = 1001,
            Integer_typeKind = 1002,
            List_typeKind = 1003,
            Long_long_typeKind = 1004,
            ObjectKind = 1005,
            Object_typeKind = 1006,
            PropertyKind = 1007,
            Quaternion_typeKind = 1008,
            Rgba_typeKind = 1009,
            Size2d_typeKind = 1010,
            StartKind = 1011,
            String_typeKind = 1012,
            Unsigned_int_typeKind = 1013,
            Url_typeKind = 1014,
            Vector2d_typeKind = 1015,
            Vector3d_typeKind = 1016,
            Vector4d_typeKind = 1017,
            AST_NODE_KIND_COUNT
        };

        int kind;
        qint64 startToken;
        qint64 endToken;

    };

    struct  Boolean_typeAst: public AstNode
    {
        enum { KIND = Boolean_typeKind };

        qint64 value;
    };

    struct  Float_typeAst: public AstNode
    {
        enum { KIND = Float_typeKind };

        qint64 value;
    };

    struct  Integer_typeAst: public AstNode
    {
        enum { KIND = Integer_typeKind };

        qint64 value;
    };

    struct  List_typeAst: public AstNode
    {
        enum { KIND = List_typeKind };

        qint64 type;
        const KDevPG::ListNode<qint64 > *valuesSequence;
        const KDevPG::ListNode<qint64 > *numbersSequence;
        const KDevPG::ListNode<qint64 > *identifiersSequence;
        const KDevPG::ListNode<qint64 > *boolsSequence;
    };

    struct  Long_long_typeAst: public AstNode
    {
        enum { KIND = Long_long_typeKind };

        qint64 value;
    };

    struct  ObjectAst: public AstNode
    {
        enum { KIND = ObjectKind };

        qint64 type;
        qint64 name;
        const KDevPG::ListNode<PropertyAst*> *propertiesSequence;
        const KDevPG::ListNode<ObjectAst*> *objectsSequence;
    };

    struct  Object_typeAst: public AstNode
    {
        enum { KIND = Object_typeKind };

        qint64 type;
        qint64 value;
    };

    struct  PropertyAst: public AstNode
    {
        enum { KIND = PropertyKind };

        qint64 propertyName;
        Boolean_typeAst* boolean_type;
        Integer_typeAst* integer_type;
        Unsigned_int_typeAst* unsigned_int_type;
        Long_long_typeAst* long_long_type;
        Float_typeAst* float_type;
        String_typeAst* string_type;
        Rgba_typeAst* rgba_type;
        Vector2d_typeAst* vector2d_type;
        Vector3d_typeAst* vector3d_type;
        Vector4d_typeAst* vector4d_type;
        Quaternion_typeAst* quaternion_type;
        Size2d_typeAst* size2d_type;
        List_typeAst* list_type;
        Url_typeAst* url_type;
        Object_typeAst* object_type;
    };

    struct  Quaternion_typeAst: public AstNode
    {
        enum { KIND = Quaternion_typeKind };

        qint64 x;
        qint64 y;
        qint64 z;
        qint64 w;
    };

    struct  Rgba_typeAst: public AstNode
    {
        enum { KIND = Rgba_typeKind };

        qint64 r;
        qint64 g;
        qint64 b;
        qint64 a;
    };

    struct  Size2d_typeAst: public AstNode
    {
        enum { KIND = Size2d_typeKind };

        qint64 width;
        qint64 height;
    };

    struct  StartAst: public AstNode
    {
        enum { KIND = StartKind };

        const KDevPG::ListNode<ObjectAst*> *objectsSequence;
    };

    struct  String_typeAst: public AstNode
    {
        enum { KIND = String_typeKind };

        qint64 value;
    };

    struct  Unsigned_int_typeAst: public AstNode
    {
        enum { KIND = Unsigned_int_typeKind };

        qint64 value;
    };

    struct  Url_typeAst: public AstNode
    {
        enum { KIND = Url_typeKind };

        qint64 path;
    };

    struct  Vector2d_typeAst: public AstNode
    {
        enum { KIND = Vector2d_typeKind };

        qint64 x;
        qint64 y;
    };

    struct  Vector3d_typeAst: public AstNode
    {
        enum { KIND = Vector3d_typeKind };

        qint64 x;
        qint64 y;
        qint64 z;
    };

    struct  Vector4d_typeAst: public AstNode
    {
        enum { KIND = Vector4d_typeKind };

        qint64 x;
        qint64 y;
        qint64 z;
        qint64 w;
    };



} // end of namespace GDL

#endif


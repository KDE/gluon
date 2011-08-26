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
        ObjectKind = 1000,
        Object_listKind = 1001,
        PropertyKind = 1002,
        StartKind = 1003,
        AST_NODE_KIND_COUNT
    };

    int kind;
    qint64 startToken;
    qint64 endToken;

};

struct  ObjectAst: public AstNode
{
    enum { KIND = ObjectKind };

    qint64 type;
    qint64 name;
    const KDevPG::ListNode<PropertyAst *> *propertiesSequence;
    const KDevPG::ListNode<Object_listAst *> *objectsSequence;
};

struct  Object_listAst: public AstNode
{
    enum { KIND = Object_listKind };

    const KDevPG::ListNode<ObjectAst *> *objectsSequence;
};

struct  PropertyAst: public AstNode
{
    enum { KIND = PropertyKind };

    qint64 variable;
    qint64 type;
    qint64 value;
};

struct  StartAst: public AstNode
{
    enum { KIND = StartKind };

    Object_listAst *list;
};



} // end of namespace GDL

#endif


#include "debugvisitor.h"

#include <QtCore/QDebug>

char const * const DebugVisitor::names[] = {
    "Object",
    "Object List",
    "Property",
    "Start"
};

void DebugVisitor::visitNode(GDL::AstNode* node)
{
    qDebug() << node->kind;
    GDL::Visitor::visitNode(node);
}

void DebugVisitor::visitObject(GDL::ObjectAst* node)
{
    qDebug() << "Object" << node->name;
    qDebug() << "    Type:" << node->type;
    
    GDL::DefaultVisitor::visitObject(node);
}

void DebugVisitor::visitProperty(GDL::PropertyAst* node)
{
    qDebug() << "Property" << node->variable;
    qDebug() << "    Type:" << node->type;
    qDebug() << "   Value:" << node->value;
    GDL::DefaultVisitor::visitProperty(node);
}


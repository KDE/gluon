#ifndef DEBUGVISITOR_H
#define DEBUGVISITOR_H

#include <gdldefaultvisitor.h>

class DebugVisitor : public GDL::DefaultVisitor
{
    public:
        virtual void visitNode(GDL::AstNode* node);
        virtual void visitObject(GDL::ObjectAst* node);
        virtual void visitProperty(GDL::PropertyAst* node);

    private:
        static char const * const names[];
};

#endif // DEBUGVISITOR_H

#ifndef DEBUGVISITOR_H
#define DEBUGVISITOR_H

#include <gdldefaultvisitor.h>

#include <QtCore/QString>
#include <gdllexer.h>

namespace GDL
{
    class Lexer;
}

class DebugVisitor : public GDL::DefaultVisitor
{
    public:
        DebugVisitor(GDL::Lexer* lexer, const QString& content);
        virtual void visitNode(GDL::AstNode* node);
        virtual void visitObject(GDL::ObjectAst* node);
        virtual void visitProperty(GDL::PropertyAst* node);

        virtual void visitBoolean_type(GDL::Boolean_typeAst* node);
        virtual void visitInteger_type(GDL::Integer_typeAst* node);
        virtual void visitUnsigned_int_type(GDL::Unsigned_int_typeAst* node);
        virtual void visitLong_long_type(GDL::Long_long_typeAst* node);
        virtual void visitFloat_type(GDL::Float_typeAst* node);
        virtual void visitString_type(GDL::String_typeAst* node);
        virtual void visitRgba_type(GDL::Rgba_typeAst* node);
        virtual void visitVector2d_type(GDL::Vector2d_typeAst* node);
        virtual void visitVector3d_type(GDL::Vector3d_typeAst* node);
        virtual void visitVector4d_type(GDL::Vector4d_typeAst* node);
        virtual void visitList_type(GDL::List_typeAst* node);
        virtual void visitQuaternion_type(GDL::Quaternion_typeAst* node);
        virtual void visitSize2d_type(GDL::Size2d_typeAst* node);
        virtual void visitObject_type(GDL::Object_typeAst* node);
        virtual void visitUrl_type(GDL::Url_typeAst* node);

    private:
        QString textForToken(GDL::Lexer::Token token);
        QString stripQuotes(const QString& string);
        
        QString m_indent;
        QString m_content;
        GDL::Lexer* m_lexer;
        static char const * const names[];
};

#endif // DEBUGVISITOR_H

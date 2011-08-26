// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "gdlparser.h"
#include "gdlast.h"
#include "QtCore/QDebug"


# 11 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdlparser.cpp"
# 40 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdl.g" 1
  
void GDL::Parser::expectedSymbol(int /*expectedSymbol*/, const QString& name)
{
  qDebug() << "Expected: " << name;
}
void GDL::Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString& name)
{
  qDebug() << "Expected token: " << name;
}
 
# 21 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdlparser.cpp" 2

namespace GDL
{

bool Parser::parseObject(ObjectAst **yynode)
{
    *yynode = create<ObjectAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->type = -1;
    (*yynode)->name = -1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            expectedToken(yytoken, Token_LBRACE, "LBRACE");
            return false;
        }
        yylex();

        if (yytoken != Token_IDENTIFIER)
        {
            expectedToken(yytoken, Token_IDENTIFIER, "IDENTIFIER");
            return false;
        }
        (*yynode)->type = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_IDENTIFIER)
        {
            expectedToken(yytoken, Token_IDENTIFIER, "IDENTIFIER");
            return false;
        }
        (*yynode)->name = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_RPAREN)
        {
            expectedToken(yytoken, Token_RPAREN, "RPAREN");
            return false;
        }
        yylex();

        while (yytoken == Token_IDENTIFIER
               || yytoken == Token_LBRACE)
        {
            if (yytoken == Token_IDENTIFIER)
            {
                PropertyAst *__node_0 = 0;
                if (!parseProperty(&__node_0))
                {
                    expectedSymbol(AstNode::PropertyKind, "property");
                    return false;
                }
                (*yynode)->propertiesSequence = snoc((*yynode)->propertiesSequence, __node_0, memoryPool);

            }
            else if (yytoken == Token_LBRACE)
            {
                Object_listAst *__node_1 = 0;
                if (!parseObject_list(&__node_1))
                {
                    expectedSymbol(AstNode::Object_listKind, "object_list");
                    return false;
                }
                (*yynode)->objectsSequence = snoc((*yynode)->objectsSequence, __node_1, memoryPool);

            }
            else
            {
                return false;
            }
        }
        if (yytoken != Token_RBRACE)
        {
            expectedToken(yytoken, Token_RBRACE, "RBRACE");
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseObject_list(Object_listAst **yynode)
{
    *yynode = create<Object_listAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        do
        {
            ObjectAst *__node_2 = 0;
            if (!parseObject(&__node_2))
            {
                expectedSymbol(AstNode::ObjectKind, "object");
                return false;
            }
            (*yynode)->objectsSequence = snoc((*yynode)->objectsSequence, __node_2, memoryPool);

        }
        while (yytoken == Token_LBRACE);
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseProperty(PropertyAst **yynode)
{
    *yynode = create<PropertyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->variable = -1;
    (*yynode)->type = -1;
    (*yynode)->value = -1;

    if (yytoken == Token_IDENTIFIER)
    {
        if (yytoken != Token_IDENTIFIER)
        {
            expectedToken(yytoken, Token_IDENTIFIER, "IDENTIFIER");
            return false;
        }
        (*yynode)->variable = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_IDENTIFIER)
        {
            expectedToken(yytoken, Token_IDENTIFIER, "IDENTIFIER");
            return false;
        }
        (*yynode)->type = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_IDENTIFIER)
        {
            expectedToken(yytoken, Token_IDENTIFIER, "IDENTIFIER");
            return false;
        }
        (*yynode)->value = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_RPAREN)
        {
            expectedToken(yytoken, Token_RPAREN, "RPAREN");
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStart(StartAst **yynode)
{
    *yynode = create<StartAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        Object_listAst *__node_3 = 0;
        if (!parseObject_list(&__node_3))
        {
            expectedSymbol(AstNode::Object_listKind, "object_list");
            return false;
        }
        (*yynode)->list = __node_3;

        if (Token_EOF != yytoken)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}


} // end of namespace GDL


// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "gdlparser.h"
#include "gdlast.h"
#include "QtCore/QDebug"
#include "gdltokentext.h"


# 12 "/home/ahiemstra/Projects/KDE/Gluon/newgdlparser/core/gdl/gdlparser.cpp"
# 150 "/home/ahiemstra/Projects/KDE/Gluon/newgdlparser/core/gdl/gdl.g" 1
  
void GDL::Parser::expectedSymbol(int /*expectedSymbol*/, const QString& name)
{
    //qDebug() << "Error when parsing rule" << name;
}
void GDL::Parser::expectedToken(int actual, qint64 /*expected*/, const QString& name)
{
    qint64 line = 0, col = 0;
    tokenStream->locationTable()->positionAt( tokenStream->curr().begin, &line, &col );
    qDebug() << "Parse Error on line" << line + 1;
    qDebug() << "Expected token" << name << "but got token" << GDL::tokenText( actual );
}
 
# 25 "/home/ahiemstra/Projects/KDE/Gluon/newgdlparser/core/gdl/gdlparser.cpp" 2

namespace GDL
{

bool Parser::parseBoolean_type(Boolean_typeAst **yynode)
{
    *yynode = create<Boolean_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->value = -1;
    (*yynode)->value = -1;

    if (yytoken == Token_BOOLEAN)
    {
        if (yytoken != Token_BOOLEAN)
        {
            expectedToken(yytoken, Token_BOOLEAN, "BOOLEAN");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken == Token_TRUE_VALUE)
        {
            if (yytoken != Token_TRUE_VALUE)
            {
                expectedToken(yytoken, Token_TRUE_VALUE, "TRUE_VALUE");
                return false;
            }
            (*yynode)->value = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_FALSE_VALUE)
        {
            if (yytoken != Token_FALSE_VALUE)
            {
                expectedToken(yytoken, Token_FALSE_VALUE, "FALSE_VALUE");
                return false;
            }
            (*yynode)->value = tokenStream->index() - 1;
            yylex();

        }
        else
        {
            return false;
        }
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

bool Parser::parseFloat_type(Float_typeAst **yynode)
{
    *yynode = create<Float_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->value = -1;

    if (yytoken == Token_FLOAT)
    {
        if (yytoken != Token_FLOAT)
        {
            expectedToken(yytoken, Token_FLOAT, "FLOAT");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
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

bool Parser::parseInteger_type(Integer_typeAst **yynode)
{
    *yynode = create<Integer_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->value = -1;

    if (yytoken == Token_INTEGER)
    {
        if (yytoken != Token_INTEGER)
        {
            expectedToken(yytoken, Token_INTEGER, "INTEGER");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
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

bool Parser::parseList_type(List_typeAst **yynode)
{
    *yynode = create<List_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;
    (*yynode)->type = -1;

    if (yytoken == Token_LIST)
    {
        if (yytoken != Token_LIST)
        {
            expectedToken(yytoken, Token_LIST, "LIST");
            return false;
        }
        yylex();

        if (yytoken != Token_LARROW)
        {
            expectedToken(yytoken, Token_LARROW, "LARROW");
            return false;
        }
        yylex();

        if (yytoken == Token_BOOLEAN)
        {
            if (yytoken != Token_BOOLEAN)
            {
                expectedToken(yytoken, Token_BOOLEAN, "BOOLEAN");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_INTEGER)
        {
            if (yytoken != Token_INTEGER)
            {
                expectedToken(yytoken, Token_INTEGER, "INTEGER");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_UNSIGNED_INT)
        {
            if (yytoken != Token_UNSIGNED_INT)
            {
                expectedToken(yytoken, Token_UNSIGNED_INT, "UNSIGNED_INT");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_LONG_LONG)
        {
            if (yytoken != Token_LONG_LONG)
            {
                expectedToken(yytoken, Token_LONG_LONG, "LONG_LONG");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_FLOAT)
        {
            if (yytoken != Token_FLOAT)
            {
                expectedToken(yytoken, Token_FLOAT, "FLOAT");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_STRING)
        {
            if (yytoken != Token_STRING)
            {
                expectedToken(yytoken, Token_STRING, "STRING");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_RGBA)
        {
            if (yytoken != Token_RGBA)
            {
                expectedToken(yytoken, Token_RGBA, "RGBA");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_VECTOR_TWOD)
        {
            if (yytoken != Token_VECTOR_TWOD)
            {
                expectedToken(yytoken, Token_VECTOR_TWOD, "VECTOR_TWOD");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_VECTOR_THREED)
        {
            if (yytoken != Token_VECTOR_THREED)
            {
                expectedToken(yytoken, Token_VECTOR_THREED, "VECTOR_THREED");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_VECTOR_FOURD)
        {
            if (yytoken != Token_VECTOR_FOURD)
            {
                expectedToken(yytoken, Token_VECTOR_FOURD, "VECTOR_FOURD");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_QUATERNION)
        {
            if (yytoken != Token_QUATERNION)
            {
                expectedToken(yytoken, Token_QUATERNION, "QUATERNION");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_SIZE_TWOD)
        {
            if (yytoken != Token_SIZE_TWOD)
            {
                expectedToken(yytoken, Token_SIZE_TWOD, "SIZE_TWOD");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_URL)
        {
            if (yytoken != Token_URL)
            {
                expectedToken(yytoken, Token_URL, "URL");
                return false;
            }
            (*yynode)->type = tokenStream->index() - 1;
            yylex();

        }
        else
        {
            return false;
        }
        if (yytoken != Token_RARROW)
        {
            expectedToken(yytoken, Token_RARROW, "RARROW");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        while (yytoken == Token_FALSE_VALUE
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_NUMBER
               || yytoken == Token_SEMICOLON
               || yytoken == Token_TRUE_VALUE
               || yytoken == Token_VALUE)
        {
            if (yytoken == Token_VALUE)
            {
                if (yytoken != Token_VALUE)
                {
                    expectedToken(yytoken, Token_VALUE, "VALUE");
                    return false;
                }
                (*yynode)->valuesSequence = snoc((*yynode)->valuesSequence, tokenStream->index() - 1, memoryPool);
                yylex();

            }
            else if (yytoken == Token_NUMBER)
            {
                if (yytoken != Token_NUMBER)
                {
                    expectedToken(yytoken, Token_NUMBER, "NUMBER");
                    return false;
                }
                (*yynode)->numbersSequence = snoc((*yynode)->numbersSequence, tokenStream->index() - 1, memoryPool);
                yylex();

            }
            else if (yytoken == Token_IDENTIFIER)
            {
                if (yytoken != Token_IDENTIFIER)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "IDENTIFIER");
                    return false;
                }
                (*yynode)->identifiersSequence = snoc((*yynode)->identifiersSequence, tokenStream->index() - 1, memoryPool);
                yylex();

            }
            else if (yytoken == Token_TRUE_VALUE)
            {
                if (yytoken != Token_TRUE_VALUE)
                {
                    expectedToken(yytoken, Token_TRUE_VALUE, "TRUE_VALUE");
                    return false;
                }
                (*yynode)->boolsSequence = snoc((*yynode)->boolsSequence, tokenStream->index() - 1, memoryPool);
                yylex();

            }
            else if (yytoken == Token_FALSE_VALUE)
            {
                if (yytoken != Token_FALSE_VALUE)
                {
                    expectedToken(yytoken, Token_FALSE_VALUE, "FALSE_VALUE");
                    return false;
                }
                (*yynode)->boolsSequence = snoc((*yynode)->boolsSequence, tokenStream->index() - 1, memoryPool);
                yylex();

            }
            else if (yytoken == Token_SEMICOLON)
            {
                if (yytoken != Token_SEMICOLON)
                {
                    expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
        }
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

bool Parser::parseLong_long_type(Long_long_typeAst **yynode)
{
    *yynode = create<Long_long_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->value = -1;

    if (yytoken == Token_LONG_LONG)
    {
        if (yytoken != Token_LONG_LONG)
        {
            expectedToken(yytoken, Token_LONG_LONG, "LONG_LONG");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
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

        if (yytoken != Token_VALUE)
        {
            expectedToken(yytoken, Token_VALUE, "VALUE");
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
                ObjectAst *__node_1 = 0;
                if (!parseObject(&__node_1))
                {
                    expectedSymbol(AstNode::ObjectKind, "object");
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

bool Parser::parseObject_type(Object_typeAst **yynode)
{
    *yynode = create<Object_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->type = -1;
    (*yynode)->value = -1;

    if (yytoken == Token_IDENTIFIER)
    {
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

        if (yytoken != Token_VALUE)
        {
            expectedToken(yytoken, Token_VALUE, "VALUE");
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

bool Parser::parseProperty(PropertyAst **yynode)
{
    *yynode = create<PropertyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->propertyName = -1;

    if (yytoken == Token_IDENTIFIER)
    {
        if (yytoken != Token_IDENTIFIER)
        {
            expectedToken(yytoken, Token_IDENTIFIER, "IDENTIFIER");
            return false;
        }
        (*yynode)->propertyName = tokenStream->index() - 1;
        yylex();

        if (yytoken == Token_BOOLEAN)
        {
            Boolean_typeAst *__node_2 = 0;
            if (!parseBoolean_type(&__node_2))
            {
                expectedSymbol(AstNode::Boolean_typeKind, "boolean_type");
                return false;
            }
            (*yynode)->boolean_type = __node_2;

        }
        else if (yytoken == Token_INTEGER)
        {
            Integer_typeAst *__node_3 = 0;
            if (!parseInteger_type(&__node_3))
            {
                expectedSymbol(AstNode::Integer_typeKind, "integer_type");
                return false;
            }
            (*yynode)->integer_type = __node_3;

        }
        else if (yytoken == Token_UNSIGNED_INT)
        {
            Unsigned_int_typeAst *__node_4 = 0;
            if (!parseUnsigned_int_type(&__node_4))
            {
                expectedSymbol(AstNode::Unsigned_int_typeKind, "unsigned_int_type");
                return false;
            }
            (*yynode)->unsigned_int_type = __node_4;

        }
        else if (yytoken == Token_LONG_LONG)
        {
            Long_long_typeAst *__node_5 = 0;
            if (!parseLong_long_type(&__node_5))
            {
                expectedSymbol(AstNode::Long_long_typeKind, "long_long_type");
                return false;
            }
            (*yynode)->long_long_type = __node_5;

        }
        else if (yytoken == Token_FLOAT)
        {
            Float_typeAst *__node_6 = 0;
            if (!parseFloat_type(&__node_6))
            {
                expectedSymbol(AstNode::Float_typeKind, "float_type");
                return false;
            }
            (*yynode)->float_type = __node_6;

        }
        else if (yytoken == Token_STRING)
        {
            String_typeAst *__node_7 = 0;
            if (!parseString_type(&__node_7))
            {
                expectedSymbol(AstNode::String_typeKind, "string_type");
                return false;
            }
            (*yynode)->string_type = __node_7;

        }
        else if (yytoken == Token_RGBA)
        {
            Rgba_typeAst *__node_8 = 0;
            if (!parseRgba_type(&__node_8))
            {
                expectedSymbol(AstNode::Rgba_typeKind, "rgba_type");
                return false;
            }
            (*yynode)->rgba_type = __node_8;

        }
        else if (yytoken == Token_VECTOR_TWOD)
        {
            Vector2d_typeAst *__node_9 = 0;
            if (!parseVector2d_type(&__node_9))
            {
                expectedSymbol(AstNode::Vector2d_typeKind, "vector2d_type");
                return false;
            }
            (*yynode)->vector2d_type = __node_9;

        }
        else if (yytoken == Token_VECTOR_THREED)
        {
            Vector3d_typeAst *__node_10 = 0;
            if (!parseVector3d_type(&__node_10))
            {
                expectedSymbol(AstNode::Vector3d_typeKind, "vector3d_type");
                return false;
            }
            (*yynode)->vector3d_type = __node_10;

        }
        else if (yytoken == Token_VECTOR_FOURD)
        {
            Vector4d_typeAst *__node_11 = 0;
            if (!parseVector4d_type(&__node_11))
            {
                expectedSymbol(AstNode::Vector4d_typeKind, "vector4d_type");
                return false;
            }
            (*yynode)->vector4d_type = __node_11;

        }
        else if (yytoken == Token_QUATERNION)
        {
            Quaternion_typeAst *__node_12 = 0;
            if (!parseQuaternion_type(&__node_12))
            {
                expectedSymbol(AstNode::Quaternion_typeKind, "quaternion_type");
                return false;
            }
            (*yynode)->quaternion_type = __node_12;

        }
        else if (yytoken == Token_SIZE_TWOD)
        {
            Size2d_typeAst *__node_13 = 0;
            if (!parseSize2d_type(&__node_13))
            {
                expectedSymbol(AstNode::Size2d_typeKind, "size2d_type");
                return false;
            }
            (*yynode)->size2d_type = __node_13;

        }
        else if (yytoken == Token_LIST)
        {
            List_typeAst *__node_14 = 0;
            if (!parseList_type(&__node_14))
            {
                expectedSymbol(AstNode::List_typeKind, "list_type");
                return false;
            }
            (*yynode)->list_type = __node_14;

        }
        else if (yytoken == Token_URL)
        {
            Url_typeAst *__node_15 = 0;
            if (!parseUrl_type(&__node_15))
            {
                expectedSymbol(AstNode::Url_typeKind, "url_type");
                return false;
            }
            (*yynode)->url_type = __node_15;

        }
        else if (yytoken == Token_IDENTIFIER)
        {
            Object_typeAst *__node_16 = 0;
            if (!parseObject_type(&__node_16))
            {
                expectedSymbol(AstNode::Object_typeKind, "object_type");
                return false;
            }
            (*yynode)->object_type = __node_16;

        }
        else
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

bool Parser::parseQuaternion_type(Quaternion_typeAst **yynode)
{
    *yynode = create<Quaternion_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->x = -1;
    (*yynode)->y = -1;
    (*yynode)->z = -1;
    (*yynode)->w = -1;

    if (yytoken == Token_QUATERNION)
    {
        if (yytoken != Token_QUATERNION)
        {
            expectedToken(yytoken, Token_QUATERNION, "QUATERNION");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->x = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->y = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->z = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->w = tokenStream->index() - 1;
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

bool Parser::parseRgba_type(Rgba_typeAst **yynode)
{
    *yynode = create<Rgba_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->r = -1;
    (*yynode)->g = -1;
    (*yynode)->b = -1;
    (*yynode)->a = -1;

    if (yytoken == Token_RGBA)
    {
        if (yytoken != Token_RGBA)
        {
            expectedToken(yytoken, Token_RGBA, "RGBA");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->r = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->g = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->b = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->a = tokenStream->index() - 1;
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

bool Parser::parseSize2d_type(Size2d_typeAst **yynode)
{
    *yynode = create<Size2d_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->width = -1;
    (*yynode)->height = -1;

    if (yytoken == Token_SIZE_TWOD)
    {
        if (yytoken != Token_SIZE_TWOD)
        {
            expectedToken(yytoken, Token_SIZE_TWOD, "SIZE_TWOD");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->width = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->height = tokenStream->index() - 1;
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
        do
        {
            ObjectAst *__node_17 = 0;
            if (!parseObject(&__node_17))
            {
                expectedSymbol(AstNode::ObjectKind, "object");
                return false;
            }
            (*yynode)->objectsSequence = snoc((*yynode)->objectsSequence, __node_17, memoryPool);

        }
        while (yytoken == Token_LBRACE);
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

bool Parser::parseString_type(String_typeAst **yynode)
{
    *yynode = create<String_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->value = -1;

    if (yytoken == Token_STRING)
    {
        if (yytoken != Token_STRING)
        {
            expectedToken(yytoken, Token_STRING, "STRING");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_VALUE)
        {
            expectedToken(yytoken, Token_VALUE, "VALUE");
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

bool Parser::parseUnsigned_int_type(Unsigned_int_typeAst **yynode)
{
    *yynode = create<Unsigned_int_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->value = -1;

    if (yytoken == Token_UNSIGNED_INT)
    {
        if (yytoken != Token_UNSIGNED_INT)
        {
            expectedToken(yytoken, Token_UNSIGNED_INT, "UNSIGNED_INT");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
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

bool Parser::parseUrl_type(Url_typeAst **yynode)
{
    *yynode = create<Url_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->path = -1;

    if (yytoken == Token_URL)
    {
        if (yytoken != Token_URL)
        {
            expectedToken(yytoken, Token_URL, "URL");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_VALUE)
        {
            expectedToken(yytoken, Token_VALUE, "VALUE");
            return false;
        }
        (*yynode)->path = tokenStream->index() - 1;
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

bool Parser::parseVector2d_type(Vector2d_typeAst **yynode)
{
    *yynode = create<Vector2d_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->x = -1;
    (*yynode)->y = -1;

    if (yytoken == Token_VECTOR_TWOD)
    {
        if (yytoken != Token_VECTOR_TWOD)
        {
            expectedToken(yytoken, Token_VECTOR_TWOD, "VECTOR_TWOD");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->x = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->y = tokenStream->index() - 1;
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

bool Parser::parseVector3d_type(Vector3d_typeAst **yynode)
{
    *yynode = create<Vector3d_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->x = -1;
    (*yynode)->y = -1;
    (*yynode)->z = -1;

    if (yytoken == Token_VECTOR_THREED)
    {
        if (yytoken != Token_VECTOR_THREED)
        {
            expectedToken(yytoken, Token_VECTOR_THREED, "VECTOR_THREED");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->x = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->y = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->z = tokenStream->index() - 1;
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

bool Parser::parseVector4d_type(Vector4d_typeAst **yynode)
{
    *yynode = create<Vector4d_typeAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->x = -1;
    (*yynode)->y = -1;
    (*yynode)->z = -1;
    (*yynode)->w = -1;

    if (yytoken == Token_VECTOR_FOURD)
    {
        if (yytoken != Token_VECTOR_FOURD)
        {
            expectedToken(yytoken, Token_VECTOR_FOURD, "VECTOR_FOURD");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "LPAREN");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->x = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->y = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->z = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, "SEMICOLON");
            return false;
        }
        yylex();

        if (yytoken != Token_NUMBER)
        {
            expectedToken(yytoken, Token_NUMBER, "NUMBER");
            return false;
        }
        (*yynode)->w = tokenStream->index() - 1;
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


} // end of namespace GDL


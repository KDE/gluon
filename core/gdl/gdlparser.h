// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_H_INCLUDED
#define GDL_H_INCLUDED

#include "gdllexer.h"
#include "gdlast-fwd.h"
#include <kdev-pg-memory-pool.h>
#include <kdev-pg-allocator.h>

namespace GDL
{

class  Parser
{
public:
    typedef Lexer::Token Token;
    Lexer *tokenStream;
    int yytoken;

    inline Token LA(qint64 k = 1) const
    {
        return tokenStream->token(tokenStream->index() - 1 + k - 1);
    }
    inline int yylex()
    {
        return (yytoken = tokenStream->nextToken());
    }
    inline void rewind(qint64 index)
    {
        tokenStream->rewind(index);
        yylex();
    }

// token stream
    void setTokenStream(Lexer *s)
    {
        tokenStream = s;
    }

// error handling
    void expectedSymbol(int kind, const QString& name);
    void expectedToken(int kind, qint64 token, const QString& name);

    bool mBlockErrors;
    inline bool blockErrors(bool block)
    {
        bool previous = mBlockErrors;
        mBlockErrors = block;
        return previous;
    }

// memory pool
    typedef KDevPG::MemoryPool memoryPoolType;

    KDevPG::MemoryPool *memoryPool;
    void setMemoryPool(KDevPG::MemoryPool *p)
    {
        memoryPool = p;
    }
    template <class T>
    inline T *create()
    {
        T *node = new (memoryPool->allocate(sizeof(T))) T();
        node->kind = T::KIND;
        return node;
    }
    template <class T>
    inline T *create(AstNode *u)
    {
        T *node = new (memoryPool->allocate(sizeof(T))) T(u);
        node->kind = T::KIND;
        return node;
    }

    enum TokenType
    {
        Token_BOOLEAN = 1000,
        Token_EOF = 1001,
        Token_FALSE_VALUE = 1002,
        Token_FLOAT = 1003,
        Token_IDENTIFIER = 1004,
        Token_INTEGER = 1005,
        Token_LARROW = 1006,
        Token_LBRACE = 1007,
        Token_LIST = 1008,
        Token_LONG_LONG = 1009,
        Token_LPAREN = 1010,
        Token_MULTILINE_VALUE = 1011,
        Token_NUMBER = 1012,
        Token_QUATERNION = 1013,
        Token_RARROW = 1014,
        Token_RBRACE = 1015,
        Token_RGBA = 1016,
        Token_RPAREN = 1017,
        Token_SEMICOLON = 1018,
        Token_SIZE_TWOD = 1019,
        Token_STRING = 1020,
        Token_TRUE_VALUE = 1021,
        Token_UNSIGNED_INT = 1022,
        Token_URL = 1023,
        Token_VALUE = 1024,
        Token_VECTOR_FOURD = 1025,
        Token_VECTOR_THREED = 1026,
        Token_VECTOR_TWOD = 1027,
        TokenTypeSize
    }; // TokenType

    Parser()
    {
        memoryPool = 0;
        tokenStream = 0;
        yytoken = Token_EOF;
        mBlockErrors = false;
    }

    virtual ~Parser() {}

    bool parseBoolean_type(Boolean_typeAst **yynode);
    bool parseFloat_type(Float_typeAst **yynode);
    bool parseInteger_type(Integer_typeAst **yynode);
    bool parseList_type(List_typeAst **yynode);
    bool parseLong_long_type(Long_long_typeAst **yynode);
    bool parseObject(ObjectAst **yynode);
    bool parseObject_list(Object_listAst **yynode);
    bool parseObject_type(Object_typeAst **yynode);
    bool parseProperty(PropertyAst **yynode);
    bool parseQuaternion_type(Quaternion_typeAst **yynode);
    bool parseRgba_type(Rgba_typeAst **yynode);
    bool parseSize2d_type(Size2d_typeAst **yynode);
    bool parseStart(StartAst **yynode);
    bool parseString_type(String_typeAst **yynode);
    bool parseUnsigned_int_type(Unsigned_int_typeAst **yynode);
    bool parseUrl_type(Url_typeAst **yynode);
    bool parseVector2d_type(Vector2d_typeAst **yynode);
    bool parseVector3d_type(Vector3d_typeAst **yynode);
    bool parseVector4d_type(Vector4d_typeAst **yynode);
};

} // end of namespace GDL

#endif


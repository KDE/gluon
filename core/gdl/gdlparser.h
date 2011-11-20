// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_H_INCLUDED
#define GDL_H_INCLUDED

#include "gdltokentype.h"
#include "gdllexer.h"
#include "gdlast-fwd.h"
#include <kdev-pg-memory-pool.h>
#include <kdev-pg-allocator.h>

namespace GDL
{

class  Parser : public TokenTypeWrapper
{
public:
    typedef Lexer::Token Token;
    Lexer *tokenStream;
    int yytoken;

    inline Token LA(qint64 k = 1) const
    {
        qint64 idx = tokenStream->index() - 1 + k - 1;
        qint64 oldidx = tokenStream->index();
        tokenStream->rewind(tokenStream->size());
        while (idx >= tokenStream->size()) tokenStream->read();
        tokenStream->rewind(oldidx);
        return tokenStream->at(idx);
    }
    inline int yylex()
    {
        yytoken = tokenStream->read().kind;
        return yytoken;
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


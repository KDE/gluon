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
        Token_EOF = 1000,
        Token_IDENTIFIER = 1001,
        Token_LBRACE = 1002,
        Token_LPAREN = 1003,
        Token_RBRACE = 1004,
        Token_RPAREN = 1005,
        Token_VALUE = 1006,
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

    bool parseObject(ObjectAst **yynode);
    bool parseObject_list(Object_listAst **yynode);
    bool parseProperty(PropertyAst **yynode);
    bool parseStart(StartAst **yynode);
};

} // end of namespace GDL

#endif


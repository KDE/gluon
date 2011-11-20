// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_TOKEN_TEXT_H_INCLUDED
#define GDL_TOKEN_TEXT_H_INCLUDED

#include "gdltokentype.h"
namespace GDL
{

QString  tokenText(int token)
{
    switch (token)
    {
    case TokenTypeWrapper::Token_BOOLEAN:
        return "BOOLEAN";
    case TokenTypeWrapper::Token_EOF:
        return "end of file";
    case TokenTypeWrapper::Token_FALSE_VALUE:
        return "FALSE_VALUE";
    case TokenTypeWrapper::Token_FLOAT:
        return "FLOAT";
    case TokenTypeWrapper::Token_IDENTIFIER:
        return "IDENTIFIER";
    case TokenTypeWrapper::Token_INTEGER:
        return "INTEGER";
    case TokenTypeWrapper::Token_LARROW:
        return "LARROW";
    case TokenTypeWrapper::Token_LBRACE:
        return "LBRACE";
    case TokenTypeWrapper::Token_LIST:
        return "LIST";
    case TokenTypeWrapper::Token_LONG_LONG:
        return "LONG_LONG";
    case TokenTypeWrapper::Token_LPAREN:
        return "LPAREN";
    case TokenTypeWrapper::Token_MULTILINE_VALUE:
        return "MULTILINE_VALUE";
    case TokenTypeWrapper::Token_NUMBER:
        return "NUMBER";
    case TokenTypeWrapper::Token_QUATERNION:
        return "QUATERNION";
    case TokenTypeWrapper::Token_RARROW:
        return "RARROW";
    case TokenTypeWrapper::Token_RBRACE:
        return "RBRACE";
    case TokenTypeWrapper::Token_RGBA:
        return "RGBA";
    case TokenTypeWrapper::Token_RPAREN:
        return "RPAREN";
    case TokenTypeWrapper::Token_SEMICOLON:
        return "SEMICOLON";
    case TokenTypeWrapper::Token_SIZE_TWOD:
        return "SIZE_TWOD";
    case TokenTypeWrapper::Token_STRING:
        return "STRING";
    case TokenTypeWrapper::Token_TRUE_VALUE:
        return "TRUE_VALUE";
    case TokenTypeWrapper::Token_UNSIGNED_INT:
        return "UNSIGNED_INT";
    case TokenTypeWrapper::Token_URL:
        return "URL";
    case TokenTypeWrapper::Token_VALUE:
        return "VALUE";
    case TokenTypeWrapper::Token_VECTOR_FOURD:
        return "VECTOR_FOURD";
    case TokenTypeWrapper::Token_VECTOR_THREED:
        return "VECTOR_THREED";
    case TokenTypeWrapper::Token_VECTOR_TWOD:
        return "VECTOR_TWOD";
    default:
        return "unknown token";
    }
}
} // end of namespace GDL

#endif


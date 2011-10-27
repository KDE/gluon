// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_TOKEN_TEXT_H_INCLUDED
#define GDL_TOKEN_TEXT_H_INCLUDED

namespace GDL
{

QString tokenText(int token)
{
    switch (token)
    {
    case Parser::Token_BOOLEAN:
        return "BOOLEAN";
    case Parser::Token_EOF:
        return "end of file";
    case Parser::Token_FALSE_VALUE:
        return "FALSE_VALUE";
    case Parser::Token_FLOAT:
        return "FLOAT";
    case Parser::Token_IDENTIFIER:
        return "IDENTIFIER";
    case Parser::Token_INTEGER:
        return "INTEGER";
    case Parser::Token_LARROW:
        return "LARROW";
    case Parser::Token_LBRACE:
        return "LBRACE";
    case Parser::Token_LIST:
        return "LIST";
    case Parser::Token_LONG_LONG:
        return "LONG_LONG";
    case Parser::Token_LPAREN:
        return "LPAREN";
    case Parser::Token_MULTILINE_VALUE:
        return "MULTILINE_VALUE";
    case Parser::Token_NUMBER:
        return "NUMBER";
    case Parser::Token_QUATERNION:
        return "QUATERNION";
    case Parser::Token_RARROW:
        return "RARROW";
    case Parser::Token_RBRACE:
        return "RBRACE";
    case Parser::Token_RGBA:
        return "RGBA";
    case Parser::Token_RPAREN:
        return "RPAREN";
    case Parser::Token_SEMICOLON:
        return "SEMICOLON";
    case Parser::Token_SIZE_TWOD:
        return "SIZE_TWOD";
    case Parser::Token_STRING:
        return "STRING";
    case Parser::Token_TRUE_VALUE:
        return "TRUE_VALUE";
    case Parser::Token_UNSIGNED_INT:
        return "UNSIGNED_INT";
    case Parser::Token_URL:
        return "URL";
    case Parser::Token_VALUE:
        return "VALUE";
    case Parser::Token_VECTOR_FOURD:
        return "VECTOR_FOURD";
    case Parser::Token_VECTOR_THREED:
        return "VECTOR_THREED";
    case Parser::Token_VECTOR_TWOD:
        return "VECTOR_TWOD";
    default:
        return "unknown token";
    }
}
} // end of namespace GDL

#endif


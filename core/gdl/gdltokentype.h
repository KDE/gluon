// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_TOKEN_TYPE_H_INCLUDED
#define GDL_TOKEN_TYPE_H_INCLUDED

namespace GDL
{

struct TokenTypeWrapper // to be imported by using inheritance
{
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
}; // TokenTypeWrapper

typedef TokenTypeWrapper::TokenType TokenType;

} // end of namespace GDL

#endif


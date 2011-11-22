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
            Token_NUMBER = 1011,
            Token_QUATERNION = 1012,
            Token_RARROW = 1013,
            Token_RBRACE = 1014,
            Token_RGBA = 1015,
            Token_RPAREN = 1016,
            Token_SEMICOLON = 1017,
            Token_SIZE_TWOD = 1018,
            Token_STRING = 1019,
            Token_TRUE_VALUE = 1020,
            Token_UNSIGNED_INT = 1021,
            Token_URL = 1022,
            Token_VALUE = 1023,
            Token_VECTOR_FOURD = 1024,
            Token_VECTOR_THREED = 1025,
            Token_VECTOR_TWOD = 1026,
            TokenTypeSize
        }; // TokenType
    }; // TokenTypeWrapper

    typedef TokenTypeWrapper::TokenType TokenType;

} // end of namespace GDL

#endif


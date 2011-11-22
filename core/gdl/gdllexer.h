// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef GDL_LEXER_H_INCLUDED
#define GDL_LEXER_H_INCLUDED

#include "gdltokentype.h"

#include <kdev-pg-char-sets.h>
#include <kdev-pg-token-stream.h>


namespace GDL
{

    class  Lexer :  public KDevPG::TokenStream, public KDevPG::QUtf8ToUcs4Iterator, public TokenTypeWrapper
    {
        public:
            typedef KDevPG::TokenStream Base;
            typedef KDevPG::QUtf8ToUcs4Iterator Iterator;

        private:
            Iterator::PlainIterator spos;
            bool continueLexeme;

        public:
            Lexer( const Iterator& iter );
            ~Lexer();
            Base::Token& read();
    };

} // end of namespace GDL

#endif


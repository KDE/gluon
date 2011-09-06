// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "gdllexer.h"
#include "gdlparser.h"

#include "QtCore/QDebug"

#include <cassert>

namespace GDL
{

Lexer::Lexer(const Lexer::Iterator& iter) : Base(), Iterator(iter), continueLexeme(false)
{}

Lexer::~Lexer()
{}

#define PP_CONCAT_IMPL(x, y) x ## y
#define PP_CONCAT(x, y) PP_CONCAT_IMPL(x, y)

#define lxCURR_POS (Iterator::plain())
#define lxCURR_IDX (Iterator::plain() - Iterator::begin())
#define lxCONTINUE {continueLexeme = true; return advance();}
#define lxLENGTH (Iterator::plain() - Iterator::begin())
#define lxBEGIN_POS (spos)
#define lxBEGIN_IDX (spos - Iterator::begin())
#define lxNAMED_TOKEN(token, X) KDevPG::Token& token(Base::next()); token.kind = ::GDL::Parser::Token_##X; token.begin = lxBEGIN_IDX; token.end = lxCURR_IDX - 1;
#define lxTOKEN(X) {lxNAMED_TOKEN(token, X);}
#define lxDONE {return Base::advance();}
#define lxRETURN(X) {lxTOKEN(X); lxDONE}
#define yytoken (Base::back())
#define lxFAIL {goto _fail;}
#define lxSKIP {return advance();}
#define lxNEXT_CHR(chr) { if(!Iterator::hasNext()) goto _end; chr = Iterator::next(); }

Lexer::Base::Token& Lexer::advance()
{
    if (Base::index() < Base::size())
        return Base::advance();
    if (!Iterator::hasNext())
    {
        Base::Token& _t(Base::advance());
        _t.kind = Parser::Token_EOF;
        _t.begin = _t.end = Iterator::plain() - Iterator::begin();
        return _t;
    }
    if (continueLexeme) continueLexeme = false;
    else spos = plain();
    Iterator::PlainIterator lpos = Iterator::plain();
    Iterator::Int chr = 0;
    int lstate = 0;
    goto _state_0; // no warning about unused label

_state_0:
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 48)
        {
            if (chr < 35)
            {
                if (chr < 32)
                {
                    if (chr < 13)
                    {
                        if (chr == 9 || chr == 10)
                            goto _state_1;
                        else
                            goto _end;
                    }
                    else
                    {
                        if (chr == 13)
                            goto _state_1;
                        else
                            goto _end;
                    }
                }
                else
                {
                    if (chr < 34)
                    {
                        if (chr == 32)
                            goto _state_1;
                        else
                            goto _end;
                    }
                    else
                    {
                        goto _state_5;
                    }
                }
            }
            else
            {
                if (chr < 41)
                {
                    if (chr < 40)
                    {
                        if (chr == 35)
                            goto _state_3;
                        else
                            goto _end;
                    }
                    else
                    {
                        goto _state_85;
                    }
                }
                else
                {
                    if (chr < 45)
                    {
                        if (chr == 41)
                            goto _state_84;
                        else
                            goto _end;
                    }
                    else
                    {
                        if (chr < 47)
                            goto _state_7;
                        else
                            goto _end;
                    }
                }
            }
        }
        else
        {
            if (chr < 65)
            {
                if (chr < 60)
                {
                    if (chr < 59)
                    {
                        if (chr < 58)
                            goto _state_7;
                        else
                            goto _end;
                    }
                    else
                    {
                        goto _state_83;
                    }
                }
                else
                {
                    if (chr < 62)
                    {
                        if (chr == 60)
                            goto _state_87;
                        else
                            goto _end;
                    }
                    else
                    {
                        if (chr == 62)
                            goto _state_86;
                        else
                            goto _end;
                    }
                }
            }
            else
            {
                if (chr < 71)
                {
                    if (chr < 70)
                    {
                        goto _state_6;
                    }
                    else
                    {
                        goto _state_12;
                    }
                }
                else
                {
                    if (chr < 84)
                    {
                        goto _state_6;
                    }
                    else
                    {
                        if (chr < 85)
                        {
                            goto _state_16;
                        }
                        else
                        {
                            if (chr < 91)
                                goto _state_6;
                            else
                                goto _end;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (chr < 113)
        {
            if (chr < 103)
            {
                if (chr < 99)
                {
                    if (chr < 98)
                    {
                        goto _state_6;
                    }
                    else
                    {
                        goto _state_82;
                    }
                }
                else
                {
                    if (chr < 102)
                    {
                        goto _state_6;
                    }
                    else
                    {
                        goto _state_63;
                    }
                }
            }
            else
            {
                if (chr < 106)
                {
                    if (chr < 105)
                    {
                        goto _state_6;
                    }
                    else
                    {
                        goto _state_78;
                    }
                }
                else
                {
                    if (chr < 108)
                    {
                        goto _state_6;
                    }
                    else
                    {
                        if (chr < 109)
                        {
                            goto _state_71;
                        }
                        else
                        {
                            goto _state_6;
                        }
                    }
                }
            }
        }
        else
        {
            if (chr < 117)
            {
                if (chr < 115)
                {
                    if (chr < 114)
                    {
                        goto _state_36;
                    }
                    else
                    {
                        goto _state_52;
                    }
                }
                else
                {
                    if (chr < 116)
                    {
                        goto _state_58;
                    }
                    else
                    {
                        goto _state_16;
                    }
                }
            }
            else
            {
                if (chr < 119)
                {
                    if (chr < 118)
                    {
                        goto _state_75;
                    }
                    else
                    {
                        goto _state_48;
                    }
                }
                else
                {
                    if (chr < 123)
                    {
                        goto _state_6;
                    }
                    else
                    {
                        if (chr < 125)
                        {
                            if (chr == 123)
                                goto _state_89;
                            else
                                goto _end;
                        }
                        else
                        {
                            if (chr == 125)
                                goto _state_88;
                            else
                                goto _end;
                        }
                    }
                }
            }
        }
    }
_state_1:
    lpos = lxCURR_POS;
    lstate = 28;
    lxNEXT_CHR(chr);
    if (chr < 13)
    {
        if (chr == 9 || chr == 10)
            goto _state_1;
        else
            goto _end;
    }
    else
    {
        if (chr < 32)
        {
            if (chr == 13)
                goto _state_1;
            else
                goto _end;
        }
        else
        {
            if (chr == 32)
                goto _state_1;
            else
                goto _end;
        }
    }
_state_2:
    lpos = lxCURR_POS;
    lstate = 27;
    lxNEXT_CHR(chr);
    if (chr < 11)
    {
        if (chr < 10)
            goto _state_2;
        else
            goto _end;
    }
    else
    {
        if (chr < 14)
        {
            if (chr < 13)
                goto _state_2;
            else
                goto _end;
        }
        else
        {
            goto _state_2;
        }
    }
_state_3:
    lxNEXT_CHR(chr);
    if (chr < 11)
    {
        if (chr < 10)
            goto _state_2;
        else
            goto _end;
    }
    else
    {
        if (chr < 14)
        {
            if (chr < 13)
                goto _state_2;
            else
                goto _end;
        }
        else
        {
            goto _state_2;
        }
    }
_state_4:
    lpos = lxCURR_POS;
    lstate = 26;
    lxNEXT_CHR(chr);
    goto _end;
_state_5:
    lxNEXT_CHR(chr);
    if (chr < 34)
    {
        goto _state_5;
    }
    else
    {
        if (chr < 35)
        {
            goto _state_4;
        }
        else
        {
            goto _state_5;
        }
    }
_state_6:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_7:
    lpos = lxCURR_POS;
    lstate = 24;
    lxNEXT_CHR(chr);
    if (chr < 48)
    {
        if (chr == 46)
            goto _state_7;
        else
            goto _end;
    }
    else
    {
        if (chr < 58)
            goto _state_7;
        else
            goto _end;
    }
_state_8:
    lpos = lxCURR_POS;
    lstate = 23;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_9:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 70)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 69)
            {
                goto _state_6;
            }
            else
            {
                goto _state_8;
            }
        }
    }
    else
    {
        if (chr < 101)
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 102)
            {
                goto _state_8;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_10:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 84)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 83)
            {
                goto _state_6;
            }
            else
            {
                goto _state_9;
            }
        }
    }
    else
    {
        if (chr < 115)
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 116)
            {
                goto _state_9;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_11:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 77)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 76)
            {
                goto _state_6;
            }
            else
            {
                goto _state_10;
            }
        }
    }
    else
    {
        if (chr < 108)
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 109)
            {
                goto _state_10;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_12:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 66)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            goto _state_11;
        }
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 98)
            {
                goto _state_11;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_13:
    lpos = lxCURR_POS;
    lstate = 22;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_14:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 70)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 69)
            {
                goto _state_6;
            }
            else
            {
                goto _state_13;
            }
        }
    }
    else
    {
        if (chr < 101)
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 102)
            {
                goto _state_13;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_15:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 86)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 85)
            {
                goto _state_6;
            }
            else
            {
                goto _state_14;
            }
        }
    }
    else
    {
        if (chr < 117)
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 118)
            {
                goto _state_14;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_16:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 83)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 82)
            {
                goto _state_6;
            }
            else
            {
                goto _state_15;
            }
        }
    }
    else
    {
        if (chr < 114)
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 115)
            {
                goto _state_15;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_17:
    lpos = lxCURR_POS;
    lstate = 21;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_18:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 108)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 109)
            {
                goto _state_17;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_19:
    lpos = lxCURR_POS;
    lstate = 20;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_20:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 116)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 117)
            {
                goto _state_19;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_21:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 115)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 116)
            {
                goto _state_20;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_22:
    lpos = lxCURR_POS;
    lstate = 19;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_23:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 100)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 101)
            {
                goto _state_22;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_24:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 51)
    {
        if (chr < 50)
        {
            if (chr >= 48)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            goto _state_23;
        }
    }
    else
    {
        if (chr < 65)
        {
            if (chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_25:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 101)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 102)
            {
                goto _state_24;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_26:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 122)
        {
            goto _state_6;
        }
        else
        {
            if (chr == 122)
                goto _state_25;
            else
                goto _end;
        }
    }
_state_27:
    lpos = lxCURR_POS;
    lstate = 18;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_28:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 110)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 111)
            {
                goto _state_27;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_29:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 111)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 112)
            {
                goto _state_28;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_30:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 105)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 106)
            {
                goto _state_29;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_31:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 110)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 111)
            {
                goto _state_30;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_32:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 114)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 115)
            {
                goto _state_31;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_33:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 101)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 102)
            {
                goto _state_32;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_34:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 116)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 117)
            {
                goto _state_33;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_35:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 98)
        {
            goto _state_34;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_36:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 117)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 118)
            {
                goto _state_35;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_37:
    lpos = lxCURR_POS;
    lstate = 17;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_38:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 100)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 101)
            {
                goto _state_37;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_39:
    lpos = lxCURR_POS;
    lstate = 16;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_40:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 100)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 101)
            {
                goto _state_39;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_41:
    lpos = lxCURR_POS;
    lstate = 15;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_42:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 100)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 101)
            {
                goto _state_41;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_43:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 52)
    {
        if (chr < 50)
        {
            if (chr >= 48)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 51)
            {
                goto _state_42;
            }
            else
            {
                goto _state_40;
            }
        }
    }
    else
    {
        if (chr < 65)
        {
            if (chr < 53)
            {
                goto _state_38;
            }
            else
            {
                if (chr < 59)
                    goto _state_6;
                else
                    goto _end;
            }
        }
        else
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_44:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 114)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 115)
            {
                goto _state_43;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_45:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 111)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 112)
            {
                goto _state_44;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_46:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 116)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 117)
            {
                goto _state_45;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_47:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 99)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 100)
            {
                goto _state_46;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_48:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 101)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 102)
            {
                goto _state_47;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_49:
    lpos = lxCURR_POS;
    lstate = 14;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_50:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 98)
        {
            goto _state_49;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_51:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 98)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 99)
            {
                goto _state_50;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_52:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 103)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 104)
            {
                goto _state_51;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_53:
    lpos = lxCURR_POS;
    lstate = 13;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_54:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 103)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 104)
            {
                goto _state_53;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_55:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 110)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 111)
            {
                goto _state_54;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_56:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 105)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 106)
            {
                goto _state_55;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_57:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 114)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 115)
            {
                goto _state_56;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_58:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 105)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                goto _state_6;
            }
        }
    }
    else
    {
        if (chr < 116)
        {
            if (chr < 106)
            {
                goto _state_26;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 117)
            {
                goto _state_57;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_59:
    lpos = lxCURR_POS;
    lstate = 12;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_60:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 116)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 117)
            {
                goto _state_59;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_61:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 98)
        {
            goto _state_60;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_62:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 111)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 112)
            {
                goto _state_61;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_63:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 66)
            {
                goto _state_11;
            }
            else
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
    else
    {
        if (chr < 108)
        {
            if (chr < 98)
            {
                goto _state_11;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 109)
            {
                goto _state_62;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_64:
    lpos = lxCURR_POS;
    lstate = 11;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_65:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 103)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 104)
            {
                goto _state_64;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_66:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 110)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 111)
            {
                goto _state_65;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_67:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 111)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 112)
            {
                goto _state_66;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_68:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 108)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 109)
            {
                goto _state_67;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_69:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 103)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 104)
            {
                goto _state_68;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_70:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 110)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 111)
            {
                goto _state_69;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_71:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 105)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                goto _state_6;
            }
        }
    }
    else
    {
        if (chr < 111)
        {
            if (chr < 106)
            {
                goto _state_21;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 112)
            {
                goto _state_70;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_72:
    lpos = lxCURR_POS;
    lstate = 10;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_73:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 116)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 117)
            {
                goto _state_72;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_74:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 110)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 111)
            {
                goto _state_73;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_75:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 105)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 97)
            {
                if (chr < 91)
                    goto _state_6;
                else
                    goto _end;
            }
            else
            {
                goto _state_6;
            }
        }
    }
    else
    {
        if (chr < 114)
        {
            if (chr < 106)
            {
                goto _state_74;
            }
            else
            {
                goto _state_6;
            }
        }
        else
        {
            if (chr < 115)
            {
                goto _state_18;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_76:
    lpos = lxCURR_POS;
    lstate = 9;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_77:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 116)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 117)
            {
                goto _state_76;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_78:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 110)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 111)
            {
                goto _state_77;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_79:
    lpos = lxCURR_POS;
    lstate = 8;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 59)
            goto _state_6;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_6;
            else
                goto _end;
        }
    }
_state_80:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 108)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 109)
            {
                goto _state_79;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_81:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 111)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 112)
            {
                goto _state_80;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_82:
    lpos = lxCURR_POS;
    lstate = 25;
    lxNEXT_CHR(chr);
    if (chr < 97)
    {
        if (chr < 65)
        {
            if (chr >= 48 && chr < 59)
                goto _state_6;
            else
                goto _end;
        }
        else
        {
            if (chr < 91)
                goto _state_6;
            else
                goto _end;
        }
    }
    else
    {
        if (chr < 111)
        {
            goto _state_6;
        }
        else
        {
            if (chr < 112)
            {
                goto _state_81;
            }
            else
            {
                if (chr < 123)
                    goto _state_6;
                else
                    goto _end;
            }
        }
    }
_state_83:
    lpos = lxCURR_POS;
    lstate = 7;
    lxNEXT_CHR(chr);
    goto _end;
_state_84:
    lpos = lxCURR_POS;
    lstate = 6;
    lxNEXT_CHR(chr);
    goto _end;
_state_85:
    lpos = lxCURR_POS;
    lstate = 5;
    lxNEXT_CHR(chr);
    goto _end;
_state_86:
    lpos = lxCURR_POS;
    lstate = 4;
    lxNEXT_CHR(chr);
    goto _end;
_state_87:
    lpos = lxCURR_POS;
    lstate = 3;
    lxNEXT_CHR(chr);
    goto _end;
_state_88:
    lpos = lxCURR_POS;
    lstate = 2;
    lxNEXT_CHR(chr);
    goto _end;
_state_89:
    lpos = lxCURR_POS;
    lstate = 1;
    lxNEXT_CHR(chr);
    goto _end;
_end:
    plain() = lpos;
    switch (lstate)
    {
    case 0:
        goto _fail; // no warning about unused label
_fail:
        {
            qDebug() << "error";
            exit(-1);
        }
    case 1:
    {
        lxRETURN(LBRACE)
    }
    case 2:
    {
        lxRETURN(RBRACE)
    }
    case 3:
    {
        lxRETURN(LARROW)
    }
    case 4:
    {
        lxRETURN(RARROW)
    }
    case 5:
    {
        lxRETURN(LPAREN)
    }
    case 6:
    {
        lxRETURN(RPAREN)
    }
    case 7:
    {
        lxRETURN(SEMICOLON)
    }
    case 8:
    {
        lxRETURN(BOOLEAN)
    }
    case 9:
    {
        lxRETURN(INTEGER)
    }
    case 10:
    {
        lxRETURN(UNSIGNED_INT)
    }
    case 11:
    {
        lxRETURN(LONG_LONG)
    }
    case 12:
    {
        lxRETURN(FLOAT)
    }
    case 13:
    {
        lxRETURN(STRING)
    }
    case 14:
    {
        lxRETURN(RGBA)
    }
    case 15:
    {
        lxRETURN(VECTOR_TWOD)
    }
    case 16:
    {
        lxRETURN(VECTOR_THREED)
    }
    case 17:
    {
        lxRETURN(VECTOR_FOURD)
    }
    case 18:
    {
        lxRETURN(QUATERNION)
    }
    case 19:
    {
        lxRETURN(SIZE_TWOD)
    }
    case 20:
    {
        lxRETURN(LIST)
    }
    case 21:
    {
        lxRETURN(URL)
    }
    case 22:
    {
        lxRETURN(TRUE_VALUE)
    }
    case 23:
    {
        lxRETURN(FALSE_VALUE)
    }
    case 24:
    {
        lxRETURN(NUMBER)
    }
    case 25:
    {
        lxRETURN(IDENTIFIER)
    }
    case 26:
    {
        lxRETURN(VALUE)
    }
    case 27:
    {
# 3689 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdllexer.cpp"
# 59 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdl.g" 1
                                           /* Comment, ignore */ 
# 3690 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdllexer.cpp" 2

        lxSKIP
    }
    case 28:
    {
# 3698 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdllexer.cpp"
# 61 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdl.g" 1
                                           /* Whitespace, ignore */ 
# 3699 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdllexer.cpp" 2

        lxSKIP
    }
    }
    /* assert(false);*/
    return Base::advance();
}

#undef lxNEXT_CHR
#undef lxFAIl
#undef lxRETURN
#undef lxTOKEN
#undef lxBEGIN_IDX
#undef lxBEGIN_POS
#undef lxLENGTH
#undef lxCONTINUE
#undef lxCURR_IDX
#undef lxCURR_POS

#undef PP_CONCAT
#undef PP_CONCAT_IMPL


} // end of namespace GDL


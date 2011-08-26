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
    if (chr < 41)
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
            if (chr < 35)
            {
                if (chr == 32)
                    goto _state_1;
                else
                    goto _end;
            }
            else
            {
                if (chr < 40)
                {
                    if (chr == 35)
                        goto _state_4;
                    else
                        goto _end;
                }
                else
                {
                    goto _state_8;
                }
            }
        }
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 65)
            {
                if (chr == 41)
                    goto _state_7;
                else
                    goto _end;
            }
            else
            {
                if (chr < 91)
                    goto _state_9;
                else
                    goto _end;
            }
        }
        else
        {
            if (chr < 123)
            {
                goto _state_9;
            }
            else
            {
                if (chr < 125)
                {
                    if (chr == 123)
                        goto _state_6;
                    else
                        goto _end;
                }
                else
                {
                    if (chr == 125)
                        goto _state_5;
                    else
                        goto _end;
                }
            }
        }
    }
_state_1:
    lpos = lxCURR_POS;
    lstate = 7;
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
    lxNEXT_CHR(chr);
    if (chr < 10)
    {
        goto _state_2;
    }
    else
    {
        if (chr < 11)
        {
            goto _state_3;
        }
        else
        {
            goto _state_2;
        }
    }
_state_3:
    lpos = lxCURR_POS;
    lstate = 6;
    lxNEXT_CHR(chr);
    if (chr < 10)
    {
        goto _state_2;
    }
    else
    {
        if (chr < 11)
        {
            goto _state_3;
        }
        else
        {
            goto _state_2;
        }
    }
_state_4:
    lxNEXT_CHR(chr);
    goto _state_2;
_state_5:
    lpos = lxCURR_POS;
    lstate = 5;
    lxNEXT_CHR(chr);
    goto _end;
_state_6:
    lpos = lxCURR_POS;
    lstate = 4;
    lxNEXT_CHR(chr);
    goto _end;
_state_7:
    lpos = lxCURR_POS;
    lstate = 3;
    lxNEXT_CHR(chr);
    goto _end;
_state_8:
    lpos = lxCURR_POS;
    lstate = 2;
    lxNEXT_CHR(chr);
    goto _end;
_state_9:
    lpos = lxCURR_POS;
    lstate = 1;
    lxNEXT_CHR(chr);
    if (chr < 65)
    {
        if (chr >= 48 && chr < 58)
            goto _state_9;
        else
            goto _end;
    }
    else
    {
        if (chr < 97)
        {
            if (chr < 91)
                goto _state_9;
            else
                goto _end;
        }
        else
        {
            if (chr < 123)
                goto _state_9;
            else
                goto _end;
        }
    }
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
        lxRETURN(IDENTIFIER)
    }
    case 2:
    {
        lxRETURN(LPAREN)
    }
    case 3:
    {
        lxRETURN(RPAREN)
    }
    case 4:
    {
        lxRETURN(LBRACE)
    }
    case 5:
    {
        lxRETURN(RBRACE)
    }
    case 6:
    {
# 296 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdllexer.cpp"
# 22 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdl.g" 1
                                                       /* Comment, ignore */ 
# 297 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdllexer.cpp" 2

        lxSKIP
    }
    case 7:
    {
# 305 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdllexer.cpp"
# 24 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdl.g" 1
                                                       /* Whitespace, ignore */ 
# 306 "/home/ahiemstra-work/Projects/KDE/gluon/core/gdl/gdllexer.cpp" 2

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


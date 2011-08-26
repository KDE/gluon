%token_stream Lexer ;

%token LPAREN, RPAREN, LBRACE, RBRACE, IDENTIFIER, VALUE ;

%lexer_bits_header "QtCore/QDebug"
%parser_bits_header "QtCore/QDebug"

%input_encoding "utf32"
-- %table_lexer
%input_stream "KDevPG::QUtf8ToUcs4Iterator"

%lexer ->
    [a-zA-Z][a-zA-Z0-9]*                            IDENTIFIER ;

    --"\""[.^{}()]+"\""                             VALUE ;
    
    "("                                             LPAREN ;
    ")"                                             RPAREN ;
    "{"                                             LBRACE ;
    "}"                                             RBRACE ;

    "#".+\n                                         [: /* Comment, ignore */ :] ;

    [\ \t\r\n]+                                     [: /* Whitespace, ignore */ :] ;
;

    variable=IDENTIFIER type=IDENTIFIER LPAREN ( value=IDENTIFIER ) RPAREN
-> property ;

    LBRACE type=IDENTIFIER LPAREN name=IDENTIFIER RPAREN
    ( #properties=property | #objects=object_list )*
    RBRACE
-> object ;

    #objects=object+
-> object_list ;

    list=object_list
-> start;

[:
void GDL::Parser::expectedSymbol(int /*expectedSymbol*/, const QString& name)
{
  qDebug() << "Expected: " << name;
}
void GDL::Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString& name)
{
  qDebug() << "Expected token: " << name;
}
:]
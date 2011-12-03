%token_stream Lexer ;

-- Base tokens
%token LBRACE, RBRACE, LPAREN, RPAREN, LBRACKET, RBRACKET, SEMICOLON, TRUE_VALUE, FALSE_VALUE, NUMBER, IDENTIFIER, VALUE ;

-- Types
%token BOOLEAN, INTEGER, UNSIGNED_INT, LONG_LONG, FLOAT, STRING, RGBA,
       VECTOR_TWOD("Vector2D"), VECTOR_THREED("Vector3D"), VECTOR_FOURD("Vector4D"), QUATERNION, SIZE_TWOD, LIST, URL ;

%lexer_bits_header "QtCore/QDebug"
%parser_bits_header "QtCore/QDebug"
%parser_bits_header "gdltokentext.h"

%input_encoding "utf32"
%input_stream "KDevPG::QUtf8ToUcs4Iterator"

%lexer ->
    -- Basic character classes
    [a-z]                               -> alphanocaps ;
    [A-Z]                               -> alphacaps ;
    [{alphanocaps}{alphacaps}]          -> alphabetic ;
    [0-9]                               -> numeric ;
    [{alphabetic}{numeric}]             -> alphanumeric ;

    -- Basic divider characters
    "{"                                 LBRACE ;
    "}"                                 RBRACE ;
    "("                                 LPAREN ;
    ")"                                 RPAREN ;
    "["                                 LBRACKET ;
    "]"                                 RBRACKET ;
    ";"                                 SEMICOLON ;

    -- Types
    "bool"                              BOOLEAN ;
    "int"                               INTEGER ;
    "uint"                              UNSIGNED_INT ;
    "longlong"                          LONG_LONG ;
    "float"                             FLOAT ;
    "string"                            STRING ;
    "rgba"                              RGBA ;
    "vector2d"                          VECTOR_TWOD ;
    "vector3d"                          VECTOR_THREED ;
    "vector4d"                          VECTOR_FOURD ;
    "quaternion"                        QUATERNION ;
    "size2d"                            SIZE_TWOD ;
    "list"                              LIST ;
    "url"                               URL ;

    -- Common elements
    [tT][rR][uU][eE]                    TRUE_VALUE ;
    [fF][aA][lL][sS][eE]                FALSE_VALUE ;

    [\-{numeric}\.][{numeric}\.]*       NUMBER ;

    {alphabetic}[{alphanumeric}\:]*     IDENTIFIER ;

    "\""[.^"\""]*"\""                   VALUE ;

    "#"[.^\r\n]+                        [: /* Comment, ignore */ :] ;

    [\ \t\r]+                           [: /* Whitespace, ignore */ :] ;

    %fail                               [:
    qint64 line = 0, col = 0;
    locationTable()->positionAt( lxCURR_IDX, &line, &col );
    qDebug() << "Tokenizer error on line" << line + 1; :]

    "\n"                                [: locationTable()->newline(lxCURR_IDX); :] ;

;

    BOOLEAN LPAREN ( value=TRUE_VALUE | value=FALSE_VALUE ) RPAREN
-> boolean_type ;

    INTEGER LPAREN value=NUMBER RPAREN
-> integer_type ;

    UNSIGNED_INT LPAREN value=NUMBER RPAREN
-> unsigned_int_type ;

    LONG_LONG LPAREN value=NUMBER RPAREN
-> long_long_type ;

    FLOAT LPAREN value=NUMBER RPAREN
-> float_type ;

    STRING LPAREN value=VALUE RPAREN
-> string_type ;

    RGBA LPAREN r=NUMBER SEMICOLON g=NUMBER SEMICOLON b=NUMBER SEMICOLON a=NUMBER RPAREN
-> rgba_type ;

    VECTOR_TWOD LPAREN x=NUMBER SEMICOLON y=NUMBER RPAREN
-> vector2d_type ;

    VECTOR_THREED LPAREN x=NUMBER SEMICOLON y=NUMBER SEMICOLON z=NUMBER RPAREN
-> vector3d_type ;

    VECTOR_FOURD LPAREN x=NUMBER SEMICOLON y=NUMBER SEMICOLON z=NUMBER SEMICOLON w=NUMBER RPAREN
-> vector4d_type ;

    QUATERNION LPAREN x=NUMBER SEMICOLON y=NUMBER SEMICOLON z=NUMBER SEMICOLON w=NUMBER RPAREN
-> quaternion_type ;

    SIZE_TWOD LPAREN width=NUMBER SEMICOLON height=NUMBER RPAREN
-> size2d_type ;

    URL LPAREN path=VALUE RPAREN
-> url_type ;

    type=IDENTIFIER LPAREN value=VALUE RPAREN
-> object_type ;

    boolean_type=boolean_type
    | integer_type=integer_type
    | unsigned_int_type=unsigned_int_type
    | long_long_type=long_long_type
    | float_type=float_type
    | string_type=string_type
    | rgba_type=rgba_type
    | vector2d_type=vector2d_type
    | vector3d_type=vector3d_type
    | vector4d_type=vector4d_type
    | quaternion_type=quaternion_type
    | size2d_type=size2d_type
    | url_type=url_type
    | object_type=object_type
-> property_type ;

    LIST LPAREN LBRACKET ( #values=property_type SEMICOLON )+ RBRACKET RPAREN
-> list_type ;

    propertyName=IDENTIFIER ( value=property_type | list=list_type )
-> property ;

    LBRACE type=IDENTIFIER LPAREN name=VALUE RPAREN
    ( #properties=property | #objects=object )*
    RBRACE
-> object ;

    #objects=object+
-> start;

[:
void GDL::Parser::expectedSymbol(int /*expectedSymbol*/, const QString& name)
{
    //qDebug() << "Error when parsing rule" << name;
}
void GDL::Parser::expectedToken(int actual, qint64 /*expected*/, const QString& name)
{
    qint64 line = 0, col = 0;
    tokenStream->locationTable()->positionAt( tokenStream->curr().begin, &line, &col );
    qDebug() << "Parse Error on line" << line + 1;
    qDebug() << "Expected token" << name << "but got token" << GDL::tokenText( actual );
}
:]

#include <core/gdl/gdlast.h>
#include <core/gdl/gdllexer.h>
#include <core/gdl/gdlparser.h>
#include <core/gdl/gdldefaultvisitor.h>

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QUrl>

#include "debugvisitor.h"
#include "objecttreebuilder.h"
#include <gluonobjectfactory.h>
#include <QApplication>
#include <gluonobject.h>
#include <QMetaObject>

QString tokenName(int token);

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    if( argc != 2 )
    {
        qDebug() << "Usage: gluonexamples_core_gdlparser [filename]";
        return 1;
    }

    QUrl filePath = QUrl::fromEncoded(argv[1]);

    qDebug() << "Opening file" << filePath.toLocalFile();

    QFile file(filePath.toLocalFile());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open file!";
        return 1;
    }

    QByteArray data = file.readAll();
    file.close();

    KDevPG::QUtf8ToUcs4Iterator itr(data);

    GDL::Lexer lexer(itr);
    KDevPG::MemoryPool mem;

    GDL::Parser parser;
    parser.setTokenStream(&lexer);
    parser.setMemoryPool(&mem);

    qDebug() << "Tokenised Tree:";

    GDL::Lexer::Token token;
    QByteArray indent = "";
    while( (token = lexer.advance()).kind != GDL::Parser::Token_EOF )
    {
        QString message = indent + "Token: " + tokenName(token.kind);
        if(token.kind == GDL::Parser::Token_LBRACE)
        {
            indent = indent + "    ";
        }
        else if(token.kind == GDL::Parser::Token_RBRACE)
        {
            if(indent.size() >= 4)
                indent = indent.left(indent.size() - 4);
        }
        qDebug() << message;
    }

    parser.rewind(0);

    qDebug() << "Start parsing...";

    GDL::StartAst* ast;
    if(!parser.parseStart(&ast))
    {
        qDebug() << "Error parsing file.";
        return 1;
    }

    qDebug() << "Output:";

    DebugVisitor visitor(&lexer, data);
    visitor.visitStart(ast);

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    GDL::ObjectTreeBuilder builder(&lexer, data);
    builder.visitStart(ast);

    qDebug() << "Object Count:" << builder.objects().count();
    if(builder.objects().count() > 0)
        builder.objects().at(0)->dumpObjectTree();
        //qDebug() << "First Object is a:" << builder.objects().at(0)->metaObject()->className();

    return 0;
}

QString tokenName(int token)
{
    switch(token)
    {
        case GDL::Parser::Token_EOF:
            return QString("EOF");
        case GDL::Parser::Token_IDENTIFIER:
            return QString("Identifier");
        case GDL::Parser::Token_LBRACE:
            return QString("{");
        case GDL::Parser::Token_RBRACE:
            return QString("}");
        case GDL::Parser::Token_VALUE:
            return QString("Value");
        case GDL::Parser::Token_MULTILINE_VALUE:
            return QString("Multiline Value");
        case GDL::Parser::Token_BOOLEAN:
            return QString("Boolean");
        case GDL::Parser::Token_INTEGER:
            return QString("Integer");
        case GDL::Parser::Token_UNSIGNED_INT:
            return QString("Unsigned Integer");
        case GDL::Parser::Token_LONG_LONG:
            return QString("Long long");
        case GDL::Parser::Token_STRING:
            return QString("String");
        case GDL::Parser::Token_RGBA:
            return QString("Colour");
        case GDL::Parser::Token_VECTOR_TWOD:
            return QString("Vector2D");
        case GDL::Parser::Token_VECTOR_THREED:
            return QString("Vector3D");
        case GDL::Parser::Token_VECTOR_FOURD:
            return QString("Vector4D");
        case GDL::Parser::Token_QUATERNION:
            return QString("Quaternion");
        case GDL::Parser::Token_LARROW:
            return QString("<");
        case GDL::Parser::Token_RARROW:
            return QString(">");
        case GDL::Parser::Token_FLOAT:
            return QString("Float");
        case GDL::Parser::Token_LIST:
            return QString("List");
        case GDL::Parser::Token_SIZE_TWOD:
            return QString("Size2D");
        case GDL::Parser::Token_LPAREN:
            return QString("(");
        case GDL::Parser::Token_RPAREN:
            return QString(")");
        case GDL::Parser::Token_NUMBER:
            return QString("Number");
        case GDL::Parser::Token_SEMICOLON:
            return QString(";");
        case GDL::Parser::Token_TRUE_VALUE:
            return QString("True");
        case GDL::Parser::Token_FALSE_VALUE:
            return QString("False");
        case GDL::Parser::Token_URL:
            return QString("Url");
        default:
            return QString("Unknown!");
    }
}
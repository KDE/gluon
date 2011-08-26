#include <core/gdl/gdlast.h>
#include <core/gdl/gdllexer.h>
#include <core/gdl/gdlparser.h>
#include <core/gdl/gdldefaultvisitor.h>

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QUrl>

#include "debugvisitor.h"

int main(int argc, char** argv)
{
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

    lexer.advance();
    parser.rewind(0);

    qDebug() << "Start parsing...";

    GDL::StartAst* ast;
    if(!parser.parseStart(&ast))
    {
        qDebug() << "Error parsing file.";
        return 1;
    }

    qDebug() << "Output:";

    DebugVisitor visitor;
    visitor.visitStart(ast);

    return 0;
}
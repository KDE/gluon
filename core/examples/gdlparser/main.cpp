/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QUrl>
#include <QtCore/QTime>
#include <QtGui/QApplication>

#include <core/gluonobjectfactory.h>
#include <core/gdl/gdlast.h>
#include <core/gdl/gdllexer.h>
#include <core/gdl/gdlparser.h>
#include <core/gdl/gdldefaultvisitor.h>
#include <core/gdl/gdltokentext.h>
#include <core/gdl/objecttreebuilder.h>

#include "debugvisitor.h"

QString tokenName(int token);

void parseNew( const QByteArray& data );
void parseOld( const QString& data );

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

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

    qDebug() << "Parsing 100 times using old parser";

    QString stringData( data );
    QTime timer;
    timer.start();
    for( int i = 0; i < 100; ++i )
    {
        parseOld( stringData );
    }

    qDebug() << "Elapsed time:" << timer.elapsed();

    qDebug() << "Parsing 100 times using new parser";
    timer.restart();
    for( int i = 0; i < 100; ++i )
    {
        parseNew( data );
    }

    qDebug() << "Elapsed time:" << timer.elapsed();

    return 0;
}

void parseOld( const QString& data )
{
    //GluonCore::GDLHandler::instance()->parseGDL( data, data.size() );
}

void parseNew(const QByteArray& data)
{
    KDevPG::QUtf8ToUcs4Iterator itr(data);

    GDL::Lexer lexer(itr);
    KDevPG::MemoryPool mem;

    GDL::Parser parser;
    parser.setTokenStream(&lexer);
    parser.setMemoryPool(&mem);

    while( lexer.advance().kind != GDL::Parser::Token_EOF );
    parser.rewind(0);

    GDL::StartAst* ast;
    if(!parser.parseStart(&ast))
    {
        qDebug() << "Error parsing file.";
        return;
    }

    GDL::ObjectTreeBuilder builder(&lexer, data);
    builder.visitStart(ast);
}

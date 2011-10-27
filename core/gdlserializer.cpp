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


#include "gdlserializer.h"

#include <QtCore/QFile>
#include <QtCore/QUrl>

#include "debughelper.h"
#include "gdl/gdlast.h"
#include "gdl/gdlparser.h"
#include "gdl/gdllexer.h"
#include "gdl/objecttreebuilder.h"

using namespace GluonCore;

GLUON_DEFINE_SINGLETON( GDLSerializer )

bool GDLSerializer::read(const QUrl& url, GluonObjectList& objects)
{
    QFile file( url.toLocalFile() );
    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        DEBUG_BLOCK
        DEBUG_TEXT2( "Could not open file %1", url.toLocalFile() );
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    if( data.size() > 0 )
    {
        return parse( data, objects );
    }
    else
    {
        return false;
    }
}

bool GDLSerializer::write(const QUrl& url, const GluonObjectList& objects)
{
    return false;
}

bool GDLSerializer::parse(const QByteArray& data, GluonObjectList& objects)
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
        return false;
    }

    GDL::ObjectTreeBuilder builder( &lexer, data );
    builder.visitStart(ast);

    if( objects.count() > 0 )
    {
        objects = builder.objects();
    }
    else
    {
        return false;
    }

    return true;
}

bool GDLSerializer::serialize(const GluonObjectList& objects, QByteArray& data)
{
    return false;
}

GDLSerializer::GDLSerializer(QObject* parent): Singleton< GluonCore::GDLSerializer >(parent)
{

}

#include "gdlserializer.moc"

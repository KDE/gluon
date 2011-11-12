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


#include "propertylist.h"

#include <QtCore/QMetaProperty>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>

#include <KDE/KLocalizedString>

#include <core/gluonobject.h>

using namespace GluonCreator;

class PropertyList::Private
{
    public:
        QGridLayout* layout;
        QLabel* name;
        QList< QWidget* > widgets;
};

PropertyList::PropertyList( QWidget* parent )
    : QTextEdit( parent ), d( new Private )
{
//     d->layout = new QGridLayout( this );
//     d->name = new QLabel( this );
//     d->layout->addWidget( d->name, 0, 0, 1, 2 );
//     setLayout( d->layout );
//     setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    setReadOnly( true );
    setWindowTitle( i18n( "Project Inspector - Gluon Creator" ) );
}

PropertyList::~PropertyList()
{

}

void PropertyList::setObject(QObject* object)
{
    clear();

    QString text( "<center>" );
    GluonCore::GluonObject* gobj = qobject_cast< GluonCore::GluonObject* >( object );
    if( gobj )
    {
        text.append( QString("<h3>%1</h3>").arg( gobj->name() ) );
    }
    else
    {
        text.append( QString("<h3>%1</h3>").arg( object->objectName() ) );
    }

    text.append( "<table width=\"100%\">" );
    text.append( QString( "<tr><td colspan=\"2\" align=\"center\">%1</td></tr>" ).arg( object->metaObject()->className() ) );

    text.append( QString( "<tr><td colspan=\"2\">&nbsp;</td></tr>" ) );

    const int numProperties = object->metaObject()->propertyCount();
    for( int i = 0; i < numProperties; ++i )
    {
        QMetaProperty property = object->metaObject()->property( i );

        text.append( "<tr>\n" );
        text.append( QString( "<td align=\"right\"><b>%1</b></td>\n<td>%2</td>\n" ).arg( property.name() ).arg( property.read( object ).toString() ) );
        text.append( "</tr>\n" );
    }

    QList<QByteArray> dynamicProperties = object->dynamicPropertyNames();
    if( dynamicProperties.count() > 0 )
    {
        text.append( QString( "<tr><td>&nbsp;</td></tr><tr><td colspan=\"2\" align=\"center\"><i>Dynamic Properties</i></td></tr>" ) );
        foreach( const QByteArray& name, dynamicProperties )
        {
            text.append( "<tr>\n" );
            text.append( QString( "<td align=\"right\"><b>%1</b></td>\n<td>%2</td>\n" ).arg( name.data() ).arg( object->property( name ).toString() ) );
            text.append( "</tr>\n" );
        }
    }

    text.append( "</table></center>" );

    setText( text );
}

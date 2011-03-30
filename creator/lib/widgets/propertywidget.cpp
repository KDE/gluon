/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "propertywidget.h"

using namespace GluonCreator;

#include "propertywidgetcontainer.h"
#include "propertywidgetitem.h"
#include "propertywidgetitemfactory.h"

#include <engine/asset.h>
#include <engine/scene.h>

#include <core/gluonobject.h>

#include <KDE/KIcon>
#include <KDE/KLocalizedString>

#include <QtGui/QBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>

#include <QtCore/QVariant>
#include <QtCore/QMetaClassInfo>

class PropertyWidget::PropertyWidgetPrivate
{
    public:
        PropertyWidgetPrivate()
        {
            object = 0;
            layout = 0;
        }
        GluonCore::GluonObject* object;
        QVBoxLayout* layout;

        void appendMetaObject( QWidget* parent, QObject* object, QGridLayout* layout );
};


PropertyWidget::PropertyWidget( QWidget* parent ): QScrollArea( parent ), d( new PropertyWidgetPrivate )
{
}

PropertyWidget::~PropertyWidget()
{
    delete d;
}

GluonCore::GluonObject* PropertyWidget::object() const
{
    return d->object;
}

void PropertyWidget::setObject( GluonCore::GluonObject* object )
{
    if( object )
    {
        d->object = object;
        d->layout = new QVBoxLayout( this );
        d->layout->setSpacing( 0 );
        d->layout->setContentsMargins( 0, 0, 0, 0 );
        d->layout->setAlignment( Qt::AlignTop );

        appendObject( object, true );
        for( int i = 0; i < object->children().count(); i++ )
        {
            GluonCore::GluonObject* theChild = object->child( i );
            if( theChild )
            {
                if( qobject_cast<GluonEngine::Asset*>( theChild ) )
                    continue;
                if( qobject_cast<GluonEngine::Scene*>( theChild ) )
                    continue;
                if( theChild->metaObject()->className() == QString( "GluonCore::GluonObject" ) )
                    continue;
                appendObject( theChild );
            }
        }
        d->layout->addStretch();

        QWidget* containerWidget = new QWidget( this );
        containerWidget->setLayout( d->layout );

        setWidget( containerWidget );
        setWidgetResizable( true );
    }
}

void PropertyWidget::clear()
{
    widget()->deleteLater();
}

void PropertyWidget::appendObject( GluonCore::GluonObject* obj, bool first )
{
    if( !first && obj->metaObject()->className() == QString( "GluonEngine::GameObject" ) )
    {
        return;
    }

    d->layout->addWidget( new PropertyWidgetContainer( obj, this ) );
}

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


#include "projectinspectorwindow.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QTreeView>
#include <QtGui/QDesktopWidget>
#include <QtGui/QApplication>

#include <engine/game.h>

#include "qobjecttreemodel.h"
#include "propertylist.h"

using namespace GluonCreator;

class ProjectInspectorWindow::Private
{
    public:
        PropertyList* propertyList;
};

ProjectInspectorWindow::ProjectInspectorWindow( QWidget* parent, Qt::WindowFlags f )
    : QDialog( parent, f ), d( new Private )
{
    QTreeView* view = new QTreeView( this );
    connect( view, SIGNAL(activated(QModelIndex)), SLOT(activated(QModelIndex)) );
    QObjectTreeModel* model = new QObjectTreeModel( GluonEngine::Game::instance()->gameProject(), this );

    view->setModel( model );

    d->propertyList = new PropertyList( this );

    QHBoxLayout* layout = new QHBoxLayout( this );
    layout->addWidget( view );
    layout->addWidget( d->propertyList );
    setLayout(layout);
}

ProjectInspectorWindow::~ProjectInspectorWindow()
{

}

QSize ProjectInspectorWindow::sizeHint() const
{
    int width = QApplication::desktop()->screenGeometry().width() / 2;
    int height = QApplication::desktop()->screenGeometry().height();

    return QSize( width, height );
}

void ProjectInspectorWindow::activated(const QModelIndex& index)
{
    if( index.isValid() )
    {
        QObject* obj = static_cast< QObject* >( index.internalPointer() );

        d->propertyList->setObject( obj );
    }
}

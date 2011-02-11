/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#include "gamewindowmanager.h"
#include "models/gameitemsmodel.h"

#include <player/lib/authentication.h>
#include <graphics/renderwidget.h>

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtGui/QGraphicsObject>
#include <QtGui/QApplication>
#include <QtCore/QSharedPointer>
#include <QtCore/QDebug>

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    app.setOrganizationName( "KDE Gluon" );
    app.setApplicationName( "Gluon QML Player" );

    QSharedPointer<GluonQMLPlayer::GameItemsModel> gameItemsModel = QSharedPointer<GluonQMLPlayer::GameItemsModel>(new GluonQMLPlayer::GameItemsModel());
    GluonPlayer::Authentication* auth = GluonPlayer::Authentication::instance();

    QSharedPointer<QDeclarativeView> view = QSharedPointer<QDeclarativeView>(new QDeclarativeView());
    QSharedPointer<GluonGraphics::RenderWidget> renderWidget = QSharedPointer<GluonGraphics::RenderWidget>(new GluonGraphics::RenderWidget( 0 ));
    QSharedPointer<GluonQMLPlayer::GameWindowManager> gameWindowManager= QSharedPointer<GluonQMLPlayer::GameWindowManager>(new GluonQMLPlayer::GameWindowManager(renderWidget.data(), view.data(), gameItemsModel.data()));

    QDeclarativeContext *ctxt = view->rootContext();
    ctxt->setContextProperty( "authentication", auth );
    ctxt->setContextProperty( "gameItemsModel", gameItemsModel.data() );
    ctxt->setContextProperty( "gameWindowManager", gameWindowManager.data() );

    view->setSource( QUrl( "qrc:/main.qml" ) );
    view->setViewport(renderWidget.data());
    view->show();

    QObject* obj = view->rootObject();
    QObject* login = obj->findChild<QObject*>( "login" );
    QObject::connect( auth, SIGNAL( initialized() ), login, SLOT( providerSet() ) );

    return app.exec();
}

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

#include "lib/models/gameviewitem.h"
#include "lib/models/gameitemsmodel.h"
#include "lib/models/commentitemsmodel.h"
#include "lib/authentication.h"

#include <graphics/renderwidget.h>

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative>
#include <QtGui/QGraphicsObject>
#include <QtGui/QApplication>

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    app.setOrganizationName( "KDE Gluon" );
    app.setApplicationName( "Gluon QML Player" );

    GluonPlayer::GameItemsModel gameItemsModel;
    GluonPlayer::CommentItemsModel commentItemsModel;
    GluonPlayer::Authentication* auth = GluonPlayer::Authentication::instance();

    QDeclarativeView view;
    GluonGraphics::RenderWidget renderWidget(&view);
    renderWidget.initializeGL();
    GluonQMLPlayer::GameWindowManager gameWindowManager(&renderWidget, &view, &gameItemsModel);

    QDeclarativeContext *ctxt = view.rootContext();
    ctxt->setContextProperty( "authentication", auth );
    ctxt->setContextProperty( "gameItemsModel", &gameItemsModel );
    ctxt->setContextProperty( "commentItemsModel", &commentItemsModel );
    ctxt->setContextProperty( "gameWindowManager", &gameWindowManager );

	// Note QML enum handling is more or less bonkers at the moment
	// It should be removed after the QML enum support is not that flaky
	qmlRegisterUncreatableType<GluonPlayer::GameViewItem>("GluonPlayerGameViewItem", 1, 0, "GameViewItem", QString("Support the Status enumeration"));

    view.setSource( QUrl( "qrc:/main.qml" ) );
    view.setViewport(&renderWidget);
    view.setFocus();
    view.show();

    QObject* obj = view.rootObject();
    QObject* login = obj->findChild<QObject*>( "login" );
    QObject::connect( auth, SIGNAL( initialized() ), login, SLOT( providerSet() ) );

    return app.exec();
}

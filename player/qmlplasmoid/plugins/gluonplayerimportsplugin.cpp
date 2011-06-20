/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "gluonplayerimportsplugin.h"

#include "gluonplayeradapter.h"

#include <lib/models/allgameitemsmodel.h>
#include <lib/models/gameitem.h>
#include <lib/ocsprovider.h>
#include <lib/ocsgamedownloadprovider.h>

#include <QtDeclarative/qdeclarative.h>

using namespace GluonPlayer;

void GluonPlayerImportsPlugin::registerTypes(const char* uri)
{
    qmlRegisterType<AllGameItemsModel>(uri, 0, 1, "AllGameItemsModel");

    qmlRegisterUncreatableType<GameItem>(uri, 0, 1, "GameItem", "GameItem is not meant to be instantiated \
        directly, it is provided only only to access Status enums");

    qmlRegisterUncreatableType<OcsProvider>(uri, 0, 1, "OcsProvider", "OcsProvider is not meant to be \
        instantiated directly. Use the GluonPlayerAdapter to obtain an instance.");

    qmlRegisterType<GluonPlayerAdapter>(uri, 0, 1, "GluonPlayerAdapter");

    qmlRegisterUncreatableType<OcsGameDownloadProvider>(uri, 0, 1, "OcsGameDownloadProvider",
        "OcsGameDownloadProvider is not meant to be instantiated directly, only OcsProvider will create and return \
        an instance");
}

#include "gluonplayerimportsplugin.moc"

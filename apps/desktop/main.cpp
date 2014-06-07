/*
    This file is part of KDE.

    Copyright 2010 Claudio Desideri <happy.snizzo@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "qtquick2controlsapplicationviewer.h"

//player lib inclusions
#include <gluon_global.h>
#include <core/directoryprovider.h>
#include <core/gluonobjectfactory.h>
 
#include <player/gamemetadata.h>
#include <player/gamemanager.h>
#include <player/models/commentitemsmodel.h>
#include <player/serviceprovider.h>
#include <player/models/allgameitemsmodel.h>
#include <player/models/gameitem.h>
#include <player/gamedownloadjob.h>

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    GluonCore::GluonObjectFactory::instance()->loadPlugins();
    
    QtQuick2ControlsApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("main.qml"));
    viewer.show();

    return app.exec();
}


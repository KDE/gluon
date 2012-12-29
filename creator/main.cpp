/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "mainwindow.h"

#include <unistd.h>

#include <KDE/KSplashScreen>
#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KStandardDirs>

#include "aboutdata.h"

int main( int argc, char** argv )
{
    KAboutData aboutData = GluonCreator::aboutData();

    KCmdLineArgs::init( argc, argv, &aboutData );
    KCmdLineOptions options;
    options.add( "+project", ki18n( "Project to open" ) );
    KCmdLineArgs::addCmdLineOptions( options );

    KApplication app;
    KCmdLineArgs* args = KCmdLineArgs::parsedArgs();

    //Create and show a splashscreen
    KSplashScreen splash( QPixmap( KGlobal::dirs()->locate( "appdata", "gluon-creator-splash.png" ) ) );
    splash.show();
    app.processEvents();

    //Create the main window
    GluonCreator::MainWindow* window = new GluonCreator::MainWindow( args->count() > 0 ? args->arg( 0 ) : QString() );
    window->show();
    splash.finish( window );

    app.exec();
}

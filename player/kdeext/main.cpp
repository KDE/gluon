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

#include "mainwindow.h"

#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KMessageBox>

#include <QtCore/QFile>

int main( int argc, char** argv )
{
    KAboutData aboutData( "gluon_kdeextplayer", "plasma_applet_gluonplayer",
                          ki18n( "KDE Extended Player" ), GLUON_VERSION_STRING.toUtf8(),
                          ki18n( "KDE Frontend Player for Gluon games." ),
                          KAboutData::License_LGPL_V2,
                          ki18n( "Copyright 2010 Laszlo Papp" ),
                          KLocalizedString(),
                          "???"
                        );

    aboutData.setProgramIconName( "KDEEXTPlayer" );
    aboutData.addAuthor( ki18n( "Laszlo Papp" ), ki18n( "KDE Extended Player" ), "" );
    aboutData.setProductName( "gluon/gluonplayer" );

    KCmdLineArgs::init( argc, argv, &aboutData );
    KCmdLineOptions options;

    options.add( "+file", ki18n( "File to open" ) );
    KCmdLineArgs::addCmdLineOptions( options );

    KApplication app;

    if( argc > 1 && !QFile::exists( argv[1] ) )
    {
        if( KMessageBox::warningContinueCancel( 0, i18n( "File does not exist: %1! Do you want to continue?" ).arg( argv[1] ), i18n( "Continue?" ),
                                                KStandardGuiItem::cont(), KStandardGuiItem::quit() ) == KMessageBox::Cancel )
            return 1;

    }

    KCmdLineArgs* args = KCmdLineArgs::parsedArgs();

    GluonKDEPlayer::MainWindow* window = new GluonKDEPlayer::MainWindow( args->count() ? args->arg( 0 ) : "" );
    window->show();

    app.exec();
}


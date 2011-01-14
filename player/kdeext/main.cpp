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

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

int main( int argc, char** argv )
{
    KAboutData aboutData("gluon_kdeextplayer", NULL,
                          ki18n("KDE Extended Player"), GLUON_VERSION_STRING.toUtf8(),
                          ki18n((QString("KDE Frontend Player for Gluon games.\nVersion %2").arg(GLUON_VERSION_STRING)).toUtf8()),
                          KAboutData::License_LGPL_V2,
                          ki18n("Copyright 2010 Laszlo Papp"),
                          KLocalizedString(),
                          "???"
                        );

    aboutData.setProgramIconName("KDEEXTPlayer");
    aboutData.addAuthor(ki18n("Laszlo Papp"), ki18n("KDE Extended Player"), "");

    KCmdLineArgs::init(argc, argv, &aboutData);
    KCmdLineOptions options;

    options.add("+file", ki18n("File to open"));
    KCmdLineArgs::addCmdLineOptions(options);

    KApplication app;

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    GluonKDEExtPlayer::MainWindow *window;
    if (args->count())
        window = new GluonKDEExtPlayer::MainWindow(args->arg(0));
    else
        window = new GluonKDEExtPlayer::MainWindow();

    window->show();
    app.exec();
}


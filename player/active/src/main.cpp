/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright 2011 Sebastian Kügler <sebas@kde.org>
 * Copyright 2011 Marco Martin <mart@kde.org>
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

// KDE
#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KDebug>
#include <KDE/KLocale>
#include <KToolBar>

// Own
#include "mainwindow.h"

static const char description[] = I18N_NOOP("Gluon Player for Tablets");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("gluonplayer-active", 0, ki18n("Gluon Player"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("Copyright 2011 Shantanu Tushar"), KLocalizedString(), 0, "jhahoneyk@gmail.com");
    about.addAuthor( ki18n("Shantanu Tushar"), KLocalizedString(), "jhahoneyk@gmail.com" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
#ifndef QT_NO_OPENGL
    options.add("opengl", ki18n("use a QGLWidget for the viewport"));
#endif
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    bool useGL = args->isSet("opengl");

    if (!useGL) {
        //use plasmarc to share this with plasma-windowed
        KConfigGroup cg(KSharedConfig::openConfig("plasmarc"), "General");
        useGL = cg.readEntry("UseOpenGl", true);
    }

    QString url;
    if (args->count() > 0) {
        url = args->arg(0);
    }

    MainWindow *mainWindow = new MainWindow(url);
    mainWindow->setUseGL(useGL);
    mainWindow->show();
    args->clear();
    return app.exec();
}

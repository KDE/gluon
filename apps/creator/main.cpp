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

#include <KCoreAddons/KAboutData>
#include <KI18n/KLocalizedString>

#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtWidgets/QApplication>

#include "aboutdata.h"

int main( int argc, char** argv )
{
    QApplication app(argc, argv);
    
    KAboutData aboutData = GluonCreator::aboutData();
    KAboutData::setApplicationData(aboutData);
    
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    //PORTING SCRIPT: adapt aboutdata variable if necessary
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);
    parser.addOption(QCommandLineOption(QStringList() <<  QLatin1String("+project"), i18n( "Project to open" )));

    QStringList posArgs = parser.positionalArguments();

    //Create the main window
    GluonCreator::MainWindow* window = new GluonCreator::MainWindow( posArgs.count() > 0 ? posArgs.at(0) : QString() );
    window->show();
    app.setActiveWindow(window);
    app.exec();
}

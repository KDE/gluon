/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#include "mainwindow.h"

#include <Plasma/Theme>

#include <KDE/KAction>
#include <KDE/KIcon>
#include <KDE/KStandardAction>

MainWindow::MainWindow()
    : KMainWindow()
{
    setAcceptDrops(true);
    KConfigGroup cg(KSharedConfig::openConfig("plasmarc"), "Theme-plasma-mobile");
    const QString themeName = cg.readEntry("name", "air-mobile");
    Plasma::Theme::defaultTheme()->setUseGlobalSettings(false);
    Plasma::Theme::defaultTheme()->setThemeName(themeName);
    addAction(KStandardAction::close(this, SLOT(close()), this));
    addAction(KStandardAction::quit(this, SLOT(close()), this));
    m_widget = new AppView(this);

    restoreWindowSize(config("Window"));
    setCentralWidget(m_widget);
}

MainWindow::~MainWindow()
{
    saveWindowSize(config("Window"));
}

KConfigGroup MainWindow::config(const QString &group)
{
    return KConfigGroup(KSharedConfig::openConfig("gluonplayeractiverc"), group);
}

QString MainWindow::name()
{
    return "Gluon Player";
}

QIcon MainWindow::icon()
{
    return KIcon("gluon-install");
}

void MainWindow::setUseGL(const bool on)
{
    m_widget->setUseGL(on);
}

bool MainWindow::useGL() const
{
    return m_widget->useGL();
}

#include "mainwindow.moc"

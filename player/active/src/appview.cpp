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

#include "appview.h"

#include <lib/models/installedgamesmodel.h>
#include <lib/models/downloadablegamesmodel.h>

#include <engine/projectmetadata.h>

#include <Plasma/Package>
#include <kdeclarative.h>
#include <KShell>
#include <KStandardDirs>
#include <KDebug>

#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeItem>
#include <QFileInfo>
#include <QScriptValue>
#include <QGLWidget>
#include <lib/models/allgameitemsmodel.h>

AppView::AppView(const QString &url, QWidget *parent)
    : QDeclarativeView(parent),
      m_useGL(false)
{
    // avoid flicker on show
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);

    setResizeMode(QDeclarativeView::SizeRootObjectToView);

    KDeclarative kdeclarative;
    kdeclarative.setDeclarativeEngine(engine());
    kdeclarative.initialize();
    //binds things like kconfig and icons
    kdeclarative.setupBindings();

    Plasma::PackageStructure::Ptr structure = Plasma::PackageStructure::load("Plasma/Generic");
    m_package = new Plasma::Package(QString(), "org.kde.gluon.player", structure);

    rootContext()->setContextProperty("installedGamesModel", new GluonPlayer::InstalledGamesModel(this));
    rootContext()->setContextProperty("downloadableGamesModel", new GluonPlayer::DownloadableGamesModel(this));

    setSource(QUrl(m_package->filePath("mainscript")));
    show();

    onStatusChanged(status());

    connect(this, SIGNAL(statusChanged(QDeclarativeView::Status)),
            this, SLOT(onStatusChanged(QDeclarativeView::Status)));
}

AppView::~AppView()
{
}

void AppView::setUseGL(const bool on)
{
#ifndef QT_NO_OPENGL
    if (on) {
        QGLWidget *glWidget = new QGLWidget;
        glWidget->setAutoFillBackground(false);
        setViewport(glWidget);
    }
#endif
    m_useGL = on;
}

bool AppView::useGL() const
{
    return m_useGL;
}

void AppView::onStatusChanged(QDeclarativeView::Status status)
{
    kDebug() << "STATUS " << status;
}

#include "appview.moc"

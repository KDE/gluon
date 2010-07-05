/*
*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "gluonviewerpart.h"
#include <graphics/glwidget.h>
#include <engine/gameproject.h>
#include <engine/game.h>

#include <QtGui/QWidget>
#include <kdemacros.h>
#include <kparts/genericfactory.h>
#include <KDE/KUrl>
#include <QtCore/QThread>

using namespace GluonCreator;

class GluonViewerPart::GameRunner : public QThread
{
    public:
        GameRunner(QObject* parent = 0) : QThread(parent) { }
        virtual void run()
        {
            GluonEngine::Game::instance()->runGame();
        }
};

class GluonViewerPart::GluonViewerPartPrivate
{
    public:
        GluonGraphics::GLWidget *widget;
        GluonEngine::GameProject *project;

        GameRunner *runner;
};

GluonCreator::GluonViewerPart::GluonViewerPart(QWidget* parentWidget, QObject* parent, const QVariantList& )
    : ReadOnlyPart(parent),
      d(new GluonViewerPartPrivate)
{
    Q_UNUSED(parentWidget)
    
    d->widget = new GluonGraphics::GLWidget();
    setWidget(d->widget);

    connect(GluonEngine::Game::instance(), SIGNAL(painted(int)), d->widget, SLOT(updateGL()));
}

GluonCreator::GluonViewerPart::~GluonViewerPart()
{
    if(d->runner->isRunning())
        d->runner->exit();
    delete d;
}

bool GluonCreator::GluonViewerPart::openFile()
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    d->project = new GluonEngine::GameProject();
    d->project->loadFromFile(url());

    GluonEngine::Game::instance()->setGameProject(d->project);
    GluonEngine::Game::instance()->setCurrentScene(d->project->entryPoint());

    d->runner = new GameRunner(this);
    d->runner->start();

    return true;
}

K_PLUGIN_FACTORY(GluonViewerPartFactory, registerPlugin<GluonViewerPart>();)
K_EXPORT_PLUGIN(GluonViewerPartFactory("GluonViewerPart","GluonViewerPart"))

#include "gluonviewerpart.moc"

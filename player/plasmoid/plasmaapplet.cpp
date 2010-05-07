/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Shantanu Tushar Jha <jhahoneyk@gmail.com>
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

#include "plasmaapplet.h"

#include <engine/game.h>
#include <engine/gameproject.h>
#include <graphics/glwidget.h>
#include <engine/scene.h>
#include <graphics/item.h>
#include <graphics/camera.h>
#include <models/gamesmodel.h>

#include <QFileDialog>
#include <QTimer>
#include <QGraphicsSceneResizeEvent>

using namespace GluonPlayer;
using namespace GluonGraphics;

PlasmaApplet::PlasmaApplet(QObject* parent, const QVariantList& args): GLFBOApplet(parent, args),
                            m_viewportWidth(0), m_viewportHeight(0), m_project(0), m_camera(0)
{
}

PlasmaApplet::~PlasmaApplet()
{
    if (m_gameFileName.isEmpty()) {
        return;
    }
    GluonEngine::Game::instance()->stopGame();
    GluonEngine::Game::instance()->cleanupAll();
}

void PlasmaApplet::init()
{
    m_gamesModel = new GamesModel(this);
    qDebug() << m_gamesModel->data(m_gamesModel->index(0, 0)).toString();
    QTimer::singleShot(1000, this, SLOT(openProject()));
}

void PlasmaApplet::openProject()
{
    setBusy(true);
    /*m_gameFileName = QFileDialog::getOpenFileName(0, tr("Please select a project"),
                                                    QString(), tr("Gluon Project Files (*.gluon)"));*/
    m_gameFileName = m_gamesModel->data(m_gamesModel->index(0, 0)).toString();
    if (m_gameFileName.isEmpty()) {
        return;
    }

    initGL();
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    m_project = new GluonEngine::GameProject();
    m_project->loadFromFile(QUrl(m_gameFileName));
    GluonEngine::Game::instance()->setGameProject(m_project);
    GluonEngine::Game::instance()->setCurrentScene(m_project->entryPoint());

    connect(GluonEngine::Game::instance(), SIGNAL(painted(int)), this, SLOT(doPaint()));
    QTimer::singleShot(1000, this, SLOT(startGame()));
}

void PlasmaApplet::doPaint()
{
    makeCurrent();
    update();
}

void PlasmaApplet::startGame()
{
    setBusy(false);
    GluonEngine::Game::instance()->runGame();
}

void PlasmaApplet::initGL()
{
    m_camera = Engine::instance()->activeCamera();
    connect(Engine::instance(), SIGNAL(activeCameraChanged(GluonGraphics::Camera*)),
            SLOT(setCamera(GluonGraphics::Camera*)));

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glAlphaFunc(GL_GREATER, 0.01);

}

void PlasmaApplet::resizeEvent(QGraphicsSceneResizeEvent* event)
{
    m_viewportWidth = event->newSize().width();
    m_viewportHeight = event->newSize().height();

    if (m_camera) {
        m_camera->setViewport(0, 0, m_viewportWidth, m_viewportHeight);
        m_camera->applyViewport();
        m_camera->applyOrtho();
    }
}


void PlasmaApplet::setCamera(Camera* camera)
{
    m_camera = camera;
}

void PlasmaApplet::render()
{
    Engine::instance()->sortItems();
    QList<Item*> items = Engine::instance()->items();
    foreach(Item *it, items) {
        it->paintGL();
    }
}

void PlasmaApplet::paintGLInterface(QPainter* painter, const QStyleOptionGraphicsItem* option)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);

    glScissor(0, 0, 400, 400);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_camera) {
        m_camera->applyView();
    }

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    render();
    glPopAttrib();
}

#include "plasmaapplet.moc"
/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include <QtCore/QTimer>

#include <graphics/renderwidget.h>
#include <graphics/camera.h>
#include <graphics/item.h>
#include <graphics/particles/particlemesh.h>
#include <graphics/engine.h>
#include <graphics/frustrum.h>
#include <material.h>
#include <QMatrix4x4>
#include <core/directoryprovider.h>

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
{
    m_widget = new GluonGraphics::RenderWidget( this );
    setCentralWidget( m_widget );

    QTimer::singleShot(0, this, SLOT(initialize()));
}

void MainWindow::initialize()
{
    GluonGraphics::Camera* cam = new GluonGraphics::Camera();
    cam->frustrum()->setOrthographic( -50.f, 50.f, -50.f, 50.f, -50.f, 50.f );
    GluonGraphics::Engine::instance()->setActiveCamera( cam );

    m_mesh = new GluonGraphics::ParticleMesh( this );
    m_mesh->initialize();
    GluonGraphics::Engine::instance()->addMesh( "particle", m_mesh );
    m_item = GluonGraphics::Engine::instance()->createItem( "particle" );

    GluonGraphics::Material* mat = GluonGraphics::Engine::instance()->createMaterial("blank");
    mat->load(QUrl( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/example_particles.gluonmaterial"));
    mat->build();
    m_item->setMaterialInstance(mat->createInstance("default"));

    m_timer = new QTimer( this );
    connect(m_timer, SIGNAL(timeout()), SLOT(render()));
    m_timer->start(16);
}

void MainWindow::render()
{
    m_mesh->update();
    m_itemMatrix.rotate(3.1415927 * 0.5, 0, 0, 1);
    m_item->setTransform(m_itemMatrix);
    m_widget->update();
}

#include "mainwindow.moc"

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
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

#include "renderwidget.h"

#include <core/debughelper.h>
#include "engine.h"
#include "camera.h"
#include "frustrum.h"

using namespace GluonGraphics;

class RenderWidget::RenderWidgetPrivate
{
    public:
};

RenderWidget::RenderWidget(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f) :
        QGLWidget(parent, shareWidget, f),
        d(new RenderWidgetPrivate)
{

}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPointSize(32);

    Engine::instance()->initialize();
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Engine::instance()->render();
}

void RenderWidget::resizeGL( int w, int h )
{
    glViewport(0, 0, w, h);

    Engine::instance()->setFramebufferSize(w, h);
}

#include "renderwidget.moc"

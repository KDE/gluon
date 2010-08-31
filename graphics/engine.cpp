/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "engine.h"

#include <QtCore/QDebug>
#include <QtOpenGL/QGLFramebufferObject>

#include "camera.h"
#include "item.h"
#include <QCoreApplication>
#include <QApplication>
#include "materialinstance.h"

using namespace GluonGraphics;

template<> Engine *GluonCore::Singleton<Engine>::m_instance = 0;

class Engine::EnginePrivate
{
    public:
        QGLFramebufferObject * fbo;
        QVector<Item*> items;
        MaterialInstance * fboShader;
};

void
Engine::render()
{
    //Bind the framebuffer object so we render to it.
    d->fbo->bind();

    //Walk through all items, rendering them as we go
    QVectorIterator<Item*> itr = d->items;
    while(itr.hasNext())
    {
        itr.next()->render();
    }

    //Unbind the FBO, making us stop rendering to it.
    d->fbo->release();

    //Render a full screen quad with the FBO data.
    
    /*d->fboShader->bind();
    glDrawArrays(GL_TRIANGLES, );
    d->fboShader->release();*/
}

Engine::Engine()
    : d(new EnginePrivate())
{
    d->fbo = new QGLFramebufferObject(2048, 2048);
}

Engine::~Engine()
{
    delete d->fbo;
    delete d;
}

#include "engine.moc"

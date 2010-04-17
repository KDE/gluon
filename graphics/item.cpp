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

#include "item.h"
#include "engine.h"

#include <core/debughelper.h>

namespace GluonGraphics
{


    Item::Item(QObject * parent)
            : Transform(parent)
    {
        m_mesh = new Mesh;
        init();
    }

    //------------------------------------------------------------
    Item::Item(Mesh * mesh , QObject * parent)
            : Transform(parent)
    {
        m_mesh = mesh;
        init();
    }
    //------------------------------------------------------------

    Item::~Item()
    {
        Engine::instance()->removeItem(this);
        delete m_mesh;
        m_mesh = 0;
    }

    void Item::init()
    {
        Engine::instance()->addItem(this);
        setObjectName(metaObject()->className());
        mProgram = 0;
    }
    //------------------------------------------------------------

    void  Item::paintGL()
    {
        glPushMatrix();
        glMultMatrixd((GLdouble*)matrix().data());

        if (mProgram != 0)
            mProgram->bind();

        m_mesh->texture()->bind();
        drawMesh();
        m_mesh->texture()->unBind();

        if (mProgram != 0)
            mProgram->release();


        glPopMatrix();
    }
    //------------------------------------------------------------
    void Item::drawMesh()
    {

        glPolygonMode(GL_FRONT_AND_BACK, mesh()->glMode());


        /*enable client state */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        /* send data */
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), m_mesh->vertexArray());
        glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), m_mesh->texCoordsArray());
        glColorPointer(4, GL_FLOAT, sizeof(Vertex), m_mesh->colorArray());

        //    /* create vertex */
        glDrawArrays(mesh()->glMode(), 0, m_mesh->vertexCount());

        /* disable client state */
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);


    }
    //------------------------------------------------------------

    void Item::setColor(const QColor& col)
    {
        if (m_mesh)
            m_mesh->setColor(col);
    }
    //------------------------------------------------------------
    void Item::setAlpha(const float& alpha)
    {
        if (m_mesh)
            m_mesh->setAlpha(alpha);

    }
    //------------------------------------------------------------
    const QColor& Item::color()
    {
        return m_mesh->color();
    }
    //------------------------------------------------------------
    const float& Item::alpha()
    {
        return m_mesh->alpha();
    }
    //------------------------------------------------------------
    void Item::setTexture(Texture * texture)
    {
        m_mesh->setTexture(texture);
    }
    //------------------------------------------------------------
    void Item::setTexture(const QPixmap& pix)
    {
        m_mesh->setTexture(pix);
    }
    //------------------------------------------------------------
    void Item::setTexture(const QImage& img)
    {
        m_mesh->setTexture(img);
    }
    //------------------------------------------------------------
    void Item::setTexture(const QString& path)
    {
        m_mesh->setTexture(path);
    }
    //------------------------------------------------------------
    void Item::setShader(QGLShaderProgram* program)
    {
        mProgram = program;
    }
    void Item::removeShader()
    {
        mProgram = 0 ;
    }
}

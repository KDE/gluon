/*
 * This file is part of the Gluon library.
 * Copyright 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright 2008 Charles Huet <packadal@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <GL/glew.h>
#include "kglparticlesitem.h"
#include <QtCore/QDebug>
#include <QtCore/QDateTime>

#include <iostream>
using namespace std;

KGLParticle::KGLParticle()
{
    init();
}

void KGLParticle::init()
{
    m_alpha =1;
    m_initAlpha=m_alpha;
    m_alphaStep = 0.01f;

    m_col = Qt::white;
    m_initCol = m_col;
    m_colStep = QColor(0,0,0);

    m_pos   =QPointF(0,0);
    m_initPos = m_pos;

    m_direction = QPointF(1,1);
    m_speed = 0.01f;
    m_size = 20;

    m_tex = new KGLTexture();
}

void KGLParticle::move()
{
    m_pos += m_direction*m_speed;

    m_alpha-=m_alphaStep;

    m_col.setRed(m_col.red() + m_colStep.red());
    m_col.setGreen(m_col.green() + m_colStep.green());
    m_col.setBlue(m_col.blue() + m_colStep.blue());

    if ( m_alpha <= 0)
    {
        reset();
    }
}

//===============================================================================================

KGLParticlesItem::KGLParticlesItem(KGLEngine * parent)
    : KGLItem(parent)
{
    qsrand(QDateTime::currentDateTime ().toTime_t ());
}

void KGLParticlesItem::paintGL()
{
 glPushMatrix();
glLoadMatrixf(matrix().data());


    foreach(KGLParticle * p, m_particles)
    {
        glEnable(GL_POINT_SPRITE);
        p->tex()->bind();
        glEnable(GL_BLEND);
        //TODO the user should be able to chose the blendFunc
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glBlendFunc (GL_DST_COLOR, GL_ZERO);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glTexEnvf(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
        glPointSize(p->size());
        glBegin(GL_POINTS);
        const float r = (float)p->color().red() / 255;
        const float g = (float)p->color().green() / 255;
        const float b = (float)p->color().blue() / 255;
        glColor4f(r, g, b,p->alpha());
        glVertex2f(p->position().x(), p->position().y());
        glEnd();
        glDisable(GL_POINT_SPRITE);
        glDisable(GL_BLEND);
        p->tex()->unBind();

        p->move();
    }
    glPopMatrix();
}

//=================================================================================

//KGLParticlesExploseItem::KGLParticlesExploseItem(unsigned int number, unsigned int angle, KGLEngine * parent)
//           :KGLParticlesItem(parent)
//{
//
// for ( int i=0; i<number; ++i)
//    {
//     KGLParticle *  p = new KGLParticle;
//        float a = (qrand()%angle) * M_PI / 180;
//        p->setDirection(QPointF(cos(a),sin(a)));
//        addParticles(p);
//    }
//
//
//
//}

void KGLParticlesItem::createExplose(unsigned int number,QPixmap texture,const double angle, float speed, float alphaStep,float size)
{
    for (unsigned int i=0; i<number; ++i)
    {
        KGLParticle *  p = new KGLParticle;
        float a = (qrand()%(int)angle) * M_PI / 180;
        p->setDirection(QPointF(cos(a),sin(a)));
        p->setSpeed(speed);
        p->setSize(size);
        p->setTexture(texture);
        p->setAlphaStep(alphaStep);
        addParticles(p);
    }
}

void KGLParticlesItem::createSmoke(unsigned int number,QPixmap texture,const double angle, float speed, float alphaStep,float size)
{
    for ( unsigned int counter=0; counter<number; ++counter)
    {
        KGLParticle *  p = new KGLParticle;
        float a = (qrand()%(int)angle) * M_PI / 180;
        p->setDirection(QPointF(cos(a),sin(a)));
        p->setTexture(texture);
        p->setSpeed(speed);
        p->setAlphaStep(alphaStep);
        p->setSize(size);
        float nbStep = p->alpha() / alphaStep;
        int i = qrand()%(int)nbStep;
        p->setPosition(p->position() + (p->direction()*p->speed()*i));
        p->setAlpha(1 - ( alphaStep*i));
        p->setInitPosition(QPointF(0,0));
        addParticles(p);
    }
}

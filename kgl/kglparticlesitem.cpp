/*
 * This file is part of the KGLEngine2D project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "kglparticlesitem.h"
#include "kglengine2d.h"
#include "kglparticle.h"

#include <cmath>

KGLParticlesItem::KGLParticlesItem(const GLint &texture, int nbParticules) :
        KGLItem()
{
    m_angleSpan = 360;
    m_speed = 0.001;
    m_alphaStep = 0.001;
    m_pointSize = 20;
    m_texture = texture;
    m_modeRandom = true;
    m_finish = false;
    m_repeat = true;
    m_nbParticles = nbParticules;
    m_count = 0;
    m_maxCount = 4;
}

void KGLParticlesItem::create()
{
    if (m_particles.size() > 0) {
        for (VECTOR_PARTICULES::iterator i = m_particles.begin(); i != m_particles.end(); ++i) {
            createParticle(*i);
        }
    } else {
        for (uint i = 0; i < m_nbParticles; ++i) {
            m_particles.push_back(createParticle());
        }
    }

    m_isCreated = true;
}

KGLParticle* KGLParticlesItem::createParticle(KGLParticle* p)
{
    if (p == 0) {
        p = new KGLParticle();
        const int angleS = m_angleSpan / 2;
        const float angle = (rand() % (angleS + angleS) - angleS) * M_PI / 180;
        //p->setDirection(cos(angle) * m_speed, sin(angle) * m_speed);
        p->rotate((rand() % 360) * M_PI / 180);
        if (m_modeRandom)
            p->repeatMove(rand() % 100);
    }

    p->setPosition(QPointF());
    p->setAlpha(1);
    p->setDecrAlpha(m_alphaStep);

    return p;
}

void KGLParticlesItem::draw()
{
    if (!m_isCreated) {
        create();
    }

    if (!m_finish) {
        glPushMatrix();

        glLoadMatrixd(m_matrix.data());

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glEnable(GL_BLEND);
        //TODO the user should be able to chose the blendFunc
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glBlendFunc (GL_DST_COLOR, GL_ZERO);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glDepthMask(GL_FALSE);

        glEnable(GL_POINT_SPRITE);
        glTexEnvf(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
        glPointSize(m_pointSize);

        for (VECTOR_PARTICULES::iterator i = m_particles.begin(); i != m_particles.end(); ++i) {
            KGLParticle* p = *i;
            glBegin(GL_POINTS);
            glColor4f(1, 1, 1, p->alpha());
            glVertex2d(p->position().x(), p->position().y());

            glEnd();
            p->move();
            if (p->isDead()) {
                createParticle(p);
                m_count++;
                if (m_count / m_nbParticles >= m_maxCount) {
                    m_finish = true; //allows to repeat m_maxCount times the particle engine when it's in random mode
                }
            }
        }

        glDepthMask(GL_TRUE);
        glDisable(GL_POINT_SPRITE);
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}

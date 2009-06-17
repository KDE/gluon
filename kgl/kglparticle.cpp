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

#include "kglparticle.h"

using namespace Eigen;

KGLParticle::KGLParticle(QPointF direction)
{
    m_direction = direction;
    m_alpha = 0.5;
    m_decrAlpha = 0.016;
    m_dead = 0;
}

KGLParticle::KGLParticle(const KGLParticle & p)
{
    m_speed = p.speed();
    m_position = p.position();
    m_angle = p.angle();

    m_alpha = p.m_alpha;
    m_decrAlpha = p.m_decrAlpha;
    m_dead = p.m_dead;
}

void KGLParticle::move()
{
    PhysicsItem::move();
    m_alpha -= m_decrAlpha;

    m_dead = m_alpha <= 0;
}

void KGLParticle::repeatMove(double r)
{
    for (double i = 0; i <= r / 100.; i += m_decrAlpha) {
        move();
    }
}

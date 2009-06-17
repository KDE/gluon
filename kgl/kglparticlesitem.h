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

#ifndef KGLPARTICLESITEM_H
#define KGLPARTICLESITEM_H

#include "kglitem.h"

class KGLParticle;

typedef std::vector<KGLParticle*> VECTOR_PARTICULES;

class KGLParticlesItem: public KGLItem
{
    Q_OBJECT
public:
    explicit KGLParticlesItem(const GLint &texture = 0, int nbParticules = 10);
    virtual void draw();

    inline void setNbParticles(uint nb) {
        m_nbParticles = nb;
        m_isCreated = false;
    }
    inline void setPointSize(float s) {
        m_pointSize = s;
        m_isCreated = false;
    }
    inline void setAngleSpan(int min) {
        m_angleSpan = min;
        m_isCreated = false;
    }
    inline void setParticleSpeed(float s) {
        m_speed = s;
        m_isCreated = false;
    }
    inline void setAlphaStep(float a) {
        m_alphaStep = a;
        m_isCreated = false;
    }
    inline void setRandom(bool r) {
        m_modeRandom = r;
        m_isCreated = false;
    }
    inline void setRepeat(bool r) {
        m_repeat = r;
        m_isCreated = false;
    }
    inline void setMaxCount(bool c) {
        m_maxCount = c;
    }

    inline void stop() {
        m_finish = true;
    }
    inline void start() {
        m_finish = false;
        m_count = 0;
    }
    inline void setTexture(const GLint &texture) {
        m_texture = texture;
    }

    inline bool isFinished() {
        return m_finish;
        m_isCreated = false;
    }

protected:
    virtual void create();

private:
    KGLParticle* createParticle(KGLParticle* p = 0);

    void addParticlesEffect(const GLint&, int) {}

    int m_angleSpan;
    float m_speed, m_alphaStep;

    unsigned int m_nbParticles;
    VECTOR_PARTICULES m_particles;
    float m_pointSize;
    GLint m_texture;

    bool m_modeRandom;
    bool m_finish;
    bool m_repeat;
    uint m_count;
    uint m_maxCount;

};

#endif //KGLPARTICLESITEM_H

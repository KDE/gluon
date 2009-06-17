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

#ifndef KGLPARTICLE_H
#define KGLPARTICLE_H

#include "kglphysicsitem.h"
#include "kglitemgroup.h"

const unsigned int LIVE = 1;
const unsigned int DEAD = 0;

class KGLParticle: public PhysicsItem
{
public:
    KGLParticle(QPointF direction = QPointF());
    KGLParticle(const KGLParticle&);

    void repeatMove(double r);

    inline float alpha() const {
        return m_alpha;
    }
    inline float decrAlpha() const {
        return m_decrAlpha;
    }
    inline bool isDead() const {
        return m_dead;
    }

    //setters
    inline void setAlpha(float a) {
        m_alpha = a;
    }
    inline void setDecrAlpha(float d) {
        m_decrAlpha = d;
    }

    virtual void move();

private:
    inline float width() const {
        return 0;
    }
    inline float height() const {
        return 0;
    }
    inline void translate(const QPointF&) {
    }
    using PhysicsItem::translate;
    inline void moveBy(const QPointF&) {
    }
    using PhysicsItem::moveBy;
    inline void setDirection(const QPointF&) {
    }
    using PhysicsItem::setDirection;
    inline QRectF transformBoundingRect() const {
        QRectF r;
        return r;
    }
    inline QPointF transformCenter() const {
        QPointF p;
        return p;
    }
    inline float radius() const {
        return 0.0;
    }
    inline void collidingWith(const KGLItemGroup&) {
    }
    inline const KGLItemGroup collidingItems() const {
        KGLItemGroup s;
        return s;
    }
    inline void updateMatrix() {
    }

    float m_alpha;
    float m_decrAlpha;

    bool m_dead;
};

#include <qmetaobject.h>
Q_DECLARE_METATYPE(KGLParticle)

#endif //KGLPARTICLE_H

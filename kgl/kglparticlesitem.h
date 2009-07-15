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

#include "kgltexture.h"
#include "kglitem.h"

class KGLParticle;
class KGLParticlesItem;
class KGLParticle
{
    public:
    KGLParticle();
    void init();
    void move();
    void reset(){m_alpha=m_initAlpha; m_pos=m_initPos;m_col=m_initCol;}
    void setColor(const QColor &col){m_col = col; m_initCol=col;}
    void setColorStep(const QColor &c){m_colStep = c;}
    void setPosition(const QPointF &p){m_pos = p;m_initPos=p;}
    void setInitPosition(const QPointF &p){m_initPos = p;}
    void setDirection (const QPointF &d){m_direction = d;}
    void setSpeed(const float &s){m_speed = s;}
    void setSize(const float &s){m_size =s;}
    void setAlpha(const float &a){m_alpha = a;}
    void setAlphaStep(const float &s){m_alphaStep = s;}
    void setTexture(const QString& name){m_tex = new KGLTexture(name);}
    void setTexture(const QPixmap& name){m_tex = new KGLTexture(name);}
    void setTexture(KGLTexture * t){m_tex = t;}
    const QPointF& position(){return m_pos;}
    const float& size(){return m_size;}
    const float& alpha(){return m_alpha;}
    const QColor& color(){return m_col;}
    const QPointF &direction(){return m_direction;}
    const float &speed(){return m_speed;}
    KGLTexture * tex(){return m_tex;}

    private:
    QColor m_col;
    QColor m_colStep;
    QColor m_initCol;
    float m_alpha;
    float m_alphaStep;
    float m_initAlpha;
    float m_size;
    QPointF m_pos;
    QPointF m_initPos;
    QPointF m_direction;

    float m_speed;
    KGLTexture * m_tex;

};
//========================================================
class KGLParticlesItem: public KGLItem
{
  public :
 KGLParticlesItem(KGLEngine * parent=0);
 virtual void draw();
void addParticles(KGLParticle * p){m_particles.append(p);}
QList<KGLParticle*> particles(){return m_particles;}
void createExplose(unsigned int number,KGLTexture t=KGLTexture(),const double angle=360, float speed=0.01, float alphaStep=0.01);
void createSmoke(unsigned int number,KGLTexture t=KGLTexture(),const double angle=360, float speed=0.01, float alphaStep=0.01);


private:
QList <KGLParticle*> m_particles;

};

//========================================================
//
//   DIFFERENTE PARTICLES ENGINES....
//
//========================================================












#endif //KGLPARTICLESITEM_H

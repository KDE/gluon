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

#include "kglintro.h"
#include "kglspriteitem.h"
#include "kglengine2d.h"
#include "textureManaging/kgltexturemanager.h"

#include <QTimer>

KGLIntroItem::KGLIntroItem(QObject * parent) :
        KGLContainerItem(parent)
{
    m_alpha = 0;
    m_asens = true;
    m_timer = new QTimer(this);
    m_timer->start(10);

    m_gear = new KGLSpriteItem(":gear.png");
    m_gear->scale(0.8);
//
//    m_gear2 = new KGLSpriteItem(":gear.png");
//    m_gear2->scale(0.6);
//    m_gear2->setPosition(0.35, 0.35);
//    m_gear2->rotate(90);
//
//    m_title = new KGLSpriteItem(":title.png");
//    m_title->moveBy(0.5, 0);
//
//    addChild(m_gear);
//    addChild(m_gear2);
//    addChild(m_title);
//
//    connect(m_timer, SIGNAL(timeout()), this, SLOT(anim()));
}

void KGLIntroItem::anim()
{
//    m_gear->setColor(QColor(255, 0, 0, m_alpha));
//    m_gear2->setColor(QColor(255, 255, 255, m_alpha));
//    m_title->setColor(QColor(255, 255, 255, m_alpha));
//
//    m_gear->rotate(0.007);
//    m_gear2->rotate(-0.00705);
//
//    m_alpha += (m_asens ? 0.5 : -0.5);
//
//    if (m_alpha >= 255 || m_alpha <= 0) {
//        m_asens = !m_asens;
//    }
}

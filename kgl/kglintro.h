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

#ifndef KGLINTRO_H
#define KGLINTRO_H

#include "kglcontaineritem.h"

class QTimer;
class KGLSpriteItem;

class KGLIntroItem: public KGLContainerItem
{
    Q_OBJECT
public:
    KGLIntroItem(QObject * parent=0);

public Q_SLOTS:

    /**
     * This function animates the introduction item, meaning the gears will spin.
     */
    virtual void anim();

private:
    KGLBoxItem* m_gear;
    KGLBoxItem* m_gear2;
    KGLBoxItem* m_title;
    QTimer* m_timer;
    double m_alpha;
    bool m_asens;
};
#endif //KGLINTRO_H

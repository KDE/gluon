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

#ifndef KGLINTRO_H
#define KGLINTRO_H

#include "kgl_export.h"
#include "kglpixmapitem.h"
#include "kglshadowitem.h"
 #include <QTimer>
#include <QTimeLine>

/**
 * \defgroup KGL KGL
 */
//@{


class KGL_EXPORT KGLIntroItem: public KGLItem
{
    Q_OBJECT
    public:
        KGLIntroItem(KGLEngine* parent=0);
    public Q_SLOTS:
     void anim(int id);

        private:
  KGLPixmapItem * m_item;
  KGLShadowItem * m_shadow;
        QTimeLine * m_timeLine;

};

//@}
#endif //KGLINTRO_H

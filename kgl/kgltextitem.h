/*
 * This file is part of the Gluon library.
 * Copyright 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright 2008 Charles Huet <packadal@gmail.com>
 * Copyright 2008 Guillaume Martres <smarter@ubuntu.com>
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

#ifndef KGLTEXTITEM_H
#define KGLTEXTITEM_H

#include <QFont>
#include <GL/glew.h>

#include "kgl_export.h"
#include "kglitem.h"

class QString;
class QColor;
class QFont;

/**
 * \defgroup KGL KGL
 */
//@{

/**
* @class KGLTextItem kgltextitem.h <KGLTextItem>
* This class provides an item that is used to display text.
*/
class KGL_EXPORT KGLTextItem: public KGLItem
{
    Q_OBJECT
    public:
        KGLTextItem(const QString& text, const QFont &font=QFont(),KGLEngine* parent=0);
        void setText(const QString& text, const QFont &font=QFont()){
          m_text=text;
          initTexture();
        }
        const QString& text() const {return m_text;}
        
    protected:
        bool initTexture();
    private:
        QString m_text;
        QFont m_font;


};

//@}
#endif //KGLTEXTITEM_H

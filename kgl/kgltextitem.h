/*
 * This file is part of the KGLEngine2D project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2008 Guillaume Martres <smarter@ubuntu.com>
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

#ifndef KGLTEXTITEM_H
#define KGLTEXTITEM_H
#include <QFont>
#include <GL/glew.h>

#include "kglitem.h"

class QString;
class QColor;
class QFont;

/**
* @class KGLTextItem kgltextitem.h <KGLTextItem>
* This class provides an item that is used to display text.
*/
class KGLTextItem: public KGLItem
{
    Q_OBJECT
public:
    /**
    * Constructs a KGLTextItem with the text @p text.
    */
    KGLTextItem(const QString& text = QString(), KGLWidget* parent=0);

    /**
    * @brief The text displayed by the item
    *
    * If the item has no text, the text() function will return an empty string.
    * @see setText
    */
    QString text() const {
        return m_text;
    }

    /**
    * Change the text displayed by the item to @p text.
    * @see text
    */
    void setText(const QString &text) {
        m_text = text;
    }

    /**
    * @brief the font to be used to display the text
    *
    * The default font is Times
    * @see setFont
    */
    inline QFont& font() {
        return m_font;
    }

    /**
    * Change the font displayed by the item to @p font.
    * @see font
    */
    inline void setFont(const QFont &font) {
        m_font = font;
    }

    /**
    * Draw the item, automatically called by the engine
    */
    virtual void draw();

private:
    QString m_text;
    QFont m_font;
};

#endif //KGLTEXTITEM_H

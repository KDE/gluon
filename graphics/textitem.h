/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef TEXTITEM_H
#define TEXTITEM_H
#include "item.h"
#include <QFont>
namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT TextItem : public Item
    {
        public:
            explicit TextItem(const QString& txt, const QFont& fnt = QFont(), QObject *parent = 0);
            void setText(const QString& txt);
            void setFont(const QFont& fnt);
            const QString& text();
            const QFont& font();

        protected:
            bool initTexture();
        private:
            QFont mFont;
            QString mText;



    };
}
#endif // TEXTITEM_H

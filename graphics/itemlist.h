/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
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

#ifndef GLUON_GRAPHICS_ITEM_LIST_H
#define GLUON_GRAPHICS_ITEM_LIST_H

#include <QtCore/QList>

#include "gluon_graphics_export.h"
#include "item.h"

/**
 * \defgroup
 */
//@{
namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT ItemList: public QList<Item*>
    {
        public:
            ItemList();
            ~ItemList();
    };
} //namesapce
//@}
#endif // ITEM_LIST_H

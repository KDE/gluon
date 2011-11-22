/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef STATNODE_H
#define STATNODE_H

#include "../lib/btlib_export.h"

struct BT_LIB_EXPORT StatNode
{
    StatNode()
    {
        fail = 1;
        succes = 1;
        p = 0.5;
        visits = 0;
        wp = 0.5;
        visited = false;
    }
    float p;
    float wp;
    int succes;
    int fail;
    int visits;
    float old_p;
    bool visited;
};

#endif // STATNODE_H

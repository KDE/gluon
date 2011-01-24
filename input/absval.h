/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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
#ifndef ABSVAL_H
#define ABSVAL_H

#include "gluon_input_export.h"

namespace GluonInput
{
    class GLUON_INPUT_EXPORT AbsVal
    {
        public:
            explicit AbsVal( int v = 0, int m = 0, int M = 0, int f = 0, int F = 0 )
                : value( v )
                , min( m )
                , max( M )
                , flat( f )
                , fuzz( F )
            {
            }

            int value;
            int min;
            int max;
            int flat;
            int fuzz;
    };
}

#endif

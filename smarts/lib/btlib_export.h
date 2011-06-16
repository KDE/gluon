/*  This file is part of the Gluon library.
    Copyright 2009 Morten Justesen <morten.justesen@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/


#ifndef BT_LIB_EXPORT_H
#define BT_LIB_EXPORT_H

#include <QtCore/qglobal.h>

#ifndef BT_LIB_EXPORT
    #if defined(MAKE_BT_LIB)
    #  define BT_LIB_EXPORT Q_DECL_EXPORT
    #else
    #  define BT_LIB_EXPORT Q_DECL_IMPORT
    #endif
#endif

# ifndef BT_LIB_EXPORT_DEPRECATED
#  define BT_LIB_EXPORT_DEPRECATED Q_DECL_DEPRECATED BT_LIB_EXPORT
# endif

#endif

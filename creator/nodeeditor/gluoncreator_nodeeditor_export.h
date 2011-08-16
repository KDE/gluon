/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONCREATOR_NODEEDITOR_EXPORT_H
#define GLUONCREATOR_NODEEDITOR_EXPORT_H

// needed for KDE_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>

#ifndef ROCSLIB_EXPORT
# if defined(MAKE_GLUON_NODEEDITOR_LIB)
// We are building this library
#  define ROCSLIB_EXPORT KDE_EXPORT
#  define GLUONCREATOR_NODEEDITOR_EXPORT Q_DECL_EXPORT
# else
// We are using this library
#  define ROCSLIB_EXPORT KDE_IMPORT
#  define GLUONCREATOR_NODEEDITOR_EXPORT Q_DECL_IMPORT
# endif
#endif

# ifndef ROCSLIB_EXPORT_DEPRECATED
#  define ROCSLIB_EXPORT_DEPRECATED KDE_DEPRECATED ROCSLIB_EXPORT
# endif

#endif


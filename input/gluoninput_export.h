/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2007 David Faure <faure@kde.org>
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

#ifndef GLUONINPUT_EXPORT_H
#define GLUONINPUT_EXPORT_H

#include <QtCore/qglobal.h>

#ifndef GLUONINPUT_EXPORT
#if defined(MAKE_GLUONINPUT_LIB)
#define GLUONINPUT_EXPORT Q_DECL_EXPORT
#else
#define GLUONINPUT_EXPORT Q_DECL_IMPORT
#endif
#endif

#ifndef GLUONINPUT_EXPORT_DEPRECATED
#define GLUONINPUT_EXPORT_DEPRECATED Q_DECL_DEPRECATED GLUONINPUT_EXPORT
#endif

#endif //GLUONINPUT_EXPORT_H

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
#ifndef GLUON_AUDIO_EXPORT_H
#define GLUON_AUDIO_EXPORT_H

#include <QtCore/QtGlobal>

#ifndef GLUON_AUDIO_EXPORT
#if defined(MAKE_GLUONAUDIO_LIB)
#define GLUON_AUDIO_EXPORT Q_DECL_EXPORT
#else
#define GLUON_AUDIO_EXPORT Q_DECL_IMPORT
#endif
#endif

#ifndef GLUON_AUDIO_EXPORT_DEPRECATED
#define GLUON_AUDIO_EXPORT_DEPRECATED Q_DECL_DEPRECATED GLUON_AUDIO_EXPORT
#endif

#endif // GLUON_EXPORT_H

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
#ifndef GLUON_CREATOR_MACROS
#define GLUON_CREATOR_MACROS

#include <kdemacros.h>
#include <KDE/KPluginFactory>
#include <KDE/KPluginLoader>

#ifndef GLUONCREATOR_EXPORT
#if defined(MAKE_GLUONCREATOR_LIB)
#  define GLUONCREATOR_EXPORT Q_DECL_EXPORT
#else
#  define GLUONCREATOR_EXPORT Q_DECL_IMPORT
#endif
#endif

#ifndef GLUONCREATOR_EXPORT_DEPRECATED
#  define GLUONCREATOR_EXPORT_DEPRECATED Q_DECL_DEPRECATED GLUONCREATOR_EXPORT
#endif

#ifndef GLUON_CREATOR_VISIBILITY
#   ifdef _MSC_VER
#       define GLUON_CREATOR_VISIBILITY
#   else
#       define GLUON_CREATOR_VISIBILITY __attribute__((visibility ("default")))
#   endif
#endif

#ifndef GLUON_CREATOR_PLUGIN_EXPORT
#   define GLUON_CREATOR_PLUGIN_EXPORT( c ) \
    K_PLUGIN_FACTORY( GluonCreatorPluginFactory, registerPlugin< c >(); ) \
    K_EXPORT_PLUGIN( GluonCreatorPluginFactory("c") )
#endif

#endif // GLUON_CREATOR_MACROS

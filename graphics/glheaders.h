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

#ifndef GLHEADERS_H
#define GLHEADERS_H

#include <QtCore/QtGlobal>
#ifdef Q_OS_WIN32
#include <windows.h>
#include <GL/glee.h>
#else
#ifdef GLUON_GRAPHICS_GLES
typedef char GLchar;
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#endif

#include <QtCore/QDebug>

#define GL_CHECK(X) X;\
    {\
        int error = glGetError(); \
        if(error != 0) qDebug() << "GL Error" << error;\
    }

#endif //GL_HEADERS_H

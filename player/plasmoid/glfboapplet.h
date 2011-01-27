/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright 2007 Zack Rusin <zack@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef GLUONPLAYER_GLFBOAPPLET_H
#define GLUONPLAYER_GLFBOAPPLET_H

#include "player/gluon_player_export.h"

#include <plasma/applet.h>

#ifdef Q_OS_WIN32
#include <windows.h>
#include <GL/glee.h>
#endif

#include <QtOpenGL/QGLWidget>

namespace GluonPlayer
{
    class GLFBOApplet : public Plasma::Applet
    {
            Q_OBJECT

        public:
            /**
            * @arg parent the QGraphicsItem this applet is parented to
            * @arg serviceId the name of the .desktop file containing the
            *      information about the widget
            * @arg appletId a unique id used to differentiate between multiple
            *      instances of the same Applet type
            */
            GLFBOApplet( QGraphicsItem* parent,
                         const QString& serviceId,
                         int appletId );

            /**
            * This constructor is to be used with the plugin loading systems
            * found in KPluginInfo and KService. The argument list is expected
            * to have two elements: the KService service ID for the desktop entry
            * and an applet ID which must be a base 10 number.
            *
            * @arg parent a QObject parent; you probably want to pass in 0
            * @arg args a list of strings containing two entries: the service id
            *      and the applet id
            */
            GLFBOApplet( QObject* parent, const QVariantList& args );

            ~GLFBOApplet();

            GLuint bindTexture( const QImage& image, GLenum target = GL_TEXTURE_2D );
            void deleteTexture( GLuint texture_id );

            /**
            * Reimplement this method to render using OpenGL. QPainter passed
            * to this method will always use OpenGL engine and rendering
            * using OpenGL api directly is supported.
            */
            virtual void paintGLInterface( QPainter* painter,
                                           const QStyleOptionGraphicsItem* option );
            void makeCurrent();

        private:
            virtual void paintInterface( QPainter* painter,
                                         const QStyleOptionGraphicsItem* option,
                                         const QRect& contentsRect );
        private:
            class GLFBOAppletPrivate;
            GLFBOAppletPrivate* const d;
    };
}

#endif // GLUONPLAYER_GLFBOAPPLET_H

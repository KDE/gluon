/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONGRAPHICS_RENDERWIDGET_H
#define GLUONGRAPHICS_RENDERWIDGET_H

#include "gluon_graphics_export.h"

#include <QtGui/QWidget>

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT RenderWidget : public QWidget
    {
            Q_OBJECT
        public:
            explicit RenderWidget( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            virtual ~RenderWidget();

            virtual void paintEvent( QPaintEvent* );
            virtual void resizeEvent(QResizeEvent* );

        public Q_SLOTS:
            virtual void update();

        private:
            class Private;
            Private* const d;
    };
}


#endif // GLUON_GRAPHICS_RENDERWIDGET_H

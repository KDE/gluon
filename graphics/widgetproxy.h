/*
 * Copyright 2008  Rivo Laks <rivolaks@hot.ee>
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
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GLUON_GRAPHICS_WIDGETPROXY_H
#define GLUON_GRAPHICS_WIDGETPROXY_H

#include "gluon_graphics_export.h"

#include <QtGui/QGraphicsView>

class QGraphicsProxyWidget;

namespace GluonGraphics
{
    class GLWidget;

    /**
     * @brief Embeds QWidgets in GLWidget
     *
     * WidgetProxy class allows easy embedding of QWidget subclasses inside a
     *  GLWidget. It tries to be as transparent as possible, continuing to use the
     *  GLWidget for rendering and doing smart event forwarding.
     * Mouse events are sent to the widget that is under the cursor. Keyboard
     *  events are sent to the widget that has focus. When user clicks outside any
     *  embedded QWidgets then focus is given to the GLWidget.
     **/
    class  WidgetProxy : public QGraphicsView
    {
        public:
            explicit WidgetProxy(GLWidget* w, QWidget* parent = 0);

            QGraphicsProxyWidget* addWidget(QWidget* w);
            QWidget* createWindow(const QString& title);

        protected:
            virtual void resizeEvent(QResizeEvent* event);
            virtual bool event(QEvent* event);
            virtual bool viewportEvent(QEvent* event);

            bool handleMouseEvent(QEvent* event, const QPoint& pos);
            bool forwardEvent(QEvent* event);

        private:
            class Scene;

            GLWidget* mGLWidget;
            bool mEventIsBeingForwarded;
    };
}


#endif // GLUON_GRAPHICS_WIDGETPROXY_H

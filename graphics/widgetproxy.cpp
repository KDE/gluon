/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2008  Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <>
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

#include "widgetproxy.h"

#include "glwidget.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QDialog>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QtDebug>
#include <QApplication>


namespace GluonGraphics
{
    class WidgetProxy::Scene : public QGraphicsScene
    {
        public:
            Scene(GLWidget* w) : QGraphicsScene()
            {
                mGLWidget = w;
                setSceneRect(QRect(QPoint(0, 0), mGLWidget->size()));
            }

            void drawBackground(QPainter* painter, const QRectF& rect)
            {
                if (!mGLWidget->glInitialized())
                {
                    //qDebug() << "GL isn't initialized";
                    return;
                }
                // Push all attributes to protect QPainter against any state changes
                //  made by GLWidget::paintGL()
                glPushAttrib(GL_ALL_ATTRIB_BITS);
                // Set blending attributes to default values
                glDisable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                mGLWidget->paintGL();

                // Pop the state
                glPopAttrib();
                // paintGL() might change the matrices so we load the same ones as
                //  the OpenGL paintengine does
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                // This is same as  gluOrtho2D(0, width(), height(), 0);
                glOrtho(0, width(), height(), 0, -1.0, 1.0);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
            }

        protected:
            GLWidget* mGLWidget;
    };

    WidgetProxy::WidgetProxy(GLWidget* w, QWidget* parent) : QGraphicsView(parent)
    {
        mEventIsBeingForwarded = false;
        mGLWidget = w;
        if (!mGLWidget->glInitialized())
        {
            qDebug() << "Initing glWidget";
            mGLWidget->init();
            if (!mGLWidget->glInitialized())
            {
                qCritical() << "GLWidget failed to init!";
            }
        }

        if (w->isVisible())
        {
            show();
        }
        setViewport(mGLWidget);
        setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        // Default to no frame, i.e. same as GLWidget
        setFrameStyle(QFrame::NoFrame);

        // Create scene
        setScene(new Scene(w));

        // Copy some properties from GL widget
        setMinimumSize(w->minimumSize());
        setMaximumSize(w->maximumSize());
        setSizePolicy(w->sizePolicy());
        setMouseTracking(w->hasMouseTracking());
    }

    void WidgetProxy::resizeEvent(QResizeEvent* event)
    {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        if (mGLWidget->glInitialized())
        {
            mGLWidget->resizeGL(event->size().width(), event->size().height());
        }

        QGraphicsView::resizeEvent(event);
    }

    bool WidgetProxy::event(QEvent* event)
    {
        if (mEventIsBeingForwarded)
        {
            return false;
        }

        //qDebug() << "WidgetProxy::event() event" << event->type();
        // We treat graphicsview stuff as being "above" the GL widget, so the
        //  events are usually first sent to the QGV and if it ignores them, then
        //  they're passed on to the GL widget.
        // TODO: maybe make it configurable: have an option to first send event to
        //  GL widget and then (if ignored) to QGV
        QGraphicsView::event(event);
        if (event->isAccepted())
        {
            return true;
        }
        //qDebug() << "WidgetProxy::event(): fwding to GL";
        return forwardEvent(event);
    }

    bool WidgetProxy::forwardEvent(QEvent* event)
    {
        mEventIsBeingForwarded = true;
        bool ret = qApp->notify(mGLWidget, event);
        mEventIsBeingForwarded = false;

        return ret;
    }

    bool WidgetProxy::viewportEvent(QEvent* event)
    {
        if (mEventIsBeingForwarded)
        {
            return false;
        }

        //qDebug() << "WidgetProxy::viewportEvent() event" << event->type();
        // For mouse and wheel events, if there is no QGV item under the cursor,
        //  then the event gets forwarded to GL widget.
        if (event->type() == QEvent::Wheel)
        {
            QWheelEvent* e = static_cast<QWheelEvent*>(event);
            if (handleMouseEvent(e, e->pos()))
            {
                return true;
            }
        }
        else if (event->type() == QEvent::MouseButtonDblClick ||
                 event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* e = static_cast<QMouseEvent*>(event);
            if (handleMouseEvent(e, e->pos()))
            {
                return true;
            }
        }
        else if (event->type() == QEvent::MouseMove && !scene()->mouseGrabberItem())
        {
            // MouseMove events get sent to both GL widget as well as QGV (unless
            //  the mouse has been grabbed by a QGraphicsItem, e.g. when dragging
            //  a widget). The reason is that if we'd send them only to the GL
            //  widget then QGV's cursor changing mechanism won't work when mouse
            //  leaves a widget with custom cursor.
            forwardEvent(event);
            event->ignore();
        }
        else if (event->type() == QEvent::ShowToParent)
        {
            // We intercept show/hide events of viewport widget to show/hide
            //  ourselves along with the viewport widget.
            show();
        }
        else if (event->type() == QEvent::HideToParent)
        {
            // See the above comment
            hide();
        }
        // Pass it on to QGV
        return QGraphicsView::viewportEvent(event);
    }

    bool WidgetProxy::handleMouseEvent(QEvent* event, const QPoint& pos)
    {
        if (scene()->mouseGrabberItem())
        {
            return false;
        }
        // We use items() to test against bounding rect of the items. itemAt()
        //  tests against item's shape which doesn't include window's heading
        if (scene()->items(QRectF(pos, QSizeF(1, 1)), Qt::IntersectsItemBoundingRect).isEmpty())
        {
            // Remove focus from QGV widgets
            scene()->setFocusItem(0);
            //qDebug() << "WidgetProxy::handleMouseEvent(): forwarding event";
            // Forward the event to GL widget.
            return forwardEvent(event);
        }
        return false;
    }

    QGraphicsProxyWidget* WidgetProxy::addWidget(QWidget* w)
    {
        QGraphicsProxyWidget* item = scene()->addWidget(w);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

        return item;
    }

    QWidget* WidgetProxy::createWindow(const QString& title)
    {
        QDialog* d = new QDialog(0, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

        d->setWindowOpacity(0.8);
        d->setWindowTitle(title);
        d->setLayout(new QVBoxLayout);

        return d;
    }

}

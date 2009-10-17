/*
 * This file is part of the Gluon library.
 * Copyright 2009 Gluon team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KGLVIEW_H
#define KGLVIEW_H

#include <KDebug>
#include <QGLWidget>
#include <QTimer>
#include <QDialog>

#include "kgl_export.h"
#include "kglengine.h"
//#include "kglscreenconfig.h"
#include "kglpixmapitem.h"

class QMouseEvent;

/**
 * \defgroup KGL KGL
 */
//@{

class KGL_EXPORT KGLView : public QGLWidget
{
    Q_OBJECT
public:
    explicit KGLView( const QSize &size, float frameRate ,QWidget* parent = 0);
    explicit KGLView(KGLEngine * engine,QWidget * parent = 0);
    explicit KGLView(QWidget * parent=0);
    ~KGLView();

    void setEngine(KGLEngine * engine)
    {
        m_engine = engine;
        m_engine->setParent(this);
    }
    KGLEngine * engine()
    {
        return m_engine;
    }

    inline void setFrameRate(int f)
    {
        m_frameRate=f;
        stop();
        start();
    }


    inline void setOrthoView(const QRectF &rect) {
        m_orthoView = rect;
        resizeGL(width(), height());
    }
    inline void setOrthoView(const float& left,const float& right,const float& bottom,const float& top)
    {
        m_orthoView.setLeft(left);
        m_orthoView.setRight(right);
        m_orthoView.setBottom(bottom);
        m_orthoView.setTop(top);
        resizeGL(width(),height());
    }
    inline QPointF mapToGL(const QPointF &p) {
        double x, y, z;
        glGetIntegerv(GL_VIEWPORT, m_viewport);
        gluUnProject(p.x(), p.y(), 0, m_modelMatrix, m_projMatrix, m_viewport, &x, &y, &z);
        return QPointF(x, -y);
    }
    inline QPointF mapFromGL(const QPointF &p) {
        const int CURSOR_HACK = 0x18; // cursor inversion
        int side = qMin(width(), height());
        return QPointF(
                side * p.x() / m_orthoView.width() + width() / 2,
                side * p.y() / m_orthoView.height() + height() / 2 + CURSOR_HACK
                );
    }

    QRectF orthoView(){
    return m_orthoView;
    }

    //=== Flags ====
    inline void setMode(GLenum mode)
    {
        m_mode=mode;
        initializeGL();
    }
    inline void setAxisShow(bool b)
    {
        m_axisShow=b;
    }
    inline bool isAxisShow() const
    {
        return m_axisShow;
    }
    inline void setInfoShow(bool b)
    {
        m_infoShow = b;
    }
    inline bool isInfoShow() const
    {
        return m_axisShow;
    }
    bool isExtensionSupported(const QString &name) const;

    bool isShaderSupported() const
    {
        return m_isShaderSupported;
    }
    float fps() const
    {
        return m_fps;
    }
public slots:
    void start()
    {
        m_timer->start(m_frameRate);
        m_fpsTimer->start(1000);
    }
    void stop()
    {
        m_timer->stop();
        m_fpsTimer->stop();
    }
    void toogleActive()
    {
        if ( m_timer->isActive())
            stop();
        else start();
    }

    virtual void nextFrame();
    inline void calculFps()
    {
        if ( m_fps!=m_countFrame)
            emit fpsChanged(m_countFrame);
        m_fps = m_countFrame;
        m_countFrame = 0;
    }
    void goFullScreen();
    void leaveFullScreen();
    void toggleFullScreen();
    void setFullscreen(bool fs);

signals:
    void fpsChanged(int fps);

protected:
    void drawRepere(float scalex, float scaley);
    void drawInfo();
    void drawGLItems();
    void saveResolution();
    bool initGlew();
    void init();
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);

private:
    KGLEngine * m_engine;
    //KGLScreenConfig * m_screenConfig;
    KGLPixmapItem * m_logo ;
    QRectF m_orthoView;
    float m_countFrame;
    float m_fps;
    float m_frameRate;
    float m_ratio;
    float m_sleep;
    QTimer* m_timer;
    QTimer* m_fpsTimer;

    bool m_axisShow;
    bool m_infoShow;
    bool m_fullscreen;
    bool m_isShaderSupported;
    GLenum m_mode;
    int m_originalResolution;

    double m_screenRatio;
    GLdouble m_modelMatrix[16];
    GLdouble m_projMatrix[16];
    int m_viewport[4];

};

//@}
#endif // KGLVIEW_H

/*
 * This file is part of the Gluon library.
 * Copyright 2009 Gluon team
 * Copyright 2009 Casper van Donderen <casper.vandonderen@gmail.com>
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

#include <GL/glew.h>

#include "kglview.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtCore/QDebug>

#include "kgldisplay.h"
#include "kglscreen.h"
#include "widgets/kglresolutiondialog.h"


KGLView:: KGLView( const QSize &size, float frameRate ,QWidget* parent)
    : QGLWidget(parent)
{
    init();
    resize(size);
    setFrameRate(frameRate);
}

KGLView::KGLView(QWidget * parent)
    : QGLWidget(parent)
{
    init();
}

KGLView::KGLView(KGLEngine * engine,QWidget * parent )
{
    init();
    setEngine(engine);
}

bool KGLView::initGlew()
{
    GLenum code;
    qDebug()<<"Glew initialization....";
    /* initialization of GLEW */
    code = glewInit();
    if(code != GLEW_OK)
    {
        qDebug()<< "cannot init GLEW :"<<glewGetErrorString(code);
        return false;
    }
    qDebug()<<"Glew success...";

    if ( (isExtensionSupported("GL_ARB_vertex_shader") || isExtensionSupported("GL_vertex_shader"))
        && (isExtensionSupported("GL_ARB_fragment_shader") || isExtensionSupported("GL_fragment_shader")))
        {
        qDebug()<<"Shaders supported...";
        m_isShaderSupported = true;
    }
    else
    {
        qDebug()<<"Shaders unsupported...";
        m_isShaderSupported = false;
    }
    return true;
}

bool KGLView::isExtensionSupported(const QString &name) const
{
    return glewIsSupported(name.toUtf8());
}

KGLView::~KGLView()
{
    stop();

    delete m_timer;
    delete m_fpsTimer;

}
void KGLView::init()
{
    m_engine = NULL;
    m_frameRate = 20;
    m_timer = new QTimer(this);
    m_fpsTimer = new QTimer(this);
    m_countFrame = 0;
    m_fps = 1000/m_frameRate;
    m_isShaderSupported = false;
    m_sleep=true;
    m_axisShow = false;
    m_infoShow = false;
    m_fullscreen = false;
    m_ratio = width() / height();
    setOrthoView(-10,10,-10,10);
    m_mode = GL_FILL;
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    setAutoBufferSwap(true);
    glInit();
    initGlew();

    //connect(this,SIGNAL(destroyed()),m_screenConfig,SLOT(restore()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    connect(m_fpsTimer, SIGNAL(timeout()), this, SLOT(calculFps()));
}
void KGLView::goFullScreen()
{
    /*int id = m_screenConfig->askResolution();
    if ( id<0) return;
    m_screenConfig->setResolution(id);*/
    KGLResolutionDialog dialog(this);
    KGLDisplay::instance()->currentScreen()->setFullscreen(true, false);
    if(dialog.exec())
    {
      if ( parentWidget()!=NULL)
      {
          parentWidget()->showFullScreen();
      }
      else
      {
          showFullScreen();
      }
      m_fullscreen = true;
    }
    else
    {
      KGLDisplay::instance()->currentScreen()->setFullscreen(false, false);
    }
}
void KGLView::leaveFullScreen()
{
    KGLDisplay::instance()->currentScreen()->restore();
    if ( parentWidget() != NULL)
    {
        parentWidget()->showNormal();
    }
    else
    {
        showNormal();
    }
    m_fullscreen = false;
}

void KGLView::toggleFullScreen()
{
    if ( m_fullscreen)
        leaveFullScreen();
    else goFullScreen();
}

void KGLView::setFullscreen(bool fs)
{
  if(fs)
  {
    goFullScreen();
  }
  else
  {
    leaveFullScreen();
  }
}

void KGLView::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA ,GL_ONE);
    glPolygonMode(GL_FRONT_AND_BACK, m_mode);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glDisable(GL_DEPTH_TEST);
    setAutoBufferSwap(true);
    QRect screenDim = QApplication::desktop()->screenGeometry();
    m_screenRatio = (double)screenDim.width()/screenDim.height();

    // Changing orthoView size according to detected screen ratio.
    m_orthoView.setCoords(-10*m_screenRatio, 10, 10*m_screenRatio, -10);

    glLoadIdentity();
    glOrtho(m_orthoView.left(), m_orthoView.right(), m_orthoView.bottom(), m_orthoView.top(), 0, 15);
    glMatrixMode(GL_MODELVIEW);

    // Storing matrices for mapping from view to scene
    glGetDoublev(GL_MODELVIEW_MATRIX, m_modelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, m_projMatrix);
}

void KGLView::resizeGL(int w, int h)
{
    qDebug()<<w<<"--"<<width();
    qDebug()<<h<<"--"<<height();

    int newWidth = w, newHeight = h;

    if (h >= w)
        newHeight = w/m_screenRatio;
    else
        newWidth = h*m_screenRatio;

    int side = qMin(newWidth, newHeight);

    glMatrixMode(GL_PROJECTION);
    glViewport((w - newWidth) / 2, (h - newHeight) / 2, newWidth, newHeight);
    glMatrixMode(GL_MODELVIEW);
}

void  KGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    if ( engine() != NULL)drawGLItems();


    glColor3ub(255, 255, 255);
    if ( m_axisShow) drawRepere(1,1);
    if ( m_infoShow) drawInfo();



    QGLWidget::paintGL();
}

void KGLView::nextFrame()
{
    if ( engine() != NULL)
        engine()->mainLoop(fps());
    updateGL();
    m_countFrame++;
}
//===============DRAW FUNCTION ============================

void KGLView::drawRepere(float scalex, float scaley) // a modifier
{
    glPushMatrix();

    glScalef(scalex, scaley,0);
    renderText(1,0,0,"X");
    renderText(0,1,0,"Y");
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex2d(0, 0);
    glColor3ub(255, 0, 0);
    glVertex2d(1, 0);
    glColor3ub(0, 255, 0);
    glVertex2d(0, 0);
    glColor3ub(0, 255, 0);
    glVertex2d(0, 1);
    glEnd();
    glPopMatrix();
}

void  KGLView::drawInfo()
{
    glColor3ub(255, 255, 255);
    renderText(50, 55, "fps : " + QString::number(m_fps));
    renderText(50, 70, "fff : " + QString::number(100 / m_fps));
    renderText(50, 85, (m_isShaderSupported) ? "Shaders supported" : "Shader unsupported" );
}

void KGLView::drawGLItems()
{
    IndexGroupMap::const_iterator i = engine()->items().constBegin();
    while (i != engine()->items().constEnd())
    {
        KGLItem * it;
        foreach ( it, i.value())
        {
            it->paintGL();
        }
        ++i;
    }
}
void KGLView::mousePressEvent(QMouseEvent * event)
{
if ( m_engine!=NULL)
    m_engine->mousePressed(mapToGL(event->posF()),event->button());
}
 void KGLView::mouseMoveEvent(QMouseEvent * event)
{
if ( m_engine!=NULL)
    m_engine->mouseMoved(mapToGL(event->posF()),event->button());
}
void KGLView::mouseReleaseEvent(QMouseEvent * event)
{
if ( m_engine!=NULL)
    m_engine->mouseReleased(mapToGL(event->posF()),event->button());
}

#include "kglview.moc"

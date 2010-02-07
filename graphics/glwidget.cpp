/*
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "glwidget.h"

#include "camera.h"
#include "fpscounter.h"
#include "textrenderer.h"
#include "glpainter.h"

#include <QtOpenGL/QGLContext>
#include <QtOpenGL/QGLFormat>

#include <core/debughelper.h>

using namespace Eigen;
using namespace GluonGraphics;

GLWidget::GLWidget(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f) :
        QGLWidget(parent, shareWidget, f)
{
    init();
}

GLWidget::GLWidget(QGLContext* context, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f) :
        QGLWidget(context, parent, shareWidget, f)
{
    init();
}

GLWidget::GLWidget(const QGLFormat& format, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f) :
        QGLWidget(format, parent, shareWidget, f)
{
    init();
}

GLWidget::~GLWidget()
{
    delete mCamera;
    delete mFpsCounter;
    delete mTextRenderer;
}

void GLWidget::init()
{
    mCamera = 0;
    mFpsCounter = 0;
    mTextRenderer = 0;
    mAutomaticClear = true;
    mClearColor = Vector4f(0, 0, 0, 0);
    mGLInitialized = false;
    mShowFps = false;
    mWireframeMode = false;
    mShortcutsEnabled = true;
    //m_engine=0;

    QAction* a;
    a = new QAction(this);
    a->setShortcut(Qt::META + Qt::Key_F);
    connect(a, SIGNAL(triggered()), this, SLOT(toggleShowFps()));
    addAction(a);
    mShortcuts.append(a);
    a = new QAction(this);
    a->setShortcut(Qt::META + Qt::Key_W);
    connect(a, SIGNAL(triggered()), this, SLOT(toggleWireframeMode()));
    addAction(a);
    mShortcuts.append(a);
    glInit();
}

void GLWidget::setShortcutsEnabled( bool enabled)
{
    if (enabled == mShortcutsEnabled) {
        return;
    }
    mShortcutsEnabled = enabled;
    foreach (QAction* a, mShortcuts) {
        a->setEnabled(enabled);
    }
}

void GLWidget::toggleShowFps()
{
    mShowFps = !mShowFps;
    update();
}

void GLWidget::toggleWireframeMode()
{
    mWireframeMode = !mWireframeMode;
    update();
}

void GLWidget::setClearColor(const Eigen::Vector4f& c)
{
    mClearColor = c;
    if (mGLInitialized) {
        // TODO: what if this is called when context isn't current?
        glClearColor(mClearColor.x(), mClearColor.y(), mClearColor.z(), mClearColor.w());
    }
}

void GLWidget::setAutomaticClear(bool clear)
{
    mAutomaticClear = clear;
}

void GLWidget::setErrorText(const QString& text)
{
    mErrorText = text;
    update();
}

GluonGraphics::TextRenderer* GLWidget::textRenderer() const
{
    if (!mTextRenderer) {
        mTextRenderer = new GluonGraphics::TextRenderer();
    }
    return mTextRenderer;


}

void GLWidget::initializeGL()
{








    // Init KGLLib

    mGLInitialized = true;

    // Create camera and fps counter
    mCamera = new GluonGraphics::Camera;
    mFpsCounter = new GluonGraphics::FPSCounter;





    // Set some defaults
    // TODO: make sure we're in RGBA mode
    setClearColor(mClearColor);
    glShadeModel(GL_SMOOTH);
     glEnable(GL_DEPTH_TEST);


//     glPolygonMode(GL_FRONT_AND_BACK, m_mode);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    //glDisable(GL_DEPTH_TEST);



    // Enable depth testing if we have depth
//     if (context()->format().depth()) {
//         glEnable(GL_DEPTH_TEST);
//     }

    // Set up camera
    //camera()->setPosition(Vector3f(0, 0, 5));
    //camera()->setLookAt(Vector3f(0, 0, 0));
    //camera()->setUp(Vector3f(0, 1, 0));
    //camera()->setDepthRange(1, 100);
}

void GLWidget::resizeGL(int width, int height)
{
    camera()->setViewport(0, 0, width, height);
    camera()->applyViewport();

    camera()->setAspect(width/(float)height);
    //camera()->applyPerspective();
    camera()->applyOrtho();
}

void GLWidget::paintGL()
{
    DEBUG_BLOCK



  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    //drawItems();


//     glColor3ub(255, 255, 255);
//     if ( m_axisShow) drawRepere(1,1);
//     if ( m_infoShow) drawInfo();



    QGLWidget::paintGL();





    // If error text has been set then show it and return
    if (!mErrorText.isNull()) {
        DEBUG_TEXT(mErrorText);
        return;
    }

    // Advance the counter
    fpsCounter()->nextFrame();

    // Clear buffers
    if (mAutomaticClear) {
        setClearColor(mClearColor);
        if (context()->format().depth()) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        } else {
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }

    // Apply camera
    camera()->applyView();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    if (mWireframeMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    render();

    glPopAttrib();

    if (mShowFps) {
        textRenderer()->begin(this);
        textRenderer()->draw(5, 0, "FPS: " + fpsCounter()->fpsString());
        textRenderer()->end();
    }
}

void GLWidget::drawItems()
{

    IndexGroupMap::const_iterator i;
    for(i = Engine::instance()->items().constBegin(); i != Engine::instance()->items().constEnd(); ++i)
    {
        foreach (Item *it, i.value())
        {

            it->paintGL();

        }
    }
}




void GLWidget::render()
{

  //if (m_engine!=0)
    drawItems();
}

#include "glwidget.moc"

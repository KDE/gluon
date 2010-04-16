/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
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

#include "glwidget.h"

#include "camera.h"
#include "fpscounter.h"
#include "textrenderer.h"
#include "glpainter.h"

#include <QtOpenGL/QGLContext>
#include <QtOpenGL/QGLFormat>

#include <core/debughelper.h>


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
    //delete mCamera;
    delete mFpsCounter;
    delete mTextRenderer;
}

void GLWidget::init()
{
    mCamera = 0;
    mFpsCounter = 0;
    mTextRenderer = 0;
    mAutomaticClear = true;
    mClearColor = QVector4D(0, 0, 0, 0);
    mGLInitialized = false;
    mShowFps = false;
    mWireframeMode = false;
    m_displayAxis = false;
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

void GLWidget::setShortcutsEnabled(bool enabled)
{
    if (enabled == mShortcutsEnabled)
    {
        return;
    }
    mShortcutsEnabled = enabled;
    foreach(QAction* a, mShortcuts)
    {
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

void GLWidget::setClearColor(const QVector4D& c)
{
    mClearColor = c;
    if (mGLInitialized)
    {
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
    if (!mTextRenderer)
    {
        mTextRenderer = new GluonGraphics::TextRenderer();
    }
    return mTextRenderer;


}

void GLWidget::initializeGL()
{
    mGLInitialized = true;

    mCamera = Engine::instance()->activeCamera();
    connect(Engine::instance(), SIGNAL(activeCameraChanged(GluonGraphics::Camera*)), SLOT(setCamera(GluonGraphics::Camera*)));

    mFpsCounter = new GluonGraphics::FPSCounter;
    // Set some defaults
    // TODO: make sure we're in RGBA mode
    setClearColor(mClearColor);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLWidget::resizeGL(int width, int height)
{
    m_viewportWidth = width;
    m_viewportHeight = height;

    if (mCamera)
    {
        camera()->setViewport(0, 0, width, height);
        camera()->applyViewport();
        camera()->applyOrtho();
    }
}

void GLWidget::paintGL()
{
    glScissor(0, 0, m_viewportWidth, m_viewportHeight);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // If error text has been set then show it and return
    if (!mErrorText.isNull())
    {
        DEBUG_BLOCK
        DEBUG_TEXT(mErrorText);
        return;
    }

    // Advance the counter
    fpsCounter()->nextFrame();

    // Clear buffers
    if (mAutomaticClear)
    {
        setClearColor(mClearColor);
        if (context()->format().depth())
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }

    // Apply camera
    if (mCamera) 
    {
        mCamera->applyView();
    }

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    if (mWireframeMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    render();

    glPopAttrib();

    if (mShowFps)
    {
        textRenderer()->begin(this);
        textRenderer()->draw(5, 0, "FPS: " + fpsCounter()->fpsString());
        textRenderer()->end();
    }
}

void GLWidget::render()
{
    if (m_displayAxis)
    {
        glBegin(GL_LINES);
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 5, 0);
        glEnd() ;

        glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(5, 0, 0);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 5);
        glEnd();
    }

    ItemList items = Engine::instance()->items();
    foreach(Item *it, items)
    {
        it->paintGL();
    }
}

void GLWidget::setCamera(Camera* camera)
{
    mCamera = camera;
    resizeGL(m_viewportWidth, m_viewportHeight);
}


#include "glwidget.moc"

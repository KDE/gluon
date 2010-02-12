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

#ifndef GLUON_GRAPHICS_GLWIDGET_H
#define GLUON_GRAPHICS_GLWIDGET_H

#include <glew.h>

#include <QtOpenGL/QGLWidget>
#include <QtCore/QList>

#include <QtGui/QAction>
#include <QtGui/QFontMetrics>
#include <QtCore/QtDebug>

#include "gluon_graphics_export.h"
#include "engine.h"

#include <QVector4D>
namespace GluonGraphics
{
class Camera;
class FPSCounter;
class TextRenderer;

/**
 * @brief Easy to use GL widget, based on QGLWidget
 *
 * GLWidget is a QGLWidget subclass which is integrated with the rest of the
 *  KGLLib and implements some of the common functionality used by many GL
 *  applications.
 *
 * If you are already using QGLWidget then switching to GLWidget is very easy.
 * All you need to do is changing class name to GLWidget and doing your OpenGL
 * rendering in @ref render() method instead of @ref paintGL().
 **/
class GLUON_GRAPHICS_EXPORT GLWidget : public QGLWidget
{
Q_OBJECT
public:
    explicit GLWidget(QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);
    explicit GLWidget(QGLContext* context, QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);
    explicit GLWidget(const QGLFormat& format, QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);

    virtual ~GLWidget();

    /**
     * @return pointer to the @ref Camera object. This is available after
     *  @ref initializeGL() has been called.
     **/
    GluonGraphics::Camera* camera() const  { return mCamera; }
    /**
     * @return pointer to the @ref FPSCounter object. This is available after
     *  @ref initializeGL() has been called.
     **/
    GluonGraphics::FPSCounter* fpsCounter() const  { return mFpsCounter; }

    /**
     * @return TextRenderer object
     **/
    GluonGraphics::TextRenderer* textRenderer() const;

    /**
     * @return whether @ref initializeGL() has been called
     **/
    bool glInitialized() const  { return mGLInitialized; }

    /**
     * Initializes OpenGL.
     * Base implementation:
     * @li calls @ref KGLLib::init() to initialize KGLLib
     * @li creates @ref camera and @ref fpsCounter objects
     * @li sets OpenGL clear color to @ref clearColor
     * @li initializes camera to look from (0, 0, 5)  at (0, 0, 0) with depth range [1, 100]
     * @li enables depth testing (if depth buffer is used)
     * @li sets OpenGL shade model to GL_SMOOTH
     * @li sets primary color to white
     **/
    virtual void initializeGL();
    /**
     * Same as above but passes the specified Renderer object to @ref KGLLib::init().
     **/

    virtual void resizeGL(int width, int height);
    /**
     * Called when the widget needs to be painted. Base implementation:
     * @li updates @ref fpsCounter
     * @li clears color and possibly depth buffer is @ref automaticClear is true
     * @li applies @ref camera
     *
     * Note that applications are preferred to use @ref render() instead. If
     *  you do your OpenGL rendering in this method then some functionality
     *  provided by this class will not work (e.g. fps display).
     **/
    virtual void paintGL();
    /**
     * Called from @ref paintGL() when the widget needs to be painted. This is
     *  the method that you should reimplement to do your rendering.
     * Base implementation does nothing, so you needn't call it from your
     *  implementation.
     **/
    virtual void render();

    /**
     * Set's OpenGL's clear color to c.
     * Default is black.
     * TODO: maybe rename to setBackgroundColor?
     **/
    void setClearColor(const QVector4D& c);
    /**
     * Specifies whether OpenGL buffers should be automatically cleared in the
     *  beginning of @ref paintGL.
     **/
    void setAutomaticClear(bool clear);

    QVector4D clearColor() const  { return mClearColor; }
    bool automaticClear() const  { return mAutomaticClear; }

    /**
     * Sets error text for this widget.
     *
     * If the error text is set, then it is displayed centered in the widget
     * and @ref render() method isn't called.
     *
     * It is handy to use when something goes wrong in your application's
     * initialization phase (e.g. data files cannot be found) and you want to
     * abort but let the user know what happened.
     **/
    void setErrorText(const QString& text);
    /**
     * @return current error text
     * @see setErrorText()
     **/
    QString errorText() const  { return mErrorText; }

    /**
     * @return whether KGLLib keyboard shortcuts are enabled.
     * @see setShortcutsEnabled()
     **/
    bool shortcutsEnabled() const  { return mShortcutsEnabled; }
    /**
     * GLWidget provides some keyboard shortcuts to ease application
     * development. For example Meta+F toggles FPS (frames per second) display
     * and Meta+W toggles wireframe rendering.
     *
     * If you don't want those shortcuts to be available, you can disable them
     * using this method.
     *
     * Shortcuts are enabled by default.
     **/
    virtual void setShortcutsEnabled( bool enabled);


       void drawItems();
           void init();
private:

public Q_SLOTS:
    void toggleShowFps();
    void toggleWireframeMode();
private:
   GluonGraphics::Camera* mCamera;
   GluonGraphics::FPSCounter* mFpsCounter;
    mutable GluonGraphics::TextRenderer* mTextRenderer;
   //GluonGraphics::Engine * m_engine;


    bool mAutomaticClear;
    QVector4D mClearColor;
    bool mGLInitialized;

    bool mShowFps;
    bool mWireframeMode;
    QString mErrorText;
    // We use our own list of actions here because we want to be able to
    //  enable/disable only those actions
    QList<QAction*> mShortcuts;
    bool mShortcutsEnabled;

};

}


#endif // GLUON_GRAPHICS_GLWIDGET_H

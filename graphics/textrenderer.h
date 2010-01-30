#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

/*
 * Copyright (C) 2007-2008 Benoit Jacob
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

/*
 This file has been taken from Avogadro project - http://avogadro.sourceforge.net/
 As such, it uses different coding style than the rest of the KGLLib. This is
 meant to minimize differences between this version and the one used by
 Avogadro, so that bugfixes, etc made to one version could easily be merged
 into the other one.
 */

#include <Eigen/Core>
#include <QtGui/QFont>

#include "gluon_graphics_export.h"

namespace GluonGraphics
{

class GLWidget;

/**
 * @class TextRenderer
 * @author Benoit Jacob
 * @brief Enhanced text renderer.
 *
 * This class renders text inside a QGLWidget. It replaces and extends the functionality
 * of QGLWidget::renderText().
 *
 * Its advantages over the renderText() in Qt 4.2.3 are that it is much faster both at
 * render-time and at startup, consumes less memory, and does outlined text.
 * Its drawback is that its Unicode-safeness is
 * not perfect as superpositions of unicode characters aren't handled.
 *
 * Every QFont can be used, every character encodings supported by Qt can be used.
 *
 * To draw plain 2D text on top of the scene, do:
 * @code
 textRenderer.begin();
 textRenderer.draw( x1, y1, string1 );
 textRenderer.draw( x2, y2, string2 );
 textRenderer.draw( x3, y2, string3 );
 textRenderer.end();
 * @endcode
 *
 * To draw text as a transparent object inside the scene, do:
 * @code
 textRenderer.begin();
 textRenderer.draw( pos1, string1 );
 textRenderer.draw( pos2, string2 );
 textRenderer.draw( pos3, string3 );
 textRenderer.end();
 * @endcode
 *
 * In order to set the text color, please call glColor3f or glColor4f before
 * calling draw(). Of course you can
 * also call qglColor or Color::apply(). You can achieve semitransparent text at
 * no additional cost by choosing a semitransparent color.
 *
 * Please make sure that no relevant OpenGL state change occurs between
 * begin() and end(), except the state changes performed by the TextRenderer
 * itself. In other words, please avoid calling glSomething() between begin() and
 * end(), except if you are sure that this call won't result in a conflicting state
 * change. Of course calling glColor*() is allowed.
 *
 * If you experience rendering problems, you can try the following:
 * - disable some OpenGL state bits. For instance, TextRenderer automatically
 *   disables fog and lighting during rendering, because it doesn't work
 *   correctly with them enabled. There probably are other OpenGL state bits
 *   that have to be disabled, so if your program enables some of them, you
 *   might have to disable them before rendering text.
 * - if you experience poor font quality, meake sure that your GLWidget is using
 *   an antialiased font.
 *
 */

  class GLUON_GRAPHICS_EXPORT TextRenderer
  {
    public:
      TextRenderer();
      ~TextRenderer();

      /**
       * Call this before drawing any text. This method saves the GL state
       * and changes it to prepare for text rendering.
       */
      void begin(GLWidget *widget);

      /**
       * Call this after drawing text. This method restores the GL state
       * to what it was when begin() was called.
       */
      void end();

      /**
       * Draw text inside the 3D scene. Must be called between begin() and end().
       * The text is centered (both horizontally and vertically) around the specified position.
       * @param pos the position of the text in the scene's coordinate system
       * @param string the QString to render
       * @returns the line spacing in pixels of the text just rendered (0 for an empty string).
       */
      int draw( const Eigen::Vector3d & pos, const QString &string, const QFont& font = QFont());

      /**
       * Draw a single line of 2D text at the position (x,y) in window coordinates. Must be called
       * between begin() and end().
       * (0,0) is the top-left corner.
       * @param x the x-coordinate
       * @param y the y-coordinate
       * @param string the QString to render
       * @returns the line spacing in pixels of the text just rendered (0 for an empty string).
       */
      int draw( int x, int y, const QString &string, const QFont& font = QFont());

      /**
       * Draws 2D text within the given rectangle.
       * The text will be positioned and layed out according to @p flags which
       * is a bitwise OR of the following flags:
       * @li Qt::AlignLeft
       * @li Qt::AlignRight
       * @li Qt::AlignHCenter
       * @li Qt::AlignTop
       * @li Qt::AlignBottom
       * @li Qt::AlignVCenter
       * @li Qt::AlignCenter
       * @li Qt::TextSingleLine
       * @li Qt::TextWordWrap
       * Any newlines contained in the @p string argument are preserved.
       * Must be called between begin() and end().
       * @return total height of the rendered text (i.e. font's line spacing
       *  times the number of drawn lines)
       **/
      int draw( const QRect& rect, const QString &string, int flags, const QFont& font = QFont());

      bool isActive();

    private:

      class Private;
      Private * const d;
  };

} // namespace GluonGraphics



#endif // GLUON_GRAPHICS_TEXTRENDERER_H

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2007-2008 Benoit Jacob
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

/*
This file has been taken from Avogadro project - http://avogadro.sourceforge.net/
As such, it uses different coding style than the rest of the KGLLib. This is
meant to minimize differences between this version and the one used by
Avogadro, so that bugfixes, etc made to one version could easily be merged
into the other one.
*/

#include "textrenderer.h"
#include "glwidget.h"

#include <QtGui/QPainter>
#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtCore/QDebug>
#include <QtGlobal>
#include <cmath>
namespace
{

#define OUTLINE_WIDTH     3
    const int OUTLINE_BRUSH[2*OUTLINE_WIDTH+1][2*OUTLINE_WIDTH+1]
    = { { 10, 30,  45,  50,  45,  30,  10 },
        { 30, 65,  85,  100,  85, 65,  30 },
        { 45, 85,  200, 256, 200, 85,  45 },
        { 50, 100, 256, 256, 256, 100, 50},
        { 45, 85,  200, 256, 200, 85,  45 },
        { 30, 65,  85,  100,  85, 65,  30 },
        { 10, 30,  45,  50,  45,  30,  10 }
    };

    /*
       = { { 40,  75,  100,  75, 40 },
       { 75,  200, 256, 200, 75 },
       { 100, 256, 256, 256, 100 },
       { 75,  200, 256, 200, 75 },
       { 40,  75,  100,  75, 40 } };
       */
    /*  = { { 200, 256, 200 },
        { 256, 256, 256 },
        { 200, 256, 200 } }; */

    /** @internal
     * This is a helper class for TextRenderer.
     *
     * The CharRenderer class represents a character stored as OpenGL rendering
     * data : a texture object and a display list mapping it on a quad and then
     * translating to the right of it.
     *
     * See the charTable member of TextRenderer for an example of use of
     * this class.
     */
    class CharRenderer
    {
        protected:
            GLuint m_glyphTexture;
            GLuint m_outlineTexture;

            GLuint m_quadDisplayList;

            GLenum m_textureTarget;

            /**
             * Width and height in pixels of the rendered character
             */
            int m_realwidth, m_realheight;

        public:
            CharRenderer();
            ~CharRenderer();

            /** Builds the texture and the display list for a given character and font */
            bool initialize(QChar c, const QFont &font, GLenum textureTarget);

            /** Calls the display list, drawing the character as a textured quad */
            void draw(const float *color) const;

            /** @returns the height of the rendered character in pixels */
            inline int height() const
            {
                return m_realheight;
            }

            /** @returns the width of the rendered character in pixels */
            inline int width() const
            {
                return m_realwidth;
            }

            inline void drawOutline() const
            {
                glBindTexture(m_textureTarget, m_outlineTexture);
                glCallList(m_quadDisplayList);
            }

            inline void drawGlyph() const
            {
                glBindTexture(m_textureTarget, m_glyphTexture);
                glCallList(m_quadDisplayList);
            }
    };

    CharRenderer::CharRenderer()
    {
        m_glyphTexture = 0;
        m_outlineTexture = 0;
        m_quadDisplayList = 0;
    }

    CharRenderer::~CharRenderer()
    {
        if (m_glyphTexture) glDeleteTextures(1, &m_glyphTexture);
        if (m_outlineTexture) glDeleteTextures(1, &m_outlineTexture);
        if (m_quadDisplayList) glDeleteLists(m_quadDisplayList, 1);
    }

    static void normalizeTexSize(GLenum textureTarget,
                                 int& texwidth, int& texheight)
    {
        // if the texture target is GL_TEXTURE_2D, that means that
        // the texture_rectangle OpenGL extension is unsupported and we must
        // use only square, power-of-two textures.
        if (textureTarget == GL_TEXTURE_2D)
        {
            int x = qMax(texwidth, texheight);
            // find next power of two
            int n;
            for (n = 1; n < x; n = n << 1) {}
            // the texture must be square, and its size must be a power of two.
            texwidth = texheight = n;
        }
    }

    bool CharRenderer::initialize(QChar c, const QFont &font, GLenum textureTarget)
    {
        if (m_quadDisplayList) return true;
        m_textureTarget = textureTarget;
        // *** STEP 1 : render the character to a QImage ***

        // compute the size of the image to create
        const QFontMetrics fontMetrics(font);
        m_realwidth = fontMetrics.width(c);
        m_realheight = fontMetrics.height();
        if (m_realwidth == 0 || m_realheight == 0) return false;
        int texwidth  =  m_realwidth + 2 * OUTLINE_WIDTH;
        int texheight = m_realheight + 2 * OUTLINE_WIDTH;
        normalizeTexSize(textureTarget, texwidth, texheight);

        // create a new image
        QImage image(texwidth, texheight, QImage::Format_RGB32);
        QPainter painter;
        // start painting the image
        painter.begin(&image);
        painter.setFont(font);
        painter.setRenderHint(QPainter::TextAntialiasing);
        painter.setBackground(Qt::black);
        painter.eraseRect(image.rect());
        // use an artificial blue color. This image is only used internally anyway.
        painter.setPen(Qt::blue);
        // actually paint the character. The position seems right at least with Helvetica
        // at various sizes, I didn't try other fonts. If in the future a user complains about
        // the text being clamped to the top/bottom, change this line.
        painter.drawText(1, m_realheight
                         + 2 * OUTLINE_WIDTH
                         - painter.fontMetrics().descent(),
                         c);
        // end painting the image
        painter.end();

        // *** STEP 2 : extract the raw bitmap from the image ***

        // --> explanation: the image we just rendered is RGB, but actually all the
        //     data is in the B channel because we painted in blue. Now we extract
        //     this blue channel into a separate bitmap that'll be faster to manipulate
        //     in what follows.

        int *rawbitmap = new int[ texwidth * texheight ];
        if (! rawbitmap) return false;
        int n = 0;
        // loop over the pixels of the image, in reverse y direction
        for (int j = texheight - 1; j >= 0; j--)
            for (int i = 0; i < texwidth; i++, n++)
            {
                double x = qBlue(image.pixel(i, j)) / 255.0;
                double y = pow(x, 0.75); /* this applies a gamma correction with gamma factor 0.5.
                  the effect of this is to concentrate the intensities in
                  the large values. This results in a slightly bolder-looking
                  font, which is more suitable for outlining. More importantly,
                  this makes more intense the otherwise dim shades. As the
                  intensity of the outline is proportional to the intensity of
                  the rawbitmap, dim shades give a dim outline which is
                  bad for readability, so we don't want a whole part of a glyph
                  to use a dim shade. Now the problem is that on my setup,
                  e.g. the small "n" had one of its legs spread across two columns
                  of pixels, each with a dim shade.*/
                rawbitmap[n] = static_cast<int>(255.0 * y);
            }

        // *** STEP 3 : compute the neighborhood map from the raw bitmap ***

        // --> explanation: we apply a convolution filter to the raw bitmap
        //     to produce a new map each pixel is associated a float telling how
        //     much it is surrounded by other pixels.

        int *neighborhood = new int[ texwidth * texheight ];
        if (! neighborhood) return false;
        for (int i = 0; i < texheight * texwidth; i++)
            neighborhood[i] = 0;

        for (int i = 0; i < texheight; i++)
        {
            for (int j = 0; j < texwidth; j++)
            {
                n = j + i * texwidth;
                for (int di = -OUTLINE_WIDTH; di <= OUTLINE_WIDTH; di++)
                {
                    for (int dj = -OUTLINE_WIDTH; dj <= OUTLINE_WIDTH; dj++)
                    {
                        int fi = i + di;
                        int fj = j + dj;
                        if (fi >= 0 && fi < texheight && fj >= 0 && fj < texwidth)
                        {
                            int fn = fj + fi * texwidth;
                            neighborhood[fn]
                            = qMax(
                                  neighborhood[fn],
                                  rawbitmap[n]
                                  * OUTLINE_BRUSH[OUTLINE_WIDTH + di]
                                  [OUTLINE_WIDTH + dj]);
                        }
                    }
                }
            }
        }

        // *** STEP 4 : compute the final bitmaps  ***
        // --> explanation: we build the bitmaps that will be passed to OpenGL for texturing.

        GLubyte *glyphbitmap = new GLubyte[ texwidth * texheight ];
        if (! glyphbitmap) return false;
        GLubyte *outlinebitmap = new GLubyte[ texwidth * texheight ];
        if (! outlinebitmap) return false;

        for (int n = 0; n < texwidth * texheight; n++)
        {
            glyphbitmap[n] = static_cast<GLubyte>(rawbitmap[n]);
            int alpha = (neighborhood[n] >> 8) + rawbitmap[n];
            if (alpha > 255)
            {
                alpha = 255;
            }
            outlinebitmap[n] = static_cast<GLubyte>(alpha);
        }

        delete [] rawbitmap;
        delete [] neighborhood;

        // *** STEP 5 : construct OpenGL textures from the final bitmaps ***

        glGenTextures(1, &m_glyphTexture);
        if (! m_glyphTexture) return false;
        glGenTextures(1, &m_outlineTexture);
        if (! m_outlineTexture) return false;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glBindTexture(textureTarget, m_glyphTexture);
        glTexImage2D(
            textureTarget,
            0,
            GL_ALPHA,
            texwidth,
            texheight,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            glyphbitmap);

        glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(textureTarget, m_outlineTexture);
        glTexImage2D(
            textureTarget,
            0,
            GL_ALPHA,
            texwidth,
            texheight,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            outlinebitmap);

        glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // the texture data is now kept alive by OpenGL. It's time to free the bitmaps.
        delete [] glyphbitmap;
        delete [] outlinebitmap;

        // *** STEP 6 : compile the display list ***

        m_quadDisplayList = glGenLists(1);
        if (! m_quadDisplayList) return false;

        int texcoord_width = (textureTarget == GL_TEXTURE_2D) ? 1 : texwidth;
        int texcoord_height = (textureTarget == GL_TEXTURE_2D) ? 1 : texheight;

        glNewList(m_quadDisplayList, GL_COMPILE);
        glBegin(GL_QUADS);
        glTexCoord2i(0, 0);
        glVertex2f(0 , -texheight);
        glTexCoord2i(texcoord_width, 0);
        glVertex2f(texwidth , -texheight);
        glTexCoord2i(texcoord_width, texcoord_height);
        glVertex2f(texwidth, 0);
        glTexCoord2i(0, texcoord_height);
        glVertex2f(0 , 0);
        glEnd();
        glEndList();

        return true;
    }

} // anonymous namespace

namespace GluonGraphics
{

    class TextRenderer::Private
    {
        public:

            Private() : initialized(false) {}
            ~Private() {}

            /**
             * This hash gives the correspondence table between QFonts and QChars
             * (the keys) and the corresponding CharRenderers (the values).
             * Every time a QChar is being met, either it is found in this
             * table, in which case it can be directly rendered, or it is
             * not found, in which case a new CharRenderer is created for
             * it and added to this table.
             */
            QMap<QFont, QHash<QChar, CharRenderer*> > charTable;

            /**
             * The GLWidget in which to render. This is set
             * once and for all by setup().
             */
            GLWidget *glwidget;

            GLboolean textmode;

            bool initialized;

            GLenum textureTarget;

            void do_draw(const QString &string, const QFont& font);
    };

    void TextRenderer::Private::do_draw(const QString &string, const QFont& font)
    {
        int i;
        GLfloat color[4];
        glGetFloatv(GL_CURRENT_COLOR, color);

        QHash<QChar, CharRenderer*>& chars = charTable[font];
        const QFontMetrics fontMetrics(font);

        // Pass 1: render and cache the glyphs that are not yet cached.
        for (i = 0; i < string.size(); i++)
        {
            if (! chars.contains(string[i]))
            {
                CharRenderer *c = new CharRenderer;
                if (!c->initialize(string[i], font, textureTarget))
                {
                    delete c;
                    c = new CharRenderer;
                    qDebug() << "Character " << string[i]
                    << "(unicode" << string[i].unicode()
                    << ") failed to render using the following font:";
                    qDebug() << font.toString();
                    if (!c->initialize('*', font, textureTarget))
                    {
                        qDebug() << "Can't render even a simple character (*).";
                        qDebug() << "Are you using a bad font, or what?";
                        qDebug() << "The font being used is:";
                        qDebug() << font.toString();
                        Q_ASSERT(false);
                    }
                }
                chars.insert(string[i], c);
            }
        }

        // Pass 2: render the outline
        glColor4f(0, 0, 0, color[3]);
        glPushMatrix();
        for (i = 0; i < string.size(); i++)
        {
            chars.value(string[i])->drawOutline();
            glTranslatef(fontMetrics.charWidth(string, i), 0, 0);
        }
        glPopMatrix();

        // Pass 3: render the glyphs themselves
        glPushMatrix();
        glColor4fv(color);
        for (i = 0; i < string.size(); i++)
        {
            chars.value(string[i])->drawGlyph();
            glTranslatef(fontMetrics.charWidth(string, i), 0, 0);
        }
        glPopMatrix();
    }


    TextRenderer::TextRenderer() : d(new Private)
    {
        d->glwidget = 0;
        d->textmode = false;
    }

    TextRenderer::~TextRenderer()
    {
        QMap<QFont, QHash<QChar, CharRenderer*> >::iterator j = d->charTable.begin();
        for (; j != d->charTable.end(); j++)
        {
            QHash<QChar, CharRenderer *>::iterator i = j.value().begin();
            for (; i != j.value().end(); i++)
            {
                delete i.value();
            }
        }
        delete d;
    }

    // void TextRenderer::setGLWidget( GLWidget *glwidget )
    // {
    //   d->glwidget = glwidget;
    //   d->font = d->glwidget->font();
    // }


    void TextRenderer::begin(GLWidget *widget)
    {
        if (!d->initialized)
        {
            if (GLEW_ARB_texture_rectangle)
            {
                d->textureTarget = GL_TEXTURE_RECTANGLE_ARB;
                qDebug() << "OpenGL extension GL_ARB_texture_rectangle is present.";
            }
            else
            {
                d->textureTarget = GL_TEXTURE_2D;
                qDebug() << "OpenGL extension GL_ARB_texture_rectangle is absent.";
            }
            d->initialized = true;
        }

        // already called begin
        if (d->glwidget == widget)
        {
            return;
        }


        // make sure we called ::end
        Q_ASSERT(!d->glwidget);

        d->glwidget = widget;
        d->textmode = true;
        //   glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
        glDisable(GL_CULL_FACE);
        glEnable(d->textureTarget);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, d->glwidget->width(), 0, d->glwidget->height(), 0, 1);
        glMatrixMode(GL_MODELVIEW);
    }

    void TextRenderer::end()
    {
        if (d->glwidget)
        {
            Q_ASSERT(d->textmode);
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopAttrib();
            d->textmode = false;
            d->glwidget = 0;
        }
    }

    int TextRenderer::draw(int x, int y, const QString &string, const QFont& font)
    {
        Q_ASSERT(d->textmode);
        if (string.isEmpty()) return 0;
        glPushMatrix();
        glLoadIdentity();
        const QFontMetrics fontMetrics(font);
        glTranslatef(x, d->glwidget->height() - y, 0);

        // Split the string into lines
        QStringList lines = string.split('\n');
        foreach(const QString &line, lines)
        {
            d->do_draw(line, font);
            // Move one line down
            glTranslatef(0, -fontMetrics.lineSpacing(), 0);
        }

        glPopMatrix();
        return lines.count() * fontMetrics.lineSpacing();
    }

    int TextRenderer::draw(const QRect& rect, const QString &string, int flags, const QFont& font)
    {
        glDisable(GL_DEPTH_TEST);
        const QFontMetrics fontMetrics(font);
        // First break the string into lines
        QStringList lines;
        if (flags & Qt::TextSingleLine)
        {
            // Entire string is a single line
            lines.append(string);
        }
        else
        {
            // Break at newlines
            lines = string.split('\n');
        }
        if (flags & Qt::TextWordWrap)
        {
            // Wrap the lines if necessary
            QStringList newlines;
            foreach(const QString &line, lines)
            {
                QString newline;
                int newlinew = 0;
                QStringList words = line.simplified().split(' ');
                foreach(const QString &word, words)
                {
                    int wordw = fontMetrics.width(' ' + word);
                    if (newlinew + wordw > rect.width())
                    {
                        // Break the line here
                        newlines.append(newline);
                        newline = QString();
                        newlinew = 0;
                    }
                    if (!newline.isEmpty())
                    {
                        newline += ' ';
                    }
                    newline += word;
                    newlinew += wordw;
                }
                if (!newline.isEmpty())
                {
                    newlines.append(newline);
                }
            }
            lines = newlines;
        }

        // Calculate text height in pixels
        int texth = lines.count() * fontMetrics.lineSpacing();

        // Calculate vertical position of the first line
        int y = rect.top();
        if (flags & Qt::AlignBottom)
        {
            y = rect.bottom() - texth;
        }
        else if (flags & Qt::AlignVCenter)
        {
            y = rect.center().y() - texth / 2;
        }
        // Draw each line
        for (int i = 0; i < lines.count(); i++)
        {
            const QString& line = lines[i];
            // Calculate horizontal position
            int x = rect.left();
            if (flags & Qt::AlignRight)
            {
                x = rect.right() - fontMetrics.width(line);
            }
            else if (flags & Qt::AlignHCenter)
            {
                x = rect.center().x() - fontMetrics.width(line) / 2;
            }
            // Draw
            y += draw(x, y, line, font);
        }
        return texth;
    }

    int TextRenderer::draw(const QVector3D &pos, const QString &string, const QFont& font)
    {
        Q_ASSERT(d->textmode);
        if (string.isEmpty()) return 0;

        const QFontMetrics fontMetrics(font);
        int w = fontMetrics.width(string);
        int h = fontMetrics.height();

        // TODO: uncomment once Camera has project() method
        QVector3D wincoords;// = d->glwidget->camera()->project(pos);

        // project is in QT window coordinates
//    wincoords.y() = d->glwidget->height() - wincoords.y();
//
//    wincoords.x() -= w/2;
//    wincoords.y() += h/2;

        wincoords.setY(d->glwidget->height() - wincoords.y());

        wincoords.setX(wincoords.x() - w / 2);
        wincoords.setY(wincoords.y() + h / 2);




        glPushMatrix();
        glLoadIdentity();
        glTranslatef(static_cast<int>(wincoords.x()),
                     static_cast<int>(wincoords.y()),
                     -wincoords.z());
        d->do_draw(string, font);
        glPopMatrix();
        return fontMetrics.lineSpacing();
    }

    bool TextRenderer::isActive()
    {
        return d->glwidget;
    }

} // namespace GluonGraphics

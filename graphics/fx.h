/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#ifndef EFFECT_H
#define EFFECT_H

#include <QtCore/QString>
#include <QtCore/QPointF>

#include "gluon_graphics_export.h"
#include "shader.h"
#include "program.h"

/**
 * \defgroup
 */
//@{


namespace GluonGraphics
{

    class Fx;
    class GLUON_GRAPHICS_EXPORT Fx : public Program
    {

        public:
            Fx(const QString& vertexShader, const QString& fragmentShader);
            Fx();
    };

    /* @short LightFx class
     *
     * Add Lighter . setAlpha between 1 and 10
     **/
    class LightFx: public Fx
    {
        public :
            LightFx();
            void setAlpha(float alpha);
            float alpha()
            {
                return m_alpha;
            }
        private:
            float m_alpha;
    };

    /* @short LightFx class
     *
     * Add Posterize effect . SetLevel between 1 and 20.
     **/
    class PosterizeFx : public Fx
    {
        public :
            PosterizeFx();
            void setLevel(float level);
            float level()
            {
                return m_level;
            }
        private:
            float m_level;

    };
    /* @short LightFx class
     *
     * Add Mosaic effect . SetLevel between 1 and 256.
     **/
    class MosaicFx : public Fx
    {
        public :
            MosaicFx();
            void setTileSize(float t);
        private:
            float m_tileSize;
    };
    /* @short KGrayScaleFx class
     *
     * change to gray
     **/
    class GrayScaleFx: public Fx
    {
        public:
            GrayScaleFx();
    };

    /* @short BlurFx class
     *
     * setBlur
     **/
    class BlurFx: public Fx
    {
        public:
            BlurFx();
            void setBlurLevel(QPointF blurLevel);
            void setBlurLevel(float x, float y)
            {
                setBlurLevel(QPointF(x, y));
            }
            QPointF blurLevel()
            {
                return m_blurLevel;
            }
        private:
            QPointF m_blurLevel;
    };

} //namespace



//@}
#endif // GLUON_GRAPHICS_EFFECT_H

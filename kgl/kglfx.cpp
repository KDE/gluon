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

#include "kglfx.h"

KGLFx::KGLFx(const QString& vertexShader, const QString& fragmentShader)
    :KGLProgram(vertexShader,fragmentShader)
{

}
KGLFx::KGLFx()
    :KGLProgram()
{
}
//==========================LIGHT=====================================
KGLLightFx::KGLLightFx()
    :KGLFx()
{
    addShader(new KGLFragmentShader(":shaders/light.frag"));
    link();
    setAlpha(0);

}

void KGLLightFx::setAlpha(float alpha)
{
    m_alpha=alpha;
    bind();
    setUniform("alpha",alpha);
    unbind();
}

//==========================POSTERIZE=====================================
KGLPosterizeFx::KGLPosterizeFx()
          :KGLFx()
{
    addShader(new KGLFragmentShader(":shaders/posterize.frag"));
    link();
    setLevel(20);
}

void KGLPosterizeFx::setLevel(float level)
{
    m_level=level;
    bind();
    setUniform("level", level);
    unbind();
}
//==========================MOSAIC=====================================
KGLMosaicFx::KGLMosaicFx()
    :KGLFx()
{
    addShader(new KGLFragmentShader(":shaders/mosaic.frag"));
    link();
    bind();
    setUniform("texSize", 128);
    unbind();
    setTileSize(1);
}
void KGLMosaicFx::setTileSize(float t)
{
    m_tileSize=t;
    bind();
    setUniform("tileSize", t);
    unbind();
}

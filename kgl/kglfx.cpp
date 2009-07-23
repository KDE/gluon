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

KGLFx::KGLFx()
{
    m_program = new KGLProgram;
}

//===========LIGHT ==========================

KGLLightFx::KGLLightFx()
    : KGLFx()
{
      program()->addShader(new KGLVertexShader(":shaders/light.vert"));
      program()->addShader(new KGLFragmentShader(":shaders/light.frag"));
      program()->link();
}

//==========BLUR =========================

KGLBlurFx::KGLBlurFx()
    : KGLFx()
{
    program()->addShader(new KGLVertexShader(":shaders/blur.vert"));
    program()->addShader(new KGLFragmentShader(":shaders/blur.frag"));
    program()->link();
}

//========= PIXELATE ====================

KGLPixelateFx::KGLPixelateFx()
    : KGLFx()
{
      program()->addShader(new KGLVertexShader(":shaders/pixelate.vert"));
      program()->addShader(new KGLFragmentShader(":shaders/pixelate.frag"));
      program()->link();
}

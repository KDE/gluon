/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
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

#include "posterizeshader.h"
namespace GluonGraphics
{
    PosterizeShader::PosterizeShader(QObject *parent)
            : QGLShaderProgram(parent)
    {
        mLevel = 20;
        vertexShader = new QGLShader(QGLShader::Vertex);
        fragmentShader = new QGLShader(QGLShader::Fragment);

        vertexShader->compileSourceFile(":/GLSL/generic.vert");
        fragmentShader->compileSourceFile(":/GLSL/posterize.frag");

        addShader(vertexShader);
        addShader(fragmentShader);

        link();
        qDebug() << log();


    }

    void PosterizeShader::setLevel(const float &value)
    {
        mLevel = value;
        bind();
        setUniformValue("level", GLfloat(value));
        release();
    }
}

/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "lightshader.h"
#include <QFile>
#include <QDebug>
namespace GluonGraphics
{
    LightShader::LightShader(QObject *parent)
            : QGLShaderProgram(parent)
    {

        mAlpha = 0;
        vertexShader = new QGLShader(QGLShader::Vertex);
        fragmentShader = new QGLShader(QGLShader::Fragment);

        vertexShader->compileSourceFile(":/GLSL/generic.vert");
        fragmentShader->compileSourceFile(":/GLSL/light.frag");

        addShader(vertexShader);
        addShader(fragmentShader);

        link();

        qDebug() << log();

    }

    void LightShader::setAlpha(const float& value)
    {
        mAlpha = value;
        bind();
        setUniformValue("alpha", GLfloat(value));
        release();
    }

}

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
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

#include "mosaicshader.h"

MosaicShader::MosaicShader(QObject *parent) :
        QGLShaderProgram(parent)
{
    mTileSize = 1;
    vertexShader = new QGLShader(QGLShader::Vertex);
    fragmentShader = new QGLShader(QGLShader::Fragment);

    vertexShader->compileSourceFile(":/GLSL/generic.vert");
    fragmentShader->compileSourceFile(":/GLSL/mosaic.frag");

    addShader(vertexShader);
    addShader(fragmentShader);

    link();

    bind();
    setUniformValue("texSize", float(128.0));
    setUniformValue("tileSize", float(2.0));
    release();

    qDebug() << log();

}

void MosaicShader::setTileSize(const float& value)
{

    mTileSize = value;
    bind();
    setUniformValue("tileSize", 2);
    release();
}

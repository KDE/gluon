/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2010
    Author:
    Sacha schutz
    ...

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

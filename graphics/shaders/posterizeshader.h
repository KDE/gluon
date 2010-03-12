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

#ifndef POSTERIZESHADER_H
#define POSTERIZESHADER_H

#include <QGLShaderProgram>
#include "../gluon_graphics_export.h"

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT PosterizeShader : public QGLShaderProgram
    {
    public:
        explicit PosterizeShader(QObject *parent = 0);
        void setLevel(const float& value);
        const float& level()
        {
            return mLevel;
        }

    private:
        QGLShader * vertexShader;
        QGLShader * fragmentShader;
        float mLevel;


    };
}

#endif // POSTERIZESHADER_H

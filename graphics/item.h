/******************************************************************************
 * This file is part of the Gluon Development Platform
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
#ifndef Item_H
#define Item_H

#include "transform.h"
#include "mesh.h"
#include "glpainter.h"
#include "texture.h"
#include "gluon_graphics_export.h"
#include <QGLShaderProgram>
namespace GluonGraphics
{
    class Engine;
    class GLUON_GRAPHICS_EXPORT Item : public Transform
    {

        public:
            Item(QObject * parent = 0);
            explicit Item(Mesh * mesh, QObject* parent = 0);
            ~Item();

            virtual void paintGL();
            void setColor(const QColor& col);
            void setAlpha(const float& alpha);
            void setTexture(Texture * texture);
            void setTexture(const QPixmap& pix);
            void setTexture(const QImage& img);
            void setTexture(const QString& path);
            void setShader(QGLShaderProgram* program);
            void removeShader();
            void setMesh(Mesh * mesh)
            {
                m_mesh = mesh;
            }
            const QColor& color();
            const float& alpha();
            Mesh * mesh()
            {
                return m_mesh;
            }
        protected:
            void init();
            void drawMesh();

        private:
            Mesh * m_mesh;
            QGLShaderProgram *mProgram;




    };

}
#endif // Item_H

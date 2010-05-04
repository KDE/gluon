/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef DISCSECTIONRENDERERCOMPONENT_H
#define DISCSECTIONRENDERERCOMPONENT_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

namespace GluonEngine
{
    class Asset;

    class GLUON_ENGINE_EXPORT DiscSectionRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT(GluonEngine::DiscSectionRendererComponent)
            Q_PROPERTY(float radius READ radius WRITE setRadius)
            Q_PROPERTY(uint nbPoints READ nbPoints WRITE setNbPoints)
            Q_PROPERTY(float degrees READ degrees WRITE setDegrees)
             Q_PROPERTY(QColor color READ color WRITE setColor)
            Q_PROPERTY(GluonEngine::Asset* texture READ texture WRITE setTexture)
            Q_INTERFACES(GluonEngine::Component)

        public:
            DiscSectionRendererComponent(QObject* parent = 0);
            DiscSectionRendererComponent(const DiscSectionRendererComponent& other);
            virtual ~DiscSectionRendererComponent();

            virtual void initialize();
            virtual void start();
            virtual void draw(int timeLapse = 0);
            virtual void cleanup();

            virtual float radius();
            virtual void setRadius(float newRadius);
            virtual uint nbPoints();
            virtual void setNbPoints(uint newNbPoints);
            virtual float degrees();
            virtual void setDegrees(float newDegrees);
            
            virtual QColor color();
            virtual Asset* texture();

        public slots:
            virtual void setColor(const QColor& color);
            virtual void setColor(int r, int g, int b, int a = 255);
            virtual void setTexture(Asset* asset);
            
        private:
            void setDiscSection(QVector3D position, float radius, uint nbPoints, float degrees, QColor color);
            
            class DiscSectionRendererComponentPrivate;
            DiscSectionRendererComponentPrivate * const d;
    };

}

Q_DECLARE_METATYPE(GluonEngine::DiscSectionRendererComponent)
Q_DECLARE_METATYPE(GluonEngine::DiscSectionRendererComponent*)

#endif
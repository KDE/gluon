/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#ifndef GLUON_ENGINE_MESHRENDERERCOMPONENT_H
#define GLUON_ENGINE_MESHRENDERERCOMPONENT_H

#include <engine/component.h>

namespace GluonGraphics
{
    class MaterialInstance;
}

namespace GluonEngine
{
    class Asset;

    class MeshRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::MeshRendererComponent )
            Q_INTERFACES( GluonEngine::Component )

            Q_PROPERTY( GluonEngine::Asset* mesh READ mesh WRITE setMesh )
            Q_PROPERTY( GluonGraphics::MaterialInstance* material READ material WRITE setMaterial )

            Q_CLASSINFO( "org.gluon.category", "Graphics Rendering" )
            Q_CLASSINFO( "org.gluon.icon", "image-x-generic" )

        public:
            Q_INVOKABLE MeshRendererComponent( QObject* parent = 0 );
            ~MeshRendererComponent();
            QString category() const;

            void initialize();
            void start();
            void draw( int timeLapse = 0 );
            void cleanup();

            GluonEngine::Asset* mesh();
            GluonGraphics::MaterialInstance* material();

        public Q_SLOTS:
            void setMesh( GluonEngine::Asset* mesh );
            void setMaterial( GluonGraphics::MaterialInstance* material );
            void setMaterial( const QString& path );

        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::MeshRendererComponent* )

#endif // GLUON_ENGINE_MESHRENDERERCOMPONENT_H

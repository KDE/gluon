/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_ENGINE_BEAMRENDERERCOMPONENT_H
#define GLUON_ENGINE_BEAMRENDERERCOMPONENT_H

#include <engine/component.h>

namespace GluonGraphics
{
    class MaterialInstance;
}

namespace GluonEngine
{
    class Asset;

    class GLUON_COMPONENT_BEAMRENDERER_EXPORT BeamRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::BeamRendererComponent )
            Q_PROPERTY( QSizeF size READ size WRITE setSize )
            Q_PROPERTY( GluonGraphics::MaterialInstance* baseMaterial READ baseMaterial WRITE setBaseMaterial )
            Q_PROPERTY( GluonGraphics::MaterialInstance* beamMaterial READ beamMaterial WRITE setBeamMaterial )
            Q_PROPERTY( GluonGraphics::MaterialInstance* tipMaterial READ tipMaterial WRITE setTipMaterial )
            Q_INTERFACES( GluonEngine::Component )

        public:
            Q_INVOKABLE BeamRendererComponent( QObject* parent = 0 );
            virtual ~BeamRendererComponent();
            virtual QString category() const;

            virtual void initialize();
            virtual void start();
            virtual void draw( int timeLapse = 0 );
            virtual void cleanup();

            virtual QSizeF size();
            virtual GluonGraphics::MaterialInstance* baseMaterial();
            virtual GluonGraphics::MaterialInstance* beamMaterial();
            virtual GluonGraphics::MaterialInstance* tipMaterial();

        public Q_SLOTS:
            virtual void setSize( const QSizeF& size );
            virtual void setBaseMaterial( GluonGraphics::MaterialInstance* material );
            virtual void setBaseMaterial( const QString& path );
            virtual void setBeamMaterial( GluonGraphics::MaterialInstance* material );
            virtual void setBeamMaterial( const QString& path );
            virtual void setTipMaterial( GluonGraphics::MaterialInstance* material );
            virtual void setTipMaterial( const QString& path );

        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::BeamRendererComponent* )

#endif // GLUON_ENGINE_BEAMRENDERERCOMPONENT_H

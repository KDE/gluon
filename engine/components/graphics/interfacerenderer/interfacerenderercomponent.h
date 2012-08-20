/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
#define GLUON_ENGINE_SPRITERENDERERCOMPONENT_H

#include <engine/component.h>

namespace GluonEngine
{
    class Asset;

    class InterfaceRendererComponent : public Component
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Component )
            GLUON_OBJECT( GluonEngine::InterfaceRendererComponent )

            Q_PROPERTY( GluonEngine::Asset* qtquickfile READ qtQuickFile WRITE setQtQuickFile )

            Q_CLASSINFO( "org.gluon.category", "Graphics Rendering" )
            Q_CLASSINFO( "org.gluon.icon", "image-x-generic" )

        public:
            Q_INVOKABLE InterfaceRendererComponent( QObject* parent = 0 );
            virtual ~InterfaceRendererComponent();
            virtual QString category() const;

            virtual void initialize();
            virtual void cleanup();

            Asset* qtQuickFile() const;
            void setQtQuickFile( Asset* asset );

        public Q_SLOTS:
            void sendEvent( QEvent* event );

        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::InterfaceRendererComponent* )

#endif // GLUON_ENGINE_SPRITERENDERERCOMPONENT_H

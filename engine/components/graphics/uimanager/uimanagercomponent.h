/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Giulio Camuffo <giuliocamuffo@gmail.com>
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

#ifndef GLUON_ENGINE_UIMANAGERCOMPONENT_H
#define GLUON_ENGINE_UIMANAGERCOMPONENT_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

class QScriptValue;

namespace GluonEngine
{
    class Asset;
    class UiAsset;

    class GLUON_COMPONENT_UIMANAGER_EXPORT UiManagerComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::UiManagerComponent )
            Q_PROPERTY( QSizeF size READ size WRITE setSize )
            Q_PROPERTY( GluonEngine::UiAsset* ui READ ui WRITE setUi )
            Q_INTERFACES( GluonEngine::Component )

        public:
            Q_INVOKABLE UiManagerComponent( QObject* parent = 0 );
            UiManagerComponent( const UiManagerComponent& other );
            virtual ~UiManagerComponent();
            virtual QString category() const;

            virtual void initialize();
            virtual void start();
            virtual void draw( int timeLapse = 0 );
            void update( int elapsedMilliseconds );
            virtual void cleanup();

            UiAsset* ui() const;
            virtual QSizeF size() const;

            void setScriptEngine( QScriptValue &value );

        public slots:
            void setUi(UiAsset* ui);
            virtual void setSize( const QSizeF& size );

        private:
            class UiManagerComponentPrivate;
            UiManagerComponentPrivate* const d;

            Q_PRIVATE_SLOT( d, void resizeQmlItem( const QRectF& rect ) );
            Q_PRIVATE_SLOT( d, void reload() );
    };

}

Q_DECLARE_METATYPE( GluonEngine::UiManagerComponent )
Q_DECLARE_METATYPE( GluonEngine::UiManagerComponent* )

#endif // GLUON_ENGINE_SPRITERENDERERCOMPONENT_H

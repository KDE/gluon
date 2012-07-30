/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUONENGINE_SCRIPTINGCOMPONENT_H
#define GLUONENGINE_SCRIPTINGCOMPONENT_H

#include "scriptingasset.h"

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

class QScriptValue;
namespace GluonEngine
{
    class GLUON_COMPONENT_SCRIPTING_EXPORT ScriptingComponent : public Component
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Component )
            GLUON_OBJECT( GluonEngine::ScriptingComponent )

            Q_PROPERTY( GluonEngine::ScriptingAsset* script READ script WRITE setScript )

            Q_CLASSINFO( "org.gluon.category", "Game Logic" )
            Q_CLASSINFO( "org.gluon.icon", "application-javascript" )

        public:
            Q_INVOKABLE ScriptingComponent( QObject* parent = 0 );
            virtual ~ScriptingComponent();

            virtual QString category() const;

            virtual void initialize();
            virtual void start();
            virtual void update( int elapsedMilliseconds );
            virtual void draw( int timeLapse = 0 );
            virtual void stop();
            virtual void cleanup();
            virtual void serialize();
            virtual void restore();

            ScriptingAsset* script() const;

        public Q_SLOTS:
            void setScript( GluonEngine::ScriptingAsset* newAsset );
            void scriptAssetUpdated();

            QScriptValue scriptObject();

        private:
            class ScriptingComponentPrivate;
            ScriptingComponentPrivate* const d;
            QScriptValue restoreComponent();
            void serializeComponent( QScriptValue object );
    };
}

Q_DECLARE_METATYPE( GluonEngine::ScriptingComponent* )

#endif // GLUONENGINE_SCRIPTINGCOMPONENT_H

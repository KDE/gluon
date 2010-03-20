/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GLUON_ENGINE_QTSCRIPTCOMPONENT_H
#define GLUON_ENGINE_QTSCRIPTCOMPONENT_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

namespace GluonEngine
{
    class Asset;

    class GLUON_ENGINE_EXPORT QtScriptComponent : public Component
    {
        Q_OBJECT
        GLUON_OBJECT(GluonEngine::QtScriptComponent)
        Q_INTERFACES(GluonEngine::Component)

        Q_PROPERTY(GluonEngine::Asset* script READ script WRITE setScript)

        public:
            QtScriptComponent ( QObject* parent = 0 );
            QtScriptComponent ( const QtScriptComponent& other);
            virtual ~QtScriptComponent();

            virtual void start();
            virtual void update ( int elapsedMilliseconds );
            virtual void draw ( int timeLapse = 0 );

            virtual Asset* script();

        public slots:
            virtual void setScript(GluonEngine::Asset* asset);

        private:
            class QtScriptComponentPrivate;
            QtScriptComponentPrivate *d;
    };

}

#endif // GLUON_ENGINE_QTSCRIPTCOMPONENT_H

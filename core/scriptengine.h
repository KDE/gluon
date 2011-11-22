/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef GLUON_CORE_SCRIPTENGINE_H
#define GLUON_CORE_SCRIPTENGINE_H

#include "gluon_core_export.h"

#include "singleton.h"

#include <QtScript/QScriptEngine>

namespace GluonCore
{
    class GLUON_CORE_EXPORT ScriptEngine : public Singleton<ScriptEngine>
    {
            Q_OBJECT
            GLUON_SINGLETON( ScriptEngine )
        public:
            QScriptEngine* scriptEngine();
            void resetEngine();

        private:
            ~ScriptEngine();

            class Private;
            Private* const d;
    };
}

#endif // GLUON_CORE_SCRIPTENGINE_H

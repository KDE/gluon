/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#ifndef GLUON_ENGINE_PREFAB_H
#define GLUON_ENGINE_PREFAB_H

#include "core/gluonobject.h"

#include <QtCore/QSharedData>

namespace GluonEngine
{
    class PrefabPrivate;

    class Prefab : public GluonCore::GluonObject
    {
            Q_OBJECT
            GLUON_OBJECT(GluonEngine::Prefab);

        public:
            Prefab(QObject * parent = 0);
            Prefab(const Prefab &other, QObject * parent = 0);
            ~Prefab();

        private:
            QSharedDataPointer<PrefabPrivate> d;
    };
}

Q_DECLARE_METATYPE(GluonEngine::Prefab)
Q_DECLARE_METATYPE(GluonEngine::Prefab*)

#endif  // GLUON_ENGINE_PREFAB_H

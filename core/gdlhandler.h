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

#ifndef GLUON_CORE_GDLHANDLER_H
#define GLUON_CORE_GDLHANDLER_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include "singleton.h"
#include "gluon_core_export.h"

namespace GluonCore
{
    class GluonObject;

    class GLUON_CORE_EXPORT GDLHandler : public Singleton<GDLHandler>
    {
            Q_OBJECT

        public:
            QList<GluonObject *> parseGDL(const QString parseThis, QObject * parent);
            QString serializeGDL(QList<const GluonObject *> serializeThis);

        private:
            friend class Singleton<GDLHandler>;

            GDLHandler();
            virtual ~GDLHandler();
            Q_DISABLE_COPY(GDLHandler)

            GluonObject * instantiateObject(QString className);
            GluonObject * createObject(QStringList objectStringList, QObject * parent);
            /**
             * Returns a list of QStringLists, where each QStringList is:
             * Index 0: The type of the object
             * Index 1: The object's name
             * Following indices: All the values in the order of definition, alternating between property names and values (in that order)
             * If any value begins with {, it is a new object
             */
            QList<QStringList> tokenizeObject(QString objectString);
    };
}

#endif  // GLUON_CORE_GDLHANDLER_H

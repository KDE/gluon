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

#ifndef GLUON_ENGINE_SAVABLE_H
#define GLUON_ENGINE_SAVABLE_H

#include "gluon_engine_export.h"

#include <QString>

namespace GluonCore
{
    class GluonObject;
}

namespace GluonEngine
{
    /**
     * The Savable class decorates any GluonObject to allow for saving it
     * to a GDL file (the filename it has).
     *
     * Note that you should only ever inherit Savable in a class which also
     * has a property called "file" which is of QVariant type QUrl.
     *
     * It is designed with the GluonEngine::Asset class in mind, but can
     * handle any class with the above requirement in order.
     */
    class GLUON_ENGINE_EXPORT Savable
    {
        public:
            virtual ~Savable() {};
            /**
             * Saves the passed asset to the filename indicated
             * by the GluonObject's file property.
             *
             * @param object     The instance you wish to save
             *
             * @return Whether or not the file was successfully saved
             *
             * @see GluonEngine::Asset
             */
            static bool saveToFile(GluonCore::GluonObject * object);

            /**
             * Serialise the contents of the asset to GDL. This function should
             * be implemented in a way which returns the GDL for what the asset
             * contains.
             *
             * @return The serialised contents of the asset
             */
            virtual QString contentsToGDL() = 0;

            /**
             * Set this to true any time you do anything to the asset which would
             * be considered a change to the data represented by it
             */
            bool savableDirty;
    };
}

#endif // GLUON_ENGINE_SAVABLE_H

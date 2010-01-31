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

#include <QString>

namespace GluonEngine
{
    class Asset;

    /**
     * The Savable class decorates any Asset to allow for saving that Asset
     * to a GDL file (the filename it has). Note that you should only ever
     * inherit Savable in a class which also inherits Asset.
     */
    class Savable
    {
        public:
            virtual ~Savable();
            /**
             * Saves the passed asset to the filename indicated
             * by the Asset's file property.
             *
             * @param asset     The asset to save
             *
             * @return Whether or not the file was successfully saved
             *
             * @see Gluon::Asset
             */
            static bool saveToFile(Asset * asset);

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

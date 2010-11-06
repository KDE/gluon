/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
            static bool saveToFile( GluonCore::GluonObject* object );

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

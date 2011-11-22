/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef GLUONCORE_GDLSERIALIZER_H
#define GLUONCORE_GDLSERIALIZER_H

#include "gluon_core_export.h"
#include "singleton.h"
#include "gluonobject.h"

class QUrl;
namespace GluonCore
{
    /**
     * \brief Helper class to serialize and deserialize GDL files.
     *
     * This class provides a simple API for reading and writing GDL
     * files to disk.
     */
    class GLUON_CORE_EXPORT GDLSerializer : public Singleton< GDLSerializer >
    {
            Q_OBJECT
            GLUON_SINGLETON( GDLSerializer )

        public:
            /**
             * Read in a file and parse its contents to a list of objects.
             *
             * \param url The url of a file to read from.
             * \param objects A list that will be cleared and populated with objects.
             * \param project The project the objects will belong to. If null, the first created object will be used.
             *
             * \return True when successful, false if any error occured.
             */
            bool read( const QUrl& url, GluonObjectList& objects, GluonObject* project = 0 );

            /**
             * Write a list of GluonObjects to a file.
             *
             * \param url The url of a file to write to.
             * \param objects A list of objects to serialize to the file.
             *
             * \return True when succesful, false if any error occured.
             */
            bool write( const QUrl& url, const GluonObjectList& objects );

            /**
             * Write a list of GluonObjects to a device.
             *
             * \param device The device to write to.
             * \param objects A list of objects to write to the device.
             *
             * \return True if successful, false if any error occured.
             */
            bool write( QIODevice* device, const GluonObjectList& objects );

            /**
             * Parse a string to a list of objects.
             *
             * \param data The data to parse.
             * \param objects A list that will be cleared and populated with objects.
             * \param project The project the objects will belong to. If null, the first created object will be used.
             *
             * \return True when successful, false if any error occured.
             */
            bool parse( const QByteArray& data, GluonObjectList& objects, GluonObject* project = 0 );
    };

}

#endif // GLUONCORE_GDLSERIALIZER_H

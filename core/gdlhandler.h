/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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
#ifndef GLUON_CORE_GDLHANDLER_H
#define GLUON_CORE_GDLHANDLER_H

#include "singleton.h"
#include "gluon_core_export.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

namespace GluonCore
{
    class GluonObject;

    /**
     * \brief Functionality for serializing and deserializing GluonObjects
     *
     * This singleton class provides functionality for serializing and deserializing
     * GluonObject instances to and from the GDL object definition language.
     *
     * A generalized use scenario for GDLHandler is loading a gdl file from disk and
     * deserializing it into GluonObject instances, do a change to some object in
     * the hierarchy and then save it back into a file. The following function will
     * do that:
     *
     * \code
    bool fiddleWithObjects(QString filename)
    {
    QFile projectFile(QFileInfo(filename().toLocalFile()).fileName());
    if (!projectFile.open(QIODevice::ReadWrite))
        return false;

    QTextStream projectReader(&projectFile);
    QString fileContents = projectReader.readAll();

    if (fileContents.isEmpty())
        return false;

    QList<GluonObject*> objectList = GluonCore::GDLHandler::instance()->parseGDL(fileContents, this->parent());

    foreach(GluonObject* obj, objectList)
    {
        obj->setName(QString("%1 %2").arg(obj->name()).arg("changed"));
    }

    QString serializedData = GluonCore::GDLHandler::instance()->serializeGDL();
    QTextStream out(&projectFile);
    out << serializedData;
    projectFile.close();

    return true;
    }\endcode
     *
     * <b>The Gluon Definition Language</b>
     *
     * The Gluon Definition Language, or GDL, is a very simple, hierarchical object
     * definition language, designed for use with GluonObject derived classes. The
     * structure of the language can easiest be described as follows:
     *
     * \verbatim
    { ClassName(ObjectName)
    PropertyName DataTypeName(Value)
    PropertyName2 DataTypeName2(Value2)
    { ClassName(ObjectName)
        PropertyName DataTypeName(Value)
    }
    }
    \endverbatim
     *
     * The above sample represents two nested objects of the type ClassName, both named
     * ObjectName. The fully qualified name for the objects respectively are ObjectName
     * and ObjectName.ObjectName and this can be used in properties as well.
     *
     * PropertyName and PropertyName2 are as the names indicate properties named that way.
     * Their values are Value and Value2 respectively, and the data type contained in the
     * properties are DataTypeName and DataTypeName2 respectively.
     *
     * An important aspect of GDL is the ability for any property to reference any other
     * object in the hierarchy. An example of this might be:
     *
     * \verbatim
    { GluonObject(AnotherObject)
    reference GluonObject(AnObject.AChildObject)
    }
    { GluonObject(AnObject)
    { GluonObject(AChildObject)
    }
    }
    \endverbatim
     *
     * The property reference on the AnotherObject object is then a reference to the object
     * with the fully qualified name AnObject.AChildObject. Also shown here is the fact
     * that an object does not have to be defined before it is able to be referenced.
     *
     * Finally, this example also shows how GDL can have multiple root nodes in the same
     * file. For these references to work correctly, it is vital that all the objects
     * have the same object parent (that is, the parent passed in the parseGDL function).
     *
     * <b>Data types</b>
     *
     * Data types supported by GDL outside of the classes registered in GluonObjectFactory are:
     *
     * - string(value) where value is any string (no quotation marks required)
     * - bool(value) where value is the string literal true or false
     * - float(value) where value is any floating point number
     * - vector3d(value;value;value) where value is any floating point number
     * - quaternion(value;value;value;value) where value is any floating point number
     * - int(value) where value is any integer value
     * - uint(value) where value is any unsigned integer value
     * - size2d(value;value) where value is any floating point value
     * - vector2d(value;value) where value is any floating point value
     * - rgba(value;value;value;value) where value is a number between 0 and 255 inclucive
     * - file(value) where value is a valid filename ( see also GluonEngine::Asset:file )
     * - url(value) where value is a valid URL
     *
     */
    class GLUON_CORE_EXPORT GDLHandler : public Singleton<GDLHandler>
    {
            Q_OBJECT

        public:
            /**
             * Deserialise a GDL string representation into their GluonObject counterpart
             *
             * \note Please be aware that in the case of an incorrect GDL string, you will not be given
             * a correct list of GluonObjects. That is, the function does not currently degrade gracefully.
             * As such, please ensure the data is acceptable upon return.
             *
             * @param   parseThis   The GDL string that you wish to parse into GluonObject instances
             * @param   parent      The QObject you wish the objects to be parented to
             * @return  A list of generated GluonObject instances
             */
            QList<GluonObject*> parseGDL( const QString data, qint64 size, QObject* parent = 0 );
            QList<GluonObject*> parseGDL( const QString& fileName, QObject* parent = 0 );
            QList<GluonObject*> parseGDL( const QUrl& fileUrl, QObject* parent = 0 );

            /**
             * Serialize a list of GluonObject instances into a GDL representation
             * @param   serializeThis   The list of GluonObject instances you wish to serialize
             * @return  The serialized objects
             */
            QString serializeGDL( QList<const GluonObject*> serializeThis );

            QString toGDL( const GluonObject* gluonObject, int indentLevel = 0 ) const;
            QString childrenToGDL( const GluonObject* gluonObject, int indentLevel = 0 ) const;
            QString propertiesToGDL( const GluonObject* gluonObject, int indentLevel = 0 ) const;

        private:
            friend class Singleton<GDLHandler>;

            GDLHandler();
            virtual ~GDLHandler();
            Q_DISABLE_COPY( GDLHandler );

            GluonObject* instantiateObject( QString className );
            GluonObject* createObject( QStringList objectStringList, QObject* parent );
            /**
             * Returns a list of QStringLists, where each QStringList is:
             * Index 0: The type of the object
             * Index 1: The object's name
             * Following indices: All the values in the order of definition, alternating between property names and values (in that order)
             * If any value begins with {, it is a new object
             */
            QList<QStringList> tokenizeObject( QString objectString );
    };
}

#endif  // GLUON_CORE_GDLHANDLER_H

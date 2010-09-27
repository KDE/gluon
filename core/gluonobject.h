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
#ifndef GLUON_CORE_GLUONOBJECT_H
#define GLUON_CORE_GLUONOBJECT_H

#include <QtCore/QObject>
#include <QtCore/QSharedData>
#include <QtCore/QList>
#include <QtCore/QUrl>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

#include "gluonobjectfactory.h"
#include "gluon_core_export.h"


Q_DECLARE_METATYPE(QList<QUrl>)

/**
 * Please insert this macro into the definition of your class when implementing a
 * GluonObject subclass. The following is the code as found in GluonObject itself:
\code
class GLUON_CORE_EXPORT GluonObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    GLUON_OBJECT(GluonCore::GluonObject);

    public:
        Q_INVOKABLE GluonObject(QObject * parent = 0);
\endcode
 *
 * \note Please make sure that you also add two Q_DECLARE_METATYPE declarations at
 * the end of your header as seen below (also a sample from GluonObject):
\code
Q_DECLARE_METATYPE(GluonCore::GluonObject)
Q_DECLARE_METATYPE(GluonCore::GluonObject*)
\endcode
 */
#define GLUON_OBJECT(CLASSNAME)\
    public:\
    virtual GluonCore::GluonObject* instantiate();\
    virtual GluonCore::GluonObject* fromVariant(const QVariant &wrappedObject);\
    virtual QVariant toVariant(GluonCore::GluonObject *wrapThis);\
    private:

namespace GluonCore
{
    class GameProject;
    class GluonObjectPrivate;
    class MetaInfo;

    /**
     * \brief Convenience-extended version of QObjects for use with Gluon
     *
     * The central object class for Gluon - it contains much convenience functionality
     * used throughout Gluon, specifically geared towards searching and the like.
     * It further extends QObject with extra functionality to help with certain specifics
     * for properties, that Qt's properties do not support, such as value borders and
     * steps for numerical values.
     *
     * <b>Subclassing</b>
     *
     * When implementing GluonObject subclasses in C++, please remember the following
     * items in your code:
     *
     * Definition (yourclassname.h):
\code
#include <gluonobject.h>

namespace YourNamespace
{
    class YourClassName : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT(YourNamespace::YourClassName);

        public:
            Q_INVOKABLE YourClassName(QObject *parent = 0);
            virtual ~YourClassName();

            // More functions here...

        private:

    }
}

Q_DECLARE_METATYPE(YourNamespace::YourClassName);
Q_DECLARE_METATYPE(YourNamespace::YourClassName*);
\endcode
     *
     * Implementation (yourclassname.cpp):
\code
#include "yourclassname.h"

REGISTER_OBJECT_TYPE(YourNamespace, YourClassName);

using YourNamespace;

YourClassName::YourClassName(QObject *parent)
    : GluonObject(parent)
{
}

YourClassName::~YourClassName()
{
}

// further implementation here...

#include "yourclassname.moc"
\endcode
     *
     * Please also ensure that all public functions are slots, as this will enable their
     * access from the QtScript based game code in GluonEngine based games.
     */
    class GLUON_CORE_EXPORT GluonObject : public QObject
    {
            Q_OBJECT
            /**
             * The local name of the object. Setting the name will sanitize it according to
             * the following rules:
             *
             *   - Names cannot contain the / symbol
             *   - Two objects on the same parent cannot have the same name
             *
             * To ensure the second rule, numbers are added until such time that the name becomes
             * unique (setting name would result in first attempting "name", then "name 1", then
             * "name 2" and so forth, until the name is unique).
             */
            Q_PROPERTY(QString name READ name WRITE setName)
            // There is deliberately no gameProject property
            GLUON_OBJECT(GluonCore::GluonObject);

        public:
            Q_INVOKABLE GluonObject(QObject * parent = 0);
            explicit GluonObject(const QString& name, QObject *parent = 0);
            GluonObject(const GluonObject& rt);
            virtual ~GluonObject();

            /**
             * Write a debug statement to the console and into the debug messages pane in Gluon Creator
             * when running a game from inside the tool.
             *
             * @param   debugText   The message you wish to write out
             */
            Q_INVOKABLE void debug(const QString& debugText) const;

            /**
             * Write a debug statement to the console and into the debug messages pane in Gluon Creator
             * when running a game from inside the tool.
             *
             * \param   debugText   The message you wish to write out
             * \param   arg         The argument of debugText. Ssee QString::arg() for more information.
             */
            Q_INVOKABLE void debug(const QString& debugText, const QString& arg) const;

            /**
             * Signal which is emitted whenever a debug statement is produced using the debug() function
             *
             * @param   debugText   The debug message test
             */
            Q_SIGNAL void showDebug(const QString& debugText) const;

            /**
             * Copy this object and all of its children, resursively.
             * It will be a child of the same GluonObject that the current object is a child of.
             *
             * @return A deep copy of the object and all its children
             */
            Q_INVOKABLE GluonObject * clone() const;
            /**
             * Copy this object and all of its children, recursively, and insert the cloned object
             * as a child of the passed GluonObject
             *
             * @return A deep copy of the object and all its children
             */
            Q_INVOKABLE GluonObject * clone(GluonObject* parentObject) const;

            /**
             * Get the object's sanitized name
             *
             * @return  The object's name
             */
            virtual QString name() const;
            /**
             * Set a new name for the object. See also the property description.
             *
             * @param   newName     The requested new name for this object
             */
            virtual void setName(const QString &newName);
            /**
             * The fully qualified name of the object, from the root and upwards.
             * The object name separator is / which means that an object named
             * AnObject which is child of the top level object AnotherObject is:
             * AnotherObject/AnObject
             */
            QString fullyQualifiedName() const;
            /**
             * A version of the fully qualified name of the object suitable for use
             * as a file name. Note that this is NOT the actual file name of any file
             * on the disk, it is only a string which is suitable for use as a file name
             *
             * @return  A version of the fully qualified object name suitable for a file name
             *
             * @see fullyQualifiedName()
             */
            QString fullyQualifiedFileName() const;

            /**
             * Used by GluonObjectFactory when requesting an object which supports a specific
             * mimetype. The default implementation returns an empty list.
             *
             * This is primarily useful for GluonEngine::Asset but other classes can potentially
             * use it as well.
             *
             * @return  A list of strings each describing a mimetype the class supports
             */
            virtual const QStringList supportedMimeTypes() const;

            /**
             * Use this to access functions on the GameProject instance associated
             * with this GluonObject.
             *
             * @return The instance of GameProject this GluonObject is associated with.
             * Note that it is returned as GluonObject so you will need to use a qobject_cast to cast it.
             * @see GameProject GameProject::findItemByName
             */
            GluonObject * gameProject() const;
            /**
             * Do not use this function unless you are absolutely sure what you
             * are doing!
             *
             * \note This should probably be private and make use of friend classes...
             *
             * @param newGameProject The GameProject instance this GluonObject can be found underneath
             */
            void setGameProject(GluonObject * newGameProject);

            /**
             * Get the Gluon meta info for this object. This function will create an instance
             * for the class if one does not exist.
             *
             * @return The meta information related to this object
             */
            Q_INVOKABLE MetaInfo* metaInfo();
            /**
             * Request information on whether the class contains MetaInfo. This function is needed
             * to ensure the ability to read metaInfo without creating one automatically.
             *
             * @return  True if a MetaInfo instance exists for the class
             */
            Q_INVOKABLE bool hasMetaInfo() const;

            /**
             * Do we need the parsing code in the GluonObject? Or can we separate this into a parser class?
             * We need to separate this into a parser class, imo. Can wait until post-alpha though. -ahiemstra
             */
            virtual QString toGDL(int indentLevel = 0) const;
            virtual QString childrenToGDL(int indentLevel = 0) const;
            virtual QString propertiesToGDL(int indentLevel = 0) const;

            virtual void setPropertyFromString(const QString &propertyName, const QString &propertyValue);
            virtual QString getStringFromProperty(const QString& propertyName, const QString& indentChars) const;

            virtual void sanitize();

            /*
            * QObject hierarchy helper functions.
            */

            /**
             * Attempt to locate an object by the specified qualified name, starting the search from
             * the object is called on. To search the full tree, for example for use with
             * fullyQualifiedName, call this function on the object returned by root()
             *
             * @param   qualifiedName   The path (with object names separated by the / symbol) to the object, relative to the object this function is called on
             * @return  The object if found, or null if not
             */
            Q_INVOKABLE GluonObject* findItemByName(QString qualifiedName);
            /**
             * Get the top-most GluonObject in the object hierarchy
             *
             * @return  The root of the GluonObject hierarchy
             */
            Q_INVOKABLE virtual GluonObject* root();

            /**
             * Add the passed GluonObject as a new child to this object. The function
             * will ensure that the name is correct
             *
             * @param   child   The new child
             *
             * @see name
             */
            virtual void addChild(GluonObject *child);
            /**
             * Remove the passed GluonObject from the list of children on this object.
             *
             * @param   child   The child you wish to remove
             * @return  True if the child was removed successfully, false if the child did not exist in this object
             */
            virtual bool removeChild(GluonObject *child);
            /**
             * Convenience function for getting a child at a specific index in the list of children
             *
             * @param   index   The index of the child you wish to fetch
             * @return  The child at that index, or null if the index is invalid
             */
            virtual GluonObject * child(int index) const;
            /**
             * Convenience function for fetching a child by a specified name
             *
             * @param   name    The name of the child you wish to fetch
             * @return  The child with the passed name, or null if no child exists by that name
             */
            virtual GluonObject * child(const QString& name) const;

        protected:
            /**
             * Convenience function which will find objects inside a passed GluonObject which
             * fit the also passed qualified name. The function is used internally by
             * findItemByName() but could well be useful for other things as well.
             *
             * @param   qualifiedName   The qualified name of the object you wish to locate
             * @param   object          The object to start the search at
             * @return  The object if found, or null if the object was not found
             */
            static GluonObject * findItemByNameInObject(QStringList qualifiedName, GluonCore::GluonObject* object);
            /**
             * This function is called by the clone function before handing the cloned object
             * back to the caller. If you have something special which needs to be done to each
             * child after adding, re-implement this function and perform those actions.
             */
            virtual void postCloneSanitize() {};

        private:
            void sanitizeReference(const QString& propName, const QString& propValue);

            QSharedDataPointer<GluonObjectPrivate> d;
    };
}

Q_DECLARE_METATYPE(GluonCore::GluonObject)
Q_DECLARE_METATYPE(GluonCore::GluonObject*)

#endif  // GLUON_CORE_GLUONOBJECT_H

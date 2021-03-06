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

#include "gluoncore_export.h"

#include "gluonobjectfactory.h"

#include <QtScript/QScriptValue>
#include <QtCore/QList>
#include <QtCore/QUrl>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

Q_DECLARE_METATYPE( QList<QUrl> )

/**
 * Please insert this macro into the definition of your class when implementing a
 * GluonObject subclass. The following is the code as found in GluonObject itself:
\code
class GLUONCORE_EXPORT GluonObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    GLUON_OBJECT(GluonCore::GluonObject)

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
    static QScriptValue objectToScriptValue( QScriptEngine* engine, CLASSNAME* const& in );\
    static void objectFromScriptValue( const QScriptValue& object, CLASSNAME*& out );\
    virtual void registerOnScriptEngine(QScriptEngine* engine) const;\
    private:

namespace GDL
{
    class ObjectTreeBuilder;
    class Writer;
}

namespace GluonCore
{
    class MetaInfo;
    enum DebugType {
        DebugDefault,
        DebugInfo,
        DebugVerbose,
        DebugWarning,
        DebugError,
        DebugFatal
    };

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
        GLUON_OBJECT(YourNamespace::YourClassName)

        public:
            Q_INVOKABLE YourClassName(QObject *parent = 0);
            virtual ~YourClassName();

            // More functions here...

        private:

    }
    }

    Q_DECLARE_METATYPE(YourNamespace::YourClassName)
    Q_DECLARE_METATYPE(YourNamespace::YourClassName*)
    \endcode
     *
     * Implementation (yourclassname.cpp):
    \code
    #include "yourclassname.h"

    REGISTER_OBJECTTYPE(YourNamespace, YourClassName);

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
     * When implementing such classes, please also ensure the following:
     *
     * - Mark all public functions which should be available from game code as a slot, or with the
     *   Q_INVOKABLE macro,
     * - Use the fully qualified type name for all properties (such as GluonInput::Mouse::MouseButton
     *   instead of just MouseButton or Mouse::MouseButton)
     */
    class GLUONCORE_EXPORT GluonObject : public QObject
    {
            Q_OBJECT
            GLUON_OBJECT( GluonCore::GluonObject )

            /**
             * The local name of the object. Setting the name will sanitize it according to
             * the following rules:
             *
             *   - Names cannot contain the / symbol, and will be simplified (all whitespace
             *     turned into a single space, and no starting and trailing spaces)
             *   - Two objects on the same parent cannot have the same name
             *
             * To ensure the second rule, numbers are added until such time that the name becomes
             * unique (setting name would result in first attempting "name", then "name 1", then
             * "name 2" and so forth, until the name is unique).
             *
             * <strong>Accessing objects in scripts</strong>
             *
             * When accessing the object in scripts, the object name is sanitized further by
             * allowing only alphanumerical symbols and underscores, with all other parts of the
             * name removed. This means that, for example, an object in a hierarchy which looks like
             * this:
             *
             * Some Object/A Child Object/Some Object - with a little comment
             *
             * would be addressed like so:
             *
             * SomeObject.AChildObject.SomeObjectwithalittlecomment
             */
            Q_PROPERTY( QString name READ name WRITE setName )
            // There is deliberately no gameProject property

        public:
            Q_INVOKABLE GluonObject( QObject* parent = 0 );
            explicit GluonObject( const QString& name, QObject* parent = 0 );
            virtual ~GluonObject();

            /**
             * Take a name in the format accepted by the GluonObject name property, and transform
             * it into the format accepted by the objectName property. This function is useful for
             * when you wish to search the hierarchy for objects by name.
             *
             * @param   name    The GluonObject name you wish transformed
             * @return  The sanitized name
             * @see name
             */
            Q_INVOKABLE static QString nameToObjectName( const QString& name );

            /**
             * Copy this object and all of its children, recursively.
             * It will be a child of the same GluonObject that the current object is a child of.
             *
             * @return A deep copy of the object and all its children
             */
            Q_INVOKABLE GluonObject* clone() const;

            /**
             * Copy this object and all of its children, recursively, and insert the cloned object
             * as a child of the passed GluonObject
             *
             * @return A deep copy of the object and all its children
             */
            Q_INVOKABLE GluonObject* clone( GluonObject* parentObject ) const;

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
            virtual void setName( const QString& newName );

            /**
             * Emitted when the name of the object changes
             */
            Q_SIGNAL void nameChanged( const QString& oldName, const QString& newName );

            /**
             * The fully qualified name of the object, from the root and upwards.
             * The object name separator is "/" which means that an object named
             * AnObject which is child of the top level object AnotherObject is:
             * AnotherObject/AnObject
             */
            QString fullyQualifiedName() const;

            /**
             * The qualified name of the object, from the local root and upwards,
             * not including the name of the local root object.
             * @see fullyQualifiedName
             */
            QString qualifiedName( const GluonObject* localRoot ) const;

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
            GluonObject* gameProject() const;

            /**
             * Do not use this function unless you are absolutely sure what you
             * are doing!
             *
             * \note This should probably be private and make use of friend classes...
             *
             * @param newGameProject The GameProject instance this GluonObject can be found underneath
             */
            void setGameProject( GluonObject* newGameProject );

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

            /*
            * QObject hierarchy helper functions.
            */

            /**
             * Attempt to locate an object by the specified qualified name, starting the search from
             * the object is called on. To search the full tree, for example for use with
             * fullyQualifiedName, use the findGlobalItemByName function.
             *
             * @param   qualifiedName   The path (with object names separated by the "/" symbol) to the object, relative to the object this function is called on
             * @return  The object if found, or null if not
             * @see findGlobalItemByName
             */
            Q_INVOKABLE GluonObject* findItemByName( QString qualifiedName );

            /**
             * Attempt to locate an object by the specified fully qualified name. If you don't have the
             * fully qualified name, use findItemByName.
             *
             * @param fullyQualifiedName The path (with object names separated by the "/" symbol) to the object, starting with the root object
             * @return The object if found, or null if not
             * @see findItemByName
             */
            Q_INVOKABLE GluonObject* findGlobalItemByName( QString fullyQualifiedName );

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
            virtual void addChild( GluonObject* child );

            /**
             * Add the passed GluonObject as a new child to this object, at the position requested.
             * If position is larger than the number of children, the new child will be appended
             * to the object. The function will ensure the name is correct.
             *
             * \note The internal logic uses removeChild(GluonObject*) and addChild(GluonObject*)
             *
             * @param   child     The new child
             * @param   position  The position at which the new child will be added
             *
             * @see name
             */
            virtual void addChildAt( GluonObject* child, int position );

            /**
             * Remove the passed GluonObject from the list of children on this object.
             *
             * @param   child   The child you wish to remove
             * @return  True if the child was removed successfully, false if the child did not exist in this object
             */
            virtual bool removeChild( GluonObject* child );

            /**
             * Convenience function for getting a child at a specific index in the list of children
             *
             * @param   index   The index of the child you wish to fetch
             * @return  The child at that index, or null if the index is invalid
             */
            virtual GluonObject* child( int index ) const;

            /**
             * Convenience function for fetching a child by a specified name
             *
             * @param   name    The name of the child you wish to fetch
             * @return  The child with the passed name, or null if no child exists by that name
             */
            virtual GluonObject* child( const QString& name ) const;

            /**
             * Fetches all the children of a given type from a GluonObject,
             * searching in the entire hierarchy.
             */
            template<class T> QList<T*> findItemsByType() const
            {
                QList<T*> items;

                foreach( QObject * child, children() )
                {
                    T* item = qobject_cast<T*>( child );
                    if( item )
                    {
                        items << item;
                        items << item->template findItemsByType<T>();
                    }
                    else
                    {
                        GluonObject* obj = qobject_cast<GluonObject*>( child );
                        if( obj )
                        {
                            items << obj->template findItemsByType<T>();
                        }
                    }
                }

                return items;
            };

            /**
             * Handle a message from the MessageHandler. Note that this will only
             * be called after MessageHandler::subscribe() has been called.
             *
             * \see MessageHandler
             *
             * \param message The message that was sent.
             */
            virtual void handleMessage( const QString& message );

            /**
             * Find out whether this object has a certain property. This includes
             * both static and dynamic properties.
             *
             * \return true if the property exists on this object, false if not.
             */
            bool hasProperty( const QString& property );

            /**
             * Get the type of a property.
             *
             * For static properties, this will return the QMetaType::Type of the property
             * as returned by QMetaProperty.
             *
             * For dynamic properties, this will return the QMetaType::Type of the QVariant
             * value returned by QObject::property(), unless there is a dynamic property called
             * {prefix}{property}_type (where prefix is the internal property prefix), in which
             * case the returned type is that set in the type property.
             *
             * \param property The name of the property to get the type of.
             * \return a QMetaType::Type value of the property tCype, or QMetaType::UnknownType if
             * the property does not exist.
             */
            int propertyType( const QString& property );

            /**
             * The prefix used for internal dynamic properties.
             *
             * Dynamic properties can be added by the platform where necessary. Any property that is
             * prefix with the internal property prefix is considered an internal property and is not
             * meant to be modified outside of the code that set it. Internal properties will not be
             * serialized and will be excluded from display in Gluon Creator's property editor.
             */
            static const QByteArray internalPropertyPrefix;

        protected:
            /**
             * findItemByName uses this function to recursively search in its children
             * for the given object. The path to the object is given as a list.
             *
             * @param   qualifiedName   The qualified name of the object you wish to locate
             * @return  The object if found, or null if the object was not found
             */
            virtual GluonObject* findItemByNameInternal( QStringList qualifiedName );

            /**
             * This function is called by the clone function before handing the cloned object
             * back to the caller. If you have something special which needs to be done to each
             * child after adding, re-implement this function and perform those actions.
             */
            virtual void postCloneSanitize() {};

            /**
             * This function is called when the MetaInfo is created and allows setting the
             * properties of the MetaInfo object.
             *
             * \param info The MetaInfo that was just created.
             */
            virtual void populateMetaInfo( MetaInfo* /* info */ ) { }

            /**
             * Should the children of this object be serialized?
             *
             * Override this method to prevent the GDL serializer from serializing children of
             * this object, in case you want to handle them in a special way.
             */
            virtual bool shouldSerializeChildren() const;

            /**
             * Cleanup the object after parsing it from GDL.
             *
             * Override this method to clean up after the object has been created by the parser.
             */
            virtual void sanitize();

            friend class GDL::ObjectTreeBuilder;
            friend class GDL::Writer;

        private:
            Q_DISABLE_COPY( GluonObject )

            class Private;
            Private* const d;
    };

    typedef QList< GluonObject* > GluonObjectList;
}

Q_DECLARE_METATYPE( GluonCore::GluonObject* )
Q_DECLARE_METATYPE( GluonCore::DebugType )

#endif  // GLUON_CORE_GLUONOBJECT_H

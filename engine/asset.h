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

#ifndef GLUON_ENGINE_ASSET_H
#define GLUON_ENGINE_ASSET_H

#include "gluon_engine_export.h"

#include <core/gluonobject.h>
#include <core/referencecounter.h>

#include <QtCore/QtPlugin>
#include <QtCore/QUrl>
#include <QtCore/QMimeData>
#include <QtGui/QIcon>

// class QAction;
class QMimeData;

namespace GluonEngine
{
    class AssetPrivate;
    class AssetAction;

    /**
     * \brief Representation of a template for a specific GluonEngine::Asset
     *
     * A simple data container class for template information for GluonEngine::Asset
     *
     * Note: To see which Asset the template is referring to, the parent() function
     * will be pointing to an instance of that class.
     */
    class GLUON_ENGINE_EXPORT AssetTemplate : public QObject
    {
            Q_OBJECT
        public:
            AssetTemplate( QString name, QString filename, QString pluginname, QObject* parent = 0 )
                : QObject( parent )
                , name( name )
                , filename( filename )
                , pluginname( pluginname )
            { }
            virtual ~AssetTemplate() {};

            /**
            * The name which the newly created asset object will be given
            */
            QString name;

            /**
            * The filename of the template, as found inside the template directory for
            * this asset (for example /usr/share/gluon/template/assetclassname/filename)
            */
            QString filename;

            /**
             * The name of the plugin (that is, the subdir inside which the template file is found)
             */
            QString pluginname;
    };

    /**
     * \brief The base class on which all Asset handlers are constructed
     *
     * The Asset class is a fat interface used to allow file access to GluonEngine based
     * games without allowing direct access to the file system.
     *
     * Assets are designed to be plugins, use the GLUON_ASSET_PLUGIN( metadatafile ) to
     * declare them as such. The metadata file is a JSON file as used by the Qt plugin
     * system. The following data can be contained in the JSON file:
     *
     * <code>
     * {
     *    "name": The name of the asset.
     *    "icon": The icon used for the asset.
     *    "category": The category of the asset.
     *    "mimeTypes": An array of strings with supported mime types.
     *    "templates": An array of objects describing the templates to use.
     *          Each object is expected to have a name and template property.
     *    "actions": An array of objects describing the actions that can be
     *          performed on this asset. Each object is expected to have a name
     *          and method property, where method should be the name of a slot on the asset.
     * }
     * </code>
     *
     * Note that if you override supportedMimeTypes() or actions() and return
     * a non-empty list those lists will be used instead of the mime data from the
     * plugin.
     */
    class GLUON_ENGINE_EXPORT Asset : public GluonCore::GluonObject, public GluonCore::ReferenceCounter
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::Asset )
            /**
             * The file name of the represented file, relative to the GameProject's position
             * on the file system. Importantly, this cannot contain parent definitions (meaning
             * no .. in the path string), and as this essentially sandboxes GluonEngine based
             * games.
             */
            Q_PROPERTY( QString file READ file WRITE setFile DESIGNABLE false )

        public:
            Q_INVOKABLE Asset( QObject* parent = 0 );
            virtual ~Asset();

            void sanitize();

            /**
             * An extension on the GluonCore::GluonObject::setName function which changes the
             * file name of the Asset when setting a new name for the Asset.
             *
             * \note As always, be aware that the requested name is not always the name which
             * is set, as two objects with the same parent cannot have the same name.
             *
             * @param   newName The requested new name for the asset
             *
             * @see file, GluonCore::GluonObject::name
             */
            virtual void setName( const QString& newName );

            virtual void setFile( const QString& newFile );
            virtual QString file() const;

            /**
             * Return the absolute path of this asset's file.
             *
             * Note that this should never be called from a script.
             *
             * @return The absolute path of this asset's file.
             */
            virtual QUrl absolutePath() const;

//             /**
//              * An icon to represent the asset. Think of it as a thumbnail representation
//              * of the contents of the asset. The default implementation returns a null icon
//              */
//             virtual QIcon icon() const;

//             /**
//              * The templates provided by the asset. The default
//              * implementation returns no templates, as many assets will not
//              * be able to provide templates.
//              */
//             virtual const QList<AssetTemplate*> templates();

            /**
             * Retrieve a list of actions relating to the current asset.
             *
             * \return A QList of QActions that can be shown in pop-up menus and
             * other places.
             */
            virtual QList<AssetAction*> actions();

            /**
             * This function should return a QMimeType containing the data the asset
             * represents. This is done to avoid having varying methods of accessing
             * the data represented by various assets. If more than one data accessor
             * function is needed, more can of course be constructed, but data() should
             * always return the primary data for the asset.
             */
            virtual const QMimeData* data() const;

            /**
             * This function should return a QMimeType containing a reference to the
             * asset itself. The data should provide a mimedata instance with the
             * mimetype format represented by the asset, and a bytestream containing
             * the fully qualified name of the asset. The default implementation returns
             * one which contains the mimetype application/gluon.engine.className, but
             * you should reimplement it and provide one which gives the actual mimetype
             * represented by the asset.
             * @return As described above
             * @see fullyQualifiedName
             */
            virtual QMimeData* dragData() const;

            /**
             * The specialization of toGDL on the Asset class does not recurse.
             * This allows Assets to handle their own children in a flexible
             * manner, without polluting the GDL with that information.
             */
            virtual bool shouldSerializeChildren( ) const;

            /**
             * Convenience function to test whether the file has been loaded or not.
             */
            virtual bool isLoaded() const;

            virtual void reload();

            /**
             * Filter the fully qualified name of an object.
             *
             * \return A URL that can be used for saving files.
             */
            static QString fullyQualifiedFileName( GluonCore::GluonObject* obj, const QString& extension = QString() );

        public Q_SLOTS:
            /**
             * Load the data of this Asset into memory.
             */
            virtual void load();

            /**
             * Unload the data of this Asset from memory.
             */
            virtual void unload();

        Q_SIGNALS:
            /**
             * This signal is fired when ever the data represented by the Asset instance
             * changes, and should be an indication that the data should be updated.
             *
             * @see data()
             */
            void dataChanged();

        protected:
            QMimeData* mimeData() const;
            void setLoaded( bool loaded );

            /**
             * Reimplemented from GluonCore::GluonObject::findItemByNameInternal
             */
            virtual GluonCore::GluonObject* findItemByNameInternal( QStringList qualifiedName );

        private:
            AssetPrivate* d;
    };
}

Q_DECLARE_INTERFACE( GluonEngine::Asset, "org.gluon.engine.asset/1.0" )
Q_DECLARE_METATYPE( GluonEngine::Asset* )

#define GLUON_ASSET_PLUGIN(_file)\
    Q_PLUGIN_METADATA(IID "org.gluon.engine.asset/1.0" FILE #_file)

#endif  // GLUON_ENGINE_ASSET_H

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

#ifndef GLUON_ENGINE_GAMEPROJECT_H
#define GLUON_ENGINE_GAMEPROJECT_H

#include "gluon_engine_export.h"
#include "scene.h"

#include <core/gluonobject.h>

#include <QtCore/QSharedData>
#include <QtCore/QUrl>
#include <graphics/texture.h>
#include "assets/graphics/texture/textureasset.h"

namespace GluonEngine
{
    const QString projectSuffix(".gluon");
    const QString projectFilename("game.gluonproject");
    const QString projectMetainfo("game.gluonmeta");
    const QString projectIcon("game.png");
    const QString projectWinIcon("game.ico");
    const QString projectScreenshot("screenshot.png");

    class GameProjectPrivate;

    /**
     * The GameProject class describes and contains a complete game project,
     * and all the meta information that goes with it, making it into a
     * complete game (minus engine, which is Gluon::Game and all the
     * Gluon::Component subclasses). As such it is the top level of the
     * GameObject hierarchy.
     *
     * The project's children (all assets, gameobjects and prefabs in the
     * project) are all found in the QObject hierarchy - they are simply
     * anchored by the QObject parent/child system.
     *
     * \note To find out which is the current scene in a game, use Game::currentScene
     *
     * <strong>The Gluon Game Bundle</strong>
     *
     * The structore of a game project as found on the disk is as follows:
     * - (gamename).gluon/ - This is a directory. Think of it as a bundle (NeXTStep style)
     *   - Assets/ - contains all the assets in a game
     *   - Cache/ - contains a number of directories, one for each asset which requires a data cache
     *   - Scenes/ - contains a file for each scene, each named (scenename).gluonscene
     *   - game.gluonproject
     *   - game.gluonmeta
     *   - screenshot.png
     *   - game.png - a 128x128 icon
     *   - game.ico - a Windows format icon file
     *   - .directory
     *   - desktop.ini
     *   - .ds_store -
     *
     * Naming conventions for the contents of the Assets and Scenes directories:
     *
     * - Filter all non-alphanumeric characters. (in short, everything not allowed in a javascript
     *   object name)
     * - All names are lower-cased
     *
     * The contents of the Cache directory should follow the following guidelines:
     *
     * - This directory contains a number of further directories, named for each asset which
     *   requires a cache
     * - The contents of each subdirectory are controlled by the asset (that is, the format is
     *   undefined), but for those creating assets it would be wise to follow the guidelines for
     *   Asset and Scene file names, to avoid problems with various operating systems.
     * - The contents will be re-generated when required, so the contents can be deleted if you
     *   should so wish, but this will increase loading times on the first access. However, if the
     *   generated files are very large, the cache for that item may be too big to distribute. Then
     *   it is good to know that the item can be safely deleted before publishing.
     */
    class GLUON_ENGINE_EXPORT GameProject : public GluonCore::GluonObject
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::GameProject )

            /**
             * A long description of the game. This can contain any string data, but
             * you should attempt to use simplified HTML syntax for markup.
             *
             * \note This should be extended when we have more knowledge about where this will be used (GamingFreedom.org and clients)
             */
            Q_PROPERTY( QString description READ description WRITE setDescription )
            /**
             * This will likely be the GamingFreedom.org page, but other pages might be
             * needed as well, for commercial or other ventures who have their own websites:
             * So, full URL to the homepage of the game.
             */
            Q_PROPERTY( QUrl homepage READ homepage WRITE setHomepage )
            /**
             * A list of URLs for images, videos and other various interesting media (for
             * screenshots, gameplay videos, promo trailers, documentation PDFs...)
             */
            Q_PROPERTY( QList<QUrl> mediaInfo READ mediaInfo WRITE setMediaInfo )

            /**
             * The Scene in which the game should begin. This is likely going to be an intro
             * scene or a menu but can also be directly into gameplay by pointing to a scene
             * which contains the game.
             */
            Q_PROPERTY( GluonEngine::Scene* entryPoint READ entryPoint WRITE setEntryPoint )

            /**
             * The icon used to represent the game both on disk, on the distribution site, and in
             * the players which show icons for the games.
             */
            Q_PROPERTY( GluonEngine::TextureAsset* icon READ icon WRITE setIcon )

            /**
             * A screenshot to represent the game, shown in the various players, and on the
             * distribution site
             */
            Q_PROPERTY( GluonEngine::TextureAsset* screenshot READ screenshot WRITE setScreenshot )

        public:
            Q_INVOKABLE GameProject( QObject* parent = 0 );
            GameProject( const GameProject& other, QObject* parent = 0 );
            ~GameProject();

            virtual void addChild( GluonObject* child );
            virtual bool removeChild( GluonObject* child );

            bool saveToFile() const;
            bool loadFromFile();
            bool loadFromFile( QUrl fileUrl );
            bool loadFromFile( QString fileName );

            /******************************************************************
             * Property Getter-setters
             *****************************************************************/
            QString description() const;
            void setDescription( QString newDescription );

            QUrl homepage() const;
            void setHomepage( QUrl newHomepage );

            QList<QUrl> mediaInfo() const;
            void setMediaInfo( QList<QUrl> newMediaInfo );

            QUrl filename() const;
            void setFilename( QUrl newFilename );
            void setFilename( QString fileName );

            QUrl dirname() const;
            void setDirname( QUrl newDirname );
            void setDirname( QString dirName );

            Scene* entryPoint() const;
            void setEntryPoint( Scene* newEntryPoint );

            GluonEngine::TextureAsset* icon() const;
            void setIcon( GluonEngine::TextureAsset* newIcon );

            GluonEngine::TextureAsset* screenshot() const;
            void setScreenshot( GluonEngine::TextureAsset* newScreenshot );

        private:
            QSharedDataPointer<GameProjectPrivate> d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::GameProject )
Q_DECLARE_METATYPE( GluonEngine::GameProject* )

#endif  // GLUON_ENGINE_GAMEPROJECT_H

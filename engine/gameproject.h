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

namespace GluonEngine
{
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
     */
    class GLUON_ENGINE_EXPORT GameProject : public GluonCore::GluonObject
    {
            Q_OBJECT;
            GLUON_OBJECT( GluonCore::GameProject );

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
             * The filename of the GameProject, meaning the name of the project file on
             * disk, relative to the project directory.
             */
            Q_PROPERTY( QUrl filename READ filename )

            /**
             * The Scene in which the game should begin. This is likely going to be an intro
             * scene or a menu but can also be directly into gameplay by pointing to a scene
             * which contains the game.
             */
            Q_PROPERTY( GluonEngine::Scene* entryPoint READ entryPoint WRITE setEntryPoint )

        public:
            Q_INVOKABLE GameProject( QObject* parent = 0 );
            GameProject( const GameProject& other, QObject* parent = 0 );
            ~GameProject();

            virtual void addChild( GluonObject* child );
            virtual bool removeChild( GluonObject* child );

            bool saveToFile() const;
            bool loadFromFile();
            bool loadFromFile( QUrl fileUrl );

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

            Scene* entryPoint() const;
            void setEntryPoint( Scene* newEntryPoint );

        private:
            QSharedDataPointer<GameProjectPrivate> d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::GameProject )
Q_DECLARE_METATYPE( GluonEngine::GameProject* )

#endif  // GLUON_ENGINE_GAMEPROJECT_H

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright (C) 2010-2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_PLAYER_SERVICEPROVIDER_H
#define GLUON_PLAYER_SERVICEPROVIDER_H

#include "lib/gluon_player_export.h"

#include <core/singleton.h>

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{
    class GameDetailListJob;
    class CommentListJob;
    class GameContentJob;
    class RatingJob;

    /**
     * \brief Provides Open Collaboration Services
     *
     * OcsProvider provides access to OCS functions on an OCS
     * compliant remote server.
     * \note Its <b>important</b> to call init() before attempting
     * to use the class
     */
    class GLUON_PLAYER_EXPORT ServiceProvider : public GluonCore::Singleton<ServiceProvider>
    {
        Q_OBJECT
        Q_PROPERTY( bool isReady READ isReady )
        Q_PROPERTY( bool isLoggedIn READ isLoggedIn )
        Q_PROPERTY( bool hasCredentials READ hasCredentials )
        Q_PROPERTY( QString username READ username )
        Q_PROPERTY( QString password READ password )
        GLUON_SINGLETON( ServiceProvider )

        public:
            /**
             * Check if the OCS Provider is ready to perform actions. To initialize,
             * call init()
             *
             * @return  true if ready, false if not
             */
            Q_INVOKABLE bool isReady() const;

            /**
             * Fetch comments from the OCS compliant service
             *
             * @param   id      ID of the content
             * @param   page    page number of the desired page
             * @param   pageSize        number of comments per page
             *
             * @return  OcsCommentsProvider object which the caller must
             * monitor to find out the result of the operation
             */
            Q_INVOKABLE CommentListJob* fetchCommentList(const QString& id, int page, int pageSize);

            /**
             * Upload a comment to the OCS compliant service
             *
             * @param   id      ID of the comment
             * @param   parentId        ID of the parent comment, leave blank if none
             * @param   subject Subject of the comment
             * @param   message The comment message (body)
             *
             * @return  OcsCommentsProvider object which the caller must
             * monitor to find out the result of the operation
             */
            Q_INVOKABLE CommentListJob* uploadComment(const QString& id, const QString& parentId,
                    const QString& subject, const QString& message);

            /**
             * Execute a login. Connect to the signal loggedIn() and loginFailed() to know the result.
             * @param   username        The username to be used
             * @param   password        The password to be used
             *
             * @return true if login was successfully initiated, false otherwise.
             */
            Q_INVOKABLE bool login(const QString& username, const QString& password);

            /**
             * Execute a logout. Connect to the signal loggedOut() and logoutFailed() to know the result.
             *
             * @return true if logout was successfully initiated, false otherwise.
             */
            Q_INVOKABLE bool logout();

            /**
             * Check if we are logged in
             *
             * @return true if logged in, false otherwise
             */
            bool isLoggedIn() const;

            /**
             * Check if saved credentials are available
             *
             * @return true if credentials are available
             */
            bool hasCredentials() const;

            /**
             * Retrieve the username
             *
             * @return a QString containing the username, empty string if not available
             */
            QString username() const;

            /**
             * Retrieve the password
             *
             * @return a QString containing the password, empty string if not available
             */
            QString password() const;

            /**
             * Fetch a list of games available on the OCS server
             * @return a OcsGameDetailsProvider object which the caller must
             * monitor to find out the result of the operation
             */
            GameDetailListJob *fetchGames();

            /**
             * Download the game with ID id
             *
             * @param id ID of the game
             * 
             * @return a GameContentTransfer object which the caller must
             * monitor to find out the result of the operation
             */
            GameContentJob *downloadGame(const QString &id);

            /**
             * Upload a game with ID
             *
             * @param id ID of the game
             * @param path Path of the file to upload
             * 
             * @return a GameContentTransfer object which the caller must
             * monitor to find out the result of the operation
             */
            GameContentJob *uploadGame(const QString &id, const QString &path);

            /**
             * Rate a game having ID with a rating from 0 to 100
             *
             * @param id ID of the game
             * @param rating Rating value between 0 to 100
             */
            RatingJob *setRating(const QString &id, uint rate);

        private Q_SLOTS:
            void providersUpdated();
            void checkLoginResult (Attica::BaseJob* baseJob);
            void loadCredentials();
            void doLogin();
            void doLogout();

        public Q_SLOTS:
            /** Call to initialize the OCS Provider 
             */
            void init();

        Q_SIGNALS:
            /** Signal which is emitted when the OCS Provider is initialized
            */
            void initializeFinished();

            /** Signal which is emitted if the OCS Provider failed to initialize
            */
            void initializeFailed();

            /** Signal which is emitted if the login is complete
            */
            void loginFinished();

            /** Signal which is emitted when the login failed
            */
            void loginFailed();

            void gameDetailListFetchStarting();
            void commentListFetchStarting();
            void commentListUploadStarting();
            void gameContentDownloadStarting();
            void gameContentUploadStarting();
            void ratingUploadStarting();

        private:
            ~ServiceProvider();

            class Private;
            Private* const d;
    };
}

#endif  // GLUON_PLAYER_SERVICEPROVIDER_H

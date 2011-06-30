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

#ifndef GLUONPLAYER_OCSPROVIDER_H
#define GLUONPLAYER_OCSPROVIDER_H

#include "lib/gluon_player_export.h"

#include <core/singleton.h>

namespace Attica
{
class Provider;
class BaseJob;
}

namespace GluonPlayer
{

class OcsGameDetailsProvider;
class OcsCommentsProvider;
class OcsGameDownloadProvider;
class OcsGameUploadProvider;
class OcsRatingProvider;

/**
 * \brief Provides Open Collaboration Services
 *
 * OcsProvider provides access to OCS functions on an OCS
 * compliant remote server.
 * \note Its <b>important</b> to call init() before attempting
 * to use the class
 */
class GLUON_PLAYER_EXPORT OcsProvider : public GluonCore::Singleton<OcsProvider>
{
    Q_OBJECT
    GLUON_SINGLETON( OcsProvider )
    Q_PROPERTY (bool isReady READ isReady)
    Q_PROPERTY (bool isLoggedIn READ isLoggedIn)
    Q_PROPERTY (bool hasCredentials READ hasCredentials)
    Q_PROPERTY (QString username READ username)
    Q_PROPERTY (QString password READ password)

public:
    /**
     * use to check if the OCS Provider is ready to perform actions. To initialize,
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
    Q_INVOKABLE OcsCommentsProvider* fetchComments (const QString& id, int page, int pageSize);

    /**
     * Uploads a comment to the OCS compliant service
     *
     * @param   id      ID of the comment
     * @param   parentId        ID of the parent comment, leave blank if none
     * @param   subject Subject of the comment
     * @param   message The comment message (body)
     *
     * @return  OcsCommentsProvider object which the caller must
     * monitor to find out the result of the operation
     */
    Q_INVOKABLE OcsCommentsProvider* uploadComment (const QString& id, const QString& parentId,
                                                    const QString& subject, const QString& message);
    /**
     * use to perform a login. Connect to the signal loggedIn() and loginFailed() to know the result.
     * @param   username        The username to be used
     * @param   password        The password to be used
     * @return true if login was successfully initiated, false otherwise.
     */
    Q_INVOKABLE bool login (const QString& username, const QString& password);

    /**
     * use to perform a logout. Connect to the signal loggedOut() and logoutFailed() to know the result.
     * @return true if logout was successfully initiated, false otherwise.
     */
    Q_INVOKABLE bool logout();

    /**
     * use to check if we are logged in
     * @return true if logged in, false otherwise
     */
    bool isLoggedIn() const;

    /**
     * use to check if saved credentials are available
     * @return true if credentials are available
     */
    bool hasCredentials() const;

    /**
     * use to retrieve the username
     * @return a QString containing the username, empty string if not available
     */
    QString username() const;

    /**
     * use to retrieve the password
     * @return a QString containing the password, empty string if not available
     */
    QString password() const;

    /**
     * Use to fetch a list of games available on the OCS server
     * @return a OcsGameDetailsProvider object which the caller must
     * monitor to find out the result of the operation
     */
    OcsGameDetailsProvider *fetchGames();

    /**
     * Use to download the game with ID id
     *
     * @param id ID of the game
     * 
     * @return a OcsGameDownloadProvider object which the caller must
     * monitor to find out the result of the operation
     */
    OcsGameDownloadProvider *downloadGame(const QString &id);

    /**
     * Use to upload a game with ID
     *
     * @param id ID of the game
     * @param path Path of the file to upload
     * 
     * @return a OcsGameUploadProvider object which the caller must
     * monitor to find out the result of the operation
     */
    OcsGameUploadProvider *uploadGame(const QString &id, const QString &path);

    /**
     * Rate a game having ID with a rating from 0 to 100
     *
     * @param id ID of the game
     * @param rating Rating value between 0 to 100
     */
    OcsRatingProvider *setRating(const QString &id, uint rating);

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
    /** signal which is emitted if the OCS Provider failed to initialize
     */
    void failedToInitialize();

    /** signal which is emitted when the OCS Provider is initialized
     */
    void providerInitialized();

    /** signal which is emitted if the login is complete
     */
    void loggedIn();

    /** signal which is emitted when the login failed
     */
    void loginFailed();

private:
    ~OcsProvider();

    class Private;
    Private* const d;
};

}

#endif  //GLUONPLAYER_OCSPROVIDER_H

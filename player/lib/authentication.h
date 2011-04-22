/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright (C) 2010-2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "gluon_player_export.h"

#include <core/singleton.h>

#include <attica/postjob.h>

namespace Attica
{
    class BaseJob;
    class PostJob;
}

namespace GluonPlayer
{
    /**
     * \brief Maintains authentication information for a Gluon Player
     *
     * This singleton maintains authentication credentials to access the online
     * OCS server and provides a way to Gluon Player implementations to login, save credentials,
     * load credentials etc.
     *
     */
    class GLUON_PLAYER_EXPORT Authentication : public GluonCore::Singleton<Authentication>
    {
            Q_OBJECT

        public:
            /**
             * function to initialize the Authentication module. Must be called before
             * using the library
             */
            void init();
            /**
             * returns if the library is initialized and ready to use
             */
            bool isInitialized();
            /**
             * use to perform a login. Connect to the signal loggedIn() and loginFailed() to know the result.
             * @param   username        The username to be used
             * @param   password        The password to be used
             * @return true if login was successfully initiated, false otherwise.
             */
            Q_INVOKABLE bool login( const QString& username, const QString& password );
            /**
             * use to perform a logout. Connect to the signal loggedOut() and logoutFailed() to know the result.
             * @return true if logout was successfully initiated, false otherwise.
             */
            Q_INVOKABLE bool logout( );
            /**
             * use to check if we are logged in
             * @return true if logged in, false otherwise
             */
            bool isLoggedIn();
            /**
             * use to check if saved credentials are available
             * @return true if credentials are available
             */
            bool hasCredentials();
            /**
             * use to retrieve the username
             * @return a QString containing the username, empty string if not available
             */
            QString username();
            /**
             * use to retrieve the password
             * @return a QString containing the password, empty string if not available
             */
            QString password();

        protected slots:
            void finishInit();
            void checkLoginResult( Attica::BaseJob* );

            void onRegisterClicked( const QString& username, const QString& password, const QString& mail, const QString& firstName, const QString& lastName );
            void onRegisterAccountFinished( Attica::BaseJob* job );

        signals:
            /** signal which is emitted when the initialization is complete
             */
            void initialized();
            /** signal which is emitted if the initialization failed
             */
            void initFailed();
            /** signal which is emitted if the new account is registered
             */
            void registered();
            /** signal which is emitted if the login is complete
             */
            void loggedIn();
            /** signal which is emitted if the logout is complete
             */
            void loggedOut();
            /** signal which is emitted when the login failed
             */
            void loginFailed();
            /** signal which is emitted when the login save credentials failed
             */
            void loginSaveCredentialsFailed();
            /** signal which is emitted when the logout failed
             */
            void logoutFailed();
            /** signal which is emitted when the registration failed
             */
            void registrationFailed();

        private:
            friend class GluonCore::Singleton<Authentication>;
            Authentication();
            ~Authentication();
            Q_DISABLE_COPY( Authentication )

            void showRegisterError( const Attica::Metadata& );

            bool m_initialized;
            bool m_loggedIn;
            QString m_username;
            QString m_password;
            Attica::PostJob* m_registerJob;
            Attica::PostJob* m_checkLoginJob;
            Attica::PostJob* m_checkLogoutJob;
    };
}

#endif // AUTHENTICATION_H

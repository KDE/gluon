#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <core/singleton.h>
#include "gluon_player_export.h"

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
             * use to perform a login. Connect to the signal loggedIn() and loginFailed() to know result.
             * @param   username        The username to be used
             * @param   password        The password to be used
             * @return true if login was successfully initiated, false otherwise.
             */
            bool login( const QString& username, const QString& password );
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

        private:
            friend class GluonCore::Singleton<Authentication>;
            Authentication();
            ~Authentication();
            Q_DISABLE_COPY( Authentication )

            bool m_initialized;
            bool m_loggedIn;
            QString m_username;
            QString m_password;
            Attica::PostJob* m_checkLoginJob;

        protected slots:
            void finishInit();
            void checkLoginResult( Attica::BaseJob* );

        signals:
            /** signal which is emitted when initialization is complete
             */
            void initialized();
            /** signal which is emitted if initialization failed
             */
            void initFailed();
            /** signal which is emitted if login is complete
             */
            void loggedIn();
            /** signal which is emitted when login failed
             */
            void loginFailed();
    };
}

#endif // AUTHENTICATION_H

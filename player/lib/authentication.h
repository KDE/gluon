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
    class GLUON_PLAYER_EXPORT Authentication : public GluonCore::Singleton<Authentication>
    {
            Q_OBJECT

        public:
            void init();
            bool isInitialized();
            bool login(const QString& username, const QString& password);
            bool isLoggedIn();
            bool hasCredentials();
            QString username();
            QString password();

        private:
            friend class GluonCore::Singleton<Authentication>;
            Authentication();
            ~Authentication();
            Q_DISABLE_COPY(Authentication)

            bool m_initialized;
            bool m_loggedIn;
            QString m_username;
            QString m_password;
            Attica::PostJob *m_checkLoginJob;

        protected slots:
            void finishInit();
            void checkLoginResult(Attica::BaseJob*);

        signals:
            void initialized();
            void initFailed();
            void loggedIn();
            void loginFailed();
    };
}

#endif // AUTHENTICATION_H

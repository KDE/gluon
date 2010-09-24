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
            QString username();
            void login(const QString& username, const QString& password);
            bool isLoggedIn();

        private:
            friend class GluonCore::Singleton<Authentication>;
            Authentication();
            ~Authentication();
            Q_DISABLE_COPY(Authentication)

            bool m_loggedIn;
            QString m_username;
            QString m_password;
            Attica::PostJob *m_checkLoginJob;

        protected slots:
            void checkAndPerformLogin();
            void performLogin(Attica::BaseJob*);

        signals:
            void loggedIn();
            void loginFailed();
    };
}

#endif // AUTHENTICATION_H

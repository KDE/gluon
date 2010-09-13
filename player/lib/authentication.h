#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <core/singleton.h>
#include <attica/providermanager.h>
#include "gluon_player_export.h"

namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT Authentication : public GluonCore::Singleton<Authentication>
    {
        Q_OBJECT

        public:
            QString username();
            void setCredentials(const QString &username, const QString &password);

        private:
            friend class GluonCore::Singleton<Authentication>;
            Authentication();
            ~Authentication();
            Q_DISABLE_COPY(Authentication)

            QString m_username;
    };
}

#endif // AUTHENTICATION_H

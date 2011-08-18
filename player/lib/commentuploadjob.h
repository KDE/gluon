/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUONPLAYER_COMMENTUPLOADJOB_H
#define GLUONPLAYER_COMMENTUPLOADJOB_H

#include "abstractsocialservicesjob.h"

namespace Attica
{
    class BaseJob;
}

namespace GluonPlayer
{

    class CommentUploadJob : public AbstractSocialServicesJob
    {
        Q_OBJECT
        public:
            CommentUploadJob( Attica::Provider* provider, const QString& id, const QString& parentId,
                                          const QString& subject, const QString& message );
            virtual ~CommentUploadJob();

            virtual QVariant data();

        protected Q_SLOTS:
            virtual void startSocialService();

        private Q_SLOTS:
            void uploadCommentFinished( Attica::BaseJob* job );

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONPLAYER_COMMENTUPLOADJOB_H

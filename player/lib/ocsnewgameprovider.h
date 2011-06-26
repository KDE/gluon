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

#ifndef GLUONPLAYER_OCSNEWGAMEPROVIDER_H
#define GLUONPLAYER_OCSNEWGAMEPROVIDER_H

#include <QtCore/QObject>

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{

    class OcsNewGameProvider : public QObject
    {
            Q_OBJECT
        public:
            explicit OcsNewGameProvider( Attica::Provider* provider, const QString& gameCategory,
                                         const QString& gameName, QObject* parent = 0 );
            virtual ~OcsNewGameProvider();

        Q_SIGNALS:
            void finished( const QString& id );
            void failed();

        private Q_SLOTS:
            void addNewGame();
            void addNewGameComplete( Attica::BaseJob* baseJob );

        private:
            class Private;
            Private* const d;

            friend class OcsProvider;
    };

}
#endif // GLUONPLAYER_OCSNEWGAMEPROVIDER_H


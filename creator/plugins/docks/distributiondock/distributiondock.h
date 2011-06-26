/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUON_CREATOR_DISTRIBUTIONDOCK_H
#define GLUON_CREATOR_DISTRIBUTIONDOCK_H

#include <QtGui/QDockWidget>

namespace GluonPlayer
{
    class OcsCategory;
}

namespace GluonEngine
{
    class GameProject;
}

namespace GluonCreator
{
    class DistributionDock : public QDockWidget
    {
            Q_OBJECT
        public:
            explicit DistributionDock( const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0 );
            virtual ~DistributionDock();

        private Q_SLOTS:
            void updateUiFromGameProject( GluonEngine::GameProject* gameProject );
            void doLogin();
            void loginSuccessful();
            void loginFailed();
            void createOrUpdateGame();
            void newGameUploadFinished( const QString &id );
            void newGameUploadFailed();
            void updateCategories();
            void categoriesFetched( QList<GluonPlayer::OcsCategory*> categories );
            void loadCredentials();

        private:
            class DistributionDockPrivate;
            DistributionDockPrivate* const d;
    };

}

#endif // GLUON_CREATOR_DISTRIBUTIONDOCKPLUGIN_H

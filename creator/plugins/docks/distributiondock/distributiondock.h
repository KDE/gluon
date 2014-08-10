/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#include <QtWidgets/QDockWidget>

namespace GluonPlayer
{
    class CategoryItem;
    class GameDetailItem;
    class LicenseItem;
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
            void updateUiFromGameProject();
            void doLogin();
            void createOrUpdateGame();
            void newGameUploadFinished();
            void newGameUploadFailed();
            void editGameFinished();
            void editGameFailed();
            void updateCategories();
            void categoriesFetched();
            void loadCredentials();
            void initEditGameProvider();
            void gameDetailsFetched();
            void updateLicenses();
            void licensesFetched();
            QString createArchive( );
            void uploadGameArchive();

        Q_SIGNALS:
            void switchToCreateMode();
            void switchToUpdateMode();
            void gameUploadFinished();

        private:
            class DistributionDockPrivate;
            DistributionDockPrivate* const d;

            void initGuiStates();
            void fetchExistingGameDetails();
    };

}

#endif // GLUON_CREATOR_DISTRIBUTIONDOCKPLUGIN_H

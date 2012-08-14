/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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

#include "distributionwizard.h"
#include <player/lib/serviceprovider.h>
#include <player/lib/addgamejob.h>
#include <player/lib/categorylistjob.h>
#include <player/lib/editgamejob.h>
#include <player/lib/gamedetaillistjob.h>
#include <player/lib/licensejob.h>
#include <player/lib/gamedetailsjob.h>
#include <player/lib/gameuploadjob.h>
#include <player/lib/archive/archiver.h>
#include "ui_distributionwizard.h"

#include <QDebug>

class DistributionWizard::DistributionWizardPrivate
{
   public:
        DistributionWizardPrivate()
        {
        }
    Ui::Wizard wizard;
    QWizard wizardobj;

};

DistributionWizard::DistributionWizard():QObject(),d( new DistributionWizardPrivate() )
{
  d->wizard.setupUi(&d->wizardobj);
//  updateCategories();
 // updateLicenses();
}

DistributionWizard::~DistributionWizard()
{
  delete d;
}

void DistributionWizard::startWizard()
{

  d->wizardobj.show();
}
void DistributionWizard::updateCategories()
{
   /* GluonPlayer::CategoryListJob* categoryListJob = GluonPlayer::ServiceProvider::instance()->fetchCategories();
    connect( categoryListJob, SIGNAL(succeeded()), SLOT(categoriesFetched()) );
    categoryListJob->start();*/
}

void DistributionWizard::uploadGame()
{
/*    GluonPlayer::AddGameJob* addGameJob = GluonPlayer::ServiceProvider::instance()->addGame(wizard.nameEdit->text(),categoryIds.at( wizard.categoryComboBox->currentIndex()));
    connect( addGameJob, SIGNAL(succeeded()), SLOT(uploadFinished()));
//    connect( addGameJob, SIGNAL(failed()), SLOT(newGameUploadFailed()) );
//    addGameJob->start();*/
}

void DistributionWizard::uploadFinished()
{
/*    QString id = qobject_cast<GluonPlayer::AddGameJob*>( sender() )->data().toString();
    wizard.gameIdEdit->setText( id );
    GluonEngine::Game::instance()->gameProject()->setProperty( "id", id );
    updateUi();
    emit gameUploadFinished();*/
}

void DistributionWizard::updateUi()
{
/*    GluonPlayer::GameDetailsJob* gameDetailsJob = GluonPlayer::ServiceProvider::instance()->fetchOneGame( id );
    connect( gameDetailsJob, SIGNAL(succeeded()), SLOT(gameDetailsFetched()) ) ;
    gameDetailsJob->start();*/

}

void DistributionWizard::categoriesFetched()
{	
/*    QList<GluonPlayer::CategoryItem*> categories = qobject_cast<GluonPlayer::CategoryListJob*>( sender() )->data().value< QList<GluonPlayer::CategoryItem*> >();
    wizard.categoryComboBox->clear();
    categoryIds.clear();

    foreach( GluonPlayer::CategoryItem * category, categories )
    {
        QString categoryString = category->name();
        if( categoryString.startsWith( QLatin1String("Gluon"), Qt::CaseInsensitive ) )
        {   
            categoryIds.append( category->id() );
            wizard.categoryComboBox->addItem( categoryString );
        }
    }
*/
}

void DistributionWizard::updateLicenses()
{
  /*  GluonPlayer::LicenseJob* licenseJob = GluonPlayer::ServiceProvider::instance()->fetchLicenses();
    connect( licenseJob, SIGNAL(succeeded()), SLOT(licensesFetched()) );
    licenseJob->start();*/
}


void DistributionWizard::licensesFetched()
{/*
    QList<GluonPlayer::LicenseItem*> licenses = qobject_cast<GluonPlayer::LicenseJob*>( sender() )->data().value< QList<GluonPlayer::LicenseItem*> >();
    wizard.licenseComboBox->clear();
    licenseIds.clear();

    foreach( GluonPlayer::LicenseItem * license, licenses )
    {
        licenseIds.append( license->id() );
        wizard.licenseComboBox->addItem( license->licenseName() );
    }*/
}

#include "distributionwizard.moc"

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
#include <ui_distributionwizard.h>
#include <player/lib/serviceprovider.h>
#include <engine/game.h>
#include <player/lib/addgamejob.h>
#include <player/lib/categorylistjob.h>
#include <player/lib/editgamejob.h>
#include <player/lib/gamedetaillistjob.h>
#include <player/lib/licensejob.h>
#include <player/lib/gamedetailsjob.h>
#include <player/lib/gameuploadjob.h>
#include <player/lib/archive/archiver.h>

#include <QDebug>


class DistributionWizard::DistributionWizardPrivate
{
   public:
        DistributionWizardPrivate()
        {
        }
    Ui::Wizard wizard;
    QWizard wizardobj;
    GluonPlayer::EditGameJob* editGameJob;
};

DistributionWizard::DistributionWizard():QObject(),d( new DistributionWizardPrivate() )
{
  countUploads = 0;
  d->wizard.setupUi(&d->wizardobj);
  connect(&d->wizardobj,SIGNAL(currentIdChanged( int)),this,SLOT(pageChanged(int)));
  updateCategories();
  updateLicenses();
}
void DistributionWizard::uploadGameArchive()
{
    if( gameid.isEmpty() || apiKey.isEmpty() )
    {
        return;
    }
    const QString dirName = GluonEngine::Game::instance()->gameProject()->dirname().toLocalFile();
    const QString gameName = GluonEngine::Game::instance()->gameProject()->name();
    const QString archivePath = dirName + "/../" + gameName + ".gluonarchive";
    Archiver archiver( dirName, archivePath );
    archiver.start();

    GluonPlayer::GameUploadJob* uploadJob = GluonPlayer::ServiceProvider::instance()->uploadGame( gameid, archivePath );
    connect( uploadJob, SIGNAL(succeeded()), SLOT(editGameFinished()) );
    uploadJob->setApiKey(apiKey );
    uploadJob->start();
}

void DistributionWizard::editGameFinished()
{
    qDebug()<<"upload job is succeeding";
}

DistributionWizard::~DistributionWizard()
{
  delete d;
}
void DistributionWizard::pageChanged(int pageId)
{
  switch(pageId)
      {
	case(1):
	  { apiKey = d->wizard.apiKeyEdit->text(); 
	    d->wizard.gameIdEdit->setEnabled(false);
	    d->wizard.versionEdit_2->setEnabled(false);
	    d->wizard.homePageEdit->setEnabled(false);
	    d->wizard.licenseComboBox->setEnabled(false);
	  }
          break;
	  
	case(2):
	  {
	    if( d->wizard.gameIdEdit->text().isEmpty() )
	      {
		gameName = d->wizard.nameEdit->text();
		chosenCategory = categoryIds.at( d->wizard.categoryComboBox->currentIndex());
		
		if(countUploads == 0)
		{	
		    GluonPlayer::AddGameJob* addGameJob = GluonPlayer::ServiceProvider::instance()->addGame( gameName,chosenCategory );
		    connect( addGameJob, SIGNAL(succeeded()), SLOT(uploadFinished()));
		    addGameJob->start();
		    countUploads++;
		}
	      }
	    updateUi();
	  }
          break;

	case(3):
	  { 
	    homepage = d->wizard.nexthomePageEdit->text();
	    version = d->wizard.nextversionEdit->text(); 
	    chosenLicense = licenseIds.at( d->wizard.nextlicenseComboBox->currentIndex());
	  }

	case(4):
	   description = d->wizard.descriptionEdit->toPlainText();

	case(5):
	  { 
	    changeLog = d->wizard.changelogEdit->toPlainText();
	    finalUploading();
	  }
	  break;
	  
	default:
	  break;

      }
}

void DistributionWizard::startWizard()
{
    d->wizardobj.show();
}
void DistributionWizard::updateCategories()
{
    GluonPlayer::CategoryListJob* categoryListJob = GluonPlayer::ServiceProvider::instance()->fetchCategories();
    connect( categoryListJob, SIGNAL(succeeded()), SLOT(categoriesFetched()) );
    categoryListJob->start();
}


void DistributionWizard::uploadFinished()
{
    QString id = qobject_cast<GluonPlayer::AddGameJob*>( sender() )->data().toString();
    GluonEngine::Game::instance()->gameProject()->setProperty( "id", id );
}

void DistributionWizard::updateUi()
{
 if( !GluonEngine::Game::instance()->gameProject() )
        return;

    QString id = GluonEngine::Game::instance()->gameProject()->property( "id" ).toString();
    d->wizard.gameIdEdit->setText( id );
    gameid = id;

    if( id.isEmpty() )
    {
        d->wizard.detailsPage->setSubTitle("Failed to generate a proper game ID, please specify name and category both");
    }
    else
    {
	d->wizard.nextdetailsPage->setSubTitle("Please fill rest of the required fields");
	d->wizard.nextgameIdEdit->setText(id);
	d->wizard.nextnameEdit->setText(gameName);
	d->wizard.nextCategory->setCurrentIndex(categoryIds.indexOf( chosenCategory));
	d->wizard.nextgameIdEdit->setEnabled(false);
	d->wizard.nextnameEdit->setEnabled(false);
	d->wizard.nextCategory->setEnabled(false);

    }
}
void DistributionWizard::finalUploading()
{
	d->editGameJob = GluonPlayer::ServiceProvider::instance()->editGame(
                             d->wizard.gameIdEdit->text() );
        connect( d->editGameJob, SIGNAL(failed()),this ,SLOT(editGamefailed()));

        d->editGameJob->setName( gameName );
        d->editGameJob->setCategory( chosenCategory);
        d->editGameJob->setChangelog(description);
        d->editGameJob->setDescription(changeLog);
        d->editGameJob->setHomepage(homepage);
        d->editGameJob->setVersion(version);
	d->editGameJob->setLicense(chosenLicense);
        d->editGameJob->start();
	uploadGameArchive();

}

void DistributionWizard::editGamefailed()
{
  qDebug()<< "Uploading Failed";
}

void DistributionWizard::gamedetailsFetched()
{
   GluonPlayer::GameDetailItem* gameDetails = qobject_cast<GluonPlayer::GameDetailsJob*>( sender() )->data().value<GluonPlayer::GameDetailItem*>();
    d->wizard.nextversionEdit->setText( gameDetails->version() );
    d->wizard.nexthomePageEdit->setText( gameDetails->homePage() );
    d->wizard.licenseComboBox->setCurrentIndex( licenseIds.indexOf( gameDetails->license() ) );
}


void DistributionWizard::categoriesFetched()
{	
    QList<GluonPlayer::CategoryItem*> categories = qobject_cast<GluonPlayer::CategoryListJob*>( sender() )->data().value< QList<GluonPlayer::CategoryItem*> >();
    d->wizard.categoryComboBox->clear();
    categoryIds.clear();

    foreach( GluonPlayer::CategoryItem * category, categories )
    {
        QString categoryString = category->name();
        if( categoryString.startsWith( QLatin1String("Gluon"), Qt::CaseInsensitive ) )
        {   
            categoryIds.append( category->id() );
            d->wizard.categoryComboBox->addItem( categoryString );
        }
    }

}

void DistributionWizard::updateLicenses()
{
    GluonPlayer::LicenseJob* licenseJob = GluonPlayer::ServiceProvider::instance()->fetchLicenses();
    connect( licenseJob, SIGNAL(succeeded()), SLOT(licensesFetched()) );
    licenseJob->start();
}


void DistributionWizard::licensesFetched()
{
    QList<GluonPlayer::LicenseItem*> licenses = qobject_cast<GluonPlayer::LicenseJob*>( sender() )->data().value< QList<GluonPlayer::LicenseItem*> >();
    d->wizard.nextlicenseComboBox->clear();
    licenseIds.clear();

    foreach( GluonPlayer::LicenseItem * license, licenses )
    {
        licenseIds.append( license->id() );
        d->wizard.nextlicenseComboBox->addItem( license->licenseName() );
    }
}

#include "distributionwizard.moc"

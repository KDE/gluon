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
#ifndef DISTRIBUTIONWIZARD_H
#define DISTRIBUTIONWIZARD_H

#include "mainwindow.h"
#include <QWizard>
#include <QWizardPage>

class QWizard;

class DistributionWizard: public QObject
{
        Q_OBJECT
        public:
            DistributionWizard();
            virtual ~DistributionWizard();
            void startWizard();
	    void updateCategories();
	    void updateLicenses();
	    void updateUi();
	    class DistributionWizardPrivate;
	    DistributionWizardPrivate* const d;

	public slots:
	    void categoriesFetched();
	    void uploadFinished();
	    void editGamefailed();
	    void editGameFinished();
	    void licensesFetched();
	    void gamedetailsFetched();
	    void pageChanged(int pageId);
	    void uploadGameArchive();
	    void finalUploading();
	
	private:
	    QStringList categoryIds;
	    QStringList licenseIds;
	    QString apiKey;
	    QString gameid;
	    QString gameName;
	    QString chosenCategory;
	    QString description;
	    QString changeLog;
	    QString homepage;
	    QString version;
	    QString chosenLicense;
};

#endif // DISTRIBUTIONWIZARD_H
 

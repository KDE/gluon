/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "vcsbranchwidget.h"

#include <QtGui/QHeaderView>
#include <QtGui/QAction>

#include <interfaces/iplugin.h>
#include <interfaces/icore.h>
#include <interfaces/iruncontroller.h>

#include <vcs/interfaces/idistributedversioncontrol.h>
#include <vcs/models/vcsitemeventmodel.h>
#include <vcs/vcsjob.h>
#include <vcs/vcsrevision.h>
#include <vcs/vcsevent.h>
#include <vcs/vcslocation.h>

#include <KDE/KDebug>
#include <KDE/KMenu>
#include <KDE/KLocale>
#include <KDE/KDialog>
#include <KDE/KPushButton>
#include <KDE/KMessageBox>
#include <KDE/KLineEdit>

#include <QtGui/QListView>

using namespace GluonCreator;

VcsBranchWidget::VcsBranchWidget( KDevelop::IDistributedVersionControl* vcsInterface, const QString& repositoryPath, QWidget* parent )
    : QWidget( parent )
    , m_vcsInterface( vcsInterface )
    , m_repositoryPath( repositoryPath )
{
    setupUi();

    connect(m_createUseButton, SIGNAL(clicked()), SLOT(createUseBranch()));
    connect(m_createButton, SIGNAL(clicked()), SLOT(createBranch()));

    m_branches = m_vcsInterface->branches(m_repositoryPath);
    m_curBranch = m_vcsInterface->curBranch(m_repositoryPath);
}

VcsBranchWidget::~VcsBranchWidget()
{
}

void VcsBranchWidget::setupUi()
{
    if( objectName().isEmpty() )
        setObjectName( QString::fromUtf8( "VcsBranchWidget" ) );

    resize( 640, 480 );

    m_gridLayout = new QGridLayout( this );
    m_gridLayout->setObjectName( QString::fromUtf8( "gridLayout" ) );

    m_branchView = new QListView(this);
    m_branchView->setObjectName(QString::fromUtf8("branchView"));

    m_gridLayout->addWidget(m_branchView, 0, 0, 1, 1); 

    m_newBranchName = new KLineEdit( "New Branch Name", this );
    m_newBranchName->setObjectName( QString::fromUtf8( "newBranchName" ) );
    m_newBranchName->setAlignment( Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop );

    m_gridLayout->addWidget( m_newBranchName, 1, 0, 1, 1 );

    m_createUseButton = new KPushButton( "Create and Use", this );
    m_createUseButton->setObjectName( QString::fromUtf8( "CreateUse" ) );
    m_createUseButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );

    m_gridLayout->addWidget( m_createUseButton, 2, 0, 1, 1 );

    m_createButton = new KPushButton( "Create", this );
    m_createButton->setObjectName( QString::fromUtf8( "Create" ) );
    m_createButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );

    m_gridLayout->addWidget( m_createButton, 2, 1, 1, 1 );

    retranslateUi();

    QMetaObject::connectSlotsByName( this );

}

void VcsBranchWidget::retranslateUi()
{
    setWindowTitle( tr2i18n( "Branch view", 0 ) );
}

void VcsBranchWidget::createUseBranch()
{
}

void VcsBranchWidget::createBranch()
{
    QString baseBranch = m_branchView->currentIndex().data().toString();
    QString newBranch = m_newBranchName->text();

    if (!m_model->findItems(newBranch).isEmpty())
    {   
        KMessageBox::messageBox(this, KMessageBox::Sorry, i18n("Branch \"%1\" already exists.\n"
                                        "Please, choose another name.", newBranch));
    }   
    else
    {
        // KDevelop::VcsJob* branchJob = m_vcsInterface->branch(m_repositoryPath, baseBranch, newBranch)
        m_vcsInterface->branch(m_repositoryPath, baseBranch, newBranch)->exec();
        
    }
}

void VcsBranchWidget::delBranch()
{
    QString baseBranch = m_ui->branchView->selectionModel()->selection().indexes().first().data().toString();

    if (baseBranch == d->curBranch(repo))
    {   
        KMessageBox::messageBox(this, KMessageBox::Sorry,
                                    i18n("Currently at the branch \"%1\".\n"
                                            "To remove it, please change to another branch.",
                                            baseBranch));
        return;
    }   

    int ret = KMessageBox::messageBox(this, KMessageBox::WarningYesNo,
                                      i18n("Are you sure you want to irreversibly remove the branch '%1'?", baseBranch));
    if (ret == KMessageBox::Yes)
        m_model->removeBranch(baseBranch);
}

void VcsBranchWidget::checkoutBranch()
{
    QString branch = m_ui->branchView->currentIndex().data().toString();
    if (branch == d->curBranch(repo))
    {
        KMessageBox::messageBox(this, KMessageBox::Sorry,
                                i18n("Already on branch \"%1\"\n",
                                        branch));
        return;
    }

    kDebug() << "Switching to" << branch << "in" << repo;
    KDevelop::VcsJob *branchJob = d->switchBranch(repo, branch);
//     connect(branchJob, SIGNAL(finished(KJob*)), m_model, SIGNAL(resetCurrent()));

    ICore::self()->runController()->registerJob(branchJob);
    close();
}


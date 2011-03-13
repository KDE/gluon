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

#include "vcsdiffwidget.h"

#include <KDE/KTextEdit>
#include <KDE/KDebug>
#include <KDE/KLocale>
#include <KDE/KSqueezedTextLabel>

#include <interfaces/icore.h>
#include <interfaces/iruncontroller.h>

#include <vcs/vcsjob.h>
#include <vcs/vcsrevision.h>
#include <vcs/vcsdiff.h>

// #include "vcsdiffpatchsources.h"

using namespace GluonCreator;

VcsDiffWidget::VcsDiffWidget( KDevelop::VcsJob* job, QWidget* parent )
    : QWidget( parent )
    , m_job( job )
{
    setupUi( );
    // connect( m_job, SIGNAL( resultsReady( KDevelop::VcsJob *) ), SLOT( diffReady( KDevelop::VcsJob* ) ) );
    // ICore::self()->runController()->registerJob( m_job );
}

VcsDiffWidget::~VcsDiffWidget()
{
}

void VcsDiffWidget::setRevisions( const KDevelop::VcsRevision& first,
                                  const KDevelop::VcsRevision& second )
{
    m_revLabel->setText( i18n("Difference between revision %1 and %2:",
                       first.prettyValue(),
                       second.prettyValue() ) );
}

void VcsDiffWidget::diffReady( KDevelop::VcsJob* job )
{
    if( job != m_job )
        return;

    // KDevelop::VcsDiff diff = qVariantValue<KDevelop::VcsDiff>( m_job->fetchResults() );

    // // Try using the patch-review plugin if possible
    // VCSDiffPatchSource* patch = new VCSDiffPatchSource(diff);

    // if(showVcsDiff(patch))
    // {
        // q->deleteLater();
        // return;
    // }else{
        // delete patch;
    // }

    // kDebug() << "diff:" << diff.leftTexts().count();
    // foreach( const KDevelop::VcsLocation &l, diff.leftTexts().keys() )
    // {
        // kDebug() << "diff:" << l.localUrl() << l.repositoryServer();
    // }
    // kDebug() << "diff:" << diff.diff();
    // kDebug() << "diff:" << diff.type();
    // kDebug() << "diff:" << diff.contentType();
    // m_ui->diffDisplay->setPlainText( diff.diff() );
    // m_ui->diffDisplay->setReadOnly( true );
}

void VcsDiffWidget::setupUi()
{
}


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

#include "vcslogwidget.h"

#include <QtGui/QHeaderView>
#include <QtGui/QAction>

#include <interfaces/iplugin.h>
#include <interfaces/icore.h>
#include <interfaces/iruncontroller.h>

#include <vcs/interfaces/ibasicversioncontrol.h>
#include <vcs/models/vcsitemeventmodel.h>
// #include <vcs/models/vcseventmodel.h>
#include <vcs/vcsjob.h>
#include <vcs/vcsrevision.h>
#include <vcs/vcsevent.h>
#include <vcs/vcslocation.h>

#include <KDE/KDebug>
#include <KDE/KMenu>
#include <KDE/KLocale>
#include <KDE/KDialog>
#include <KDE/KPushButton>

using namespace GluonCreator;

VcsLogWidget::VcsLogWidget( const KUrl& url, KDevelop::VcsJob* job, QWidget* parent )
    : QWidget( parent )
    , m_job( job )
    , m_url( url )
{

    //Don't autodelete this job, its metadata will be used later on
    if( m_job )
        m_job->setAutoDelete( false );

    setupUi();

    connect( m_job, SIGNAL( resultsReady( KDevelop::VcsJob* ) ), SLOT( jobReceivedResults( KDevelop::VcsJob* ) ) );
    connect( m_historySlider, SIGNAL( valueChanged(int) ), SLOT( updateCommit(int) ) );
    connect( m_fineHistorySlider, SIGNAL( valueChanged(int) ), SLOT( updateCommit(int) ) );
    KDevelop::ICore::self()->runController()->registerJob( m_job );
}

VcsLogWidget::~VcsLogWidget()
{
    delete m_logModel;
    delete m_detailModel;
}

// void VcsLogWidget::eventViewCustomContextMenuRequested( const QPoint& point )
// {
    // m_contextIndex = m_eventView->indexAt( point );
    // if( !m_contextIndex.isValid() )
    // {
        // kDebug() << "contextMenu is not in TreeView";
        // return;
    // }

    // KMenu menu( m_eventView );

    // QAction* action = menu.addAction( i18n( "Diff to previous revision" ) );
    // QObject::connect( action, SIGNAL( triggered( bool ) ), SLOT( diffToPrevious() ) );

    // action = menu.addAction( i18n( "Diff between revisions" ) );
    // QObject::connect( action, SIGNAL( triggered( bool ) ), SLOT( diffRevisions() ) );
    // action->setEnabled( m_eventView->selectionModel()->selectedRows().size() >= 2 );

    // menu.exec( m_eventView->viewport()->mapToGlobal( point ) );
// }

// void VcsLogWidget::currentRowChanged( const QModelIndex& start, const QModelIndex& [> end <] )
// {
    // if( start.isValid() )
        // eventViewClicked( start );
// }

// void VcsLogWidget::eventViewClicked( const QModelIndex& index )
// {
    // KDevelop::VcsEvent ev = m_logModel->eventForIndex( index );
    // if( ev.revision().revisionType() != KDevelop::VcsRevision::Invalid )
    // {
    // m_ui->message->setPlainText( ev.message() );
    // m_detailModel->clear();
    // m_detailModel->addItemEvents( ev.items() );
    // }else
    // {
    // m_ui->message->clear();
    // m_detailModel->clear();
    // }
// }

void VcsLogWidget::jobReceivedResults( KDevelop::VcsJob* job )
{
    if( job == m_job )
    {
        QList<QVariant> l = job->fetchResults().toList();
        m_historySlider->setRange( 0, l.count() - 1 );
        m_fineHistorySlider->setRange( 0, l.count() - 1 );
        m_newevents.clear();
        foreach( const QVariant & v, l )
        {
            if( qVariantCanConvert<KDevelop::VcsEvent>( v ) )
            {
                m_newevents << qVariantValue<KDevelop::VcsEvent>( v );
            }
        }
        m_message->setPlainText( m_newevents.last().message() );
        m_historySlider->setValue( m_newevents.count());
        m_fineHistorySlider->setValue( m_newevents.count());
    }
}

void VcsLogWidget::setupUi()
{
    if( objectName().isEmpty() )
        setObjectName( QString::fromUtf8( "VcsLogWidget" ) );

    resize( 640, 480 );

    m_gridLayout = new QGridLayout( this );
    m_gridLayout->setObjectName( QString::fromUtf8( "gridLayout" ) );

    m_historySlider = new QSlider( Qt::Horizontal, this );
    m_historySlider->setObjectName( QString::fromUtf8( "historySlider") );

    m_gridLayout->addWidget( m_historySlider, 0, 0, 1, 1 );

    m_fineHistorySlider = new QSlider( Qt::Horizontal, this );
    m_fineHistorySlider->setObjectName( QString::fromUtf8( "fineHistorySlider") );

    m_gridLayout->addWidget( m_fineHistorySlider, 1, 0, 1, 1 );

    m_label = new KSqueezedTextLabel( this );
    m_label->setObjectName( QString::fromUtf8( "label" ) );
    m_label->setTextFormat( Qt::PlainText );
    m_label->setAlignment( Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop );

    m_gridLayout->addWidget( m_label, 2, 0, 1, 1 );

    m_label2 = new KSqueezedTextLabel( this );
    m_label2->setObjectName( QString::fromUtf8( "label_2" ) );
    m_label2->setTextFormat( Qt::PlainText );
    m_label2->setAlignment( Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop );

    m_gridLayout->addWidget( m_label2, 3, 0, 1, 1 );

    m_message = new KTextBrowser( this );
    m_message->setObjectName( QString::fromUtf8( "message" ) );
    QSizePolicy sizePolicy1( QSizePolicy::Expanding, QSizePolicy::Expanding );
    sizePolicy1.setHorizontalStretch( 2 );
    sizePolicy1.setVerticalStretch( 0 );
    sizePolicy1.setHeightForWidth( m_message->sizePolicy().hasHeightForWidth() );
    m_message->setSizePolicy( sizePolicy1 );
    m_message->setAcceptRichText( false );

    m_gridLayout->addWidget( m_message, 4, 0, 1, 1 );

    // m_diffButton = new KPushButton( "See Changes", this );
    // m_diffButton->setObjectName( QString::fromUtf8( "diffButton" ) );
    // m_diffButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );

    // m_gridLayout->addWidget( m_label, 5, 0, 1, 1 );


#ifndef UI_QT_NO_SHORTCUT
    m_label2->setBuddy( m_message );
#endif // QT_NO_SHORTCUT

    retranslateUi();

    QMetaObject::connectSlotsByName( this );

}

void VcsLogWidget::retranslateUi()
{
    setWindowTitle( tr2i18n( "Logview", 0 ) );
    m_label->setText( tr2i18n( "History:", 0 ) );
    m_label2->setText( tr2i18n( "Message:", 0 ) );
}

void VcsLogWidget::updateCommit(int)
{
    m_message->setPlainText( m_newevents.at(m_historySlider->value()).message());
}


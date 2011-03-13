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

#include "vcsdiffwidget.h"

#include <QtGui/QHeaderView>
#include <QtGui/QAction>

#include <interfaces/iplugin.h>
#include <interfaces/icore.h>
#include <interfaces/iruncontroller.h>

#include <vcs/interfaces/ibasicversioncontrol.h>
#include <vcs/models/vcsitemeventmodel.h>
#include <vcs/models/vcseventmodel.h>
#include <vcs/vcsjob.h>
#include <vcs/vcsrevision.h>
#include <vcs/vcsevent.h>
#include <vcs/vcslocation.h>

#include <KDE/KDebug>
#include <KDE/KMenu>
#include <KDE/KLocale>
#include <KDE/KDialog>

using namespace GluonCreator;

VcsLogWidget::VcsLogWidget( const KUrl& url, KDevelop::VcsJob *job, QWidget *parent )
    : QWidget(parent)
    , m_job( job )
    , m_url( url )
{

    //Don't autodelete this job, its metadata will be used later on
    m_job->setAutoDelete( false );

    // setupUi();

    m_logModel= new KDevelop::VcsEventModel(this);
    m_eventView->setModel( m_logModel );
    m_eventView->sortByColumn(0, Qt::DescendingOrder);
    m_eventView->setContextMenuPolicy( Qt::CustomContextMenu );
    QHeaderView* header = m_eventView->horizontalHeader();
    header->setResizeMode( 0, QHeaderView::ResizeToContents );
    header->setResizeMode( 1, QHeaderView::ResizeToContents );
    header->setResizeMode( 2, QHeaderView::ResizeToContents );
    header->setResizeMode( 3, QHeaderView::Stretch );

    m_detailModel = new KDevelop::VcsItemEventModel(this);
    m_itemEventView->setModel( m_detailModel );
    header = m_itemEventView->horizontalHeader();
    header->setResizeMode( 0, QHeaderView::ResizeToContents );
    header->setResizeMode( 1, QHeaderView::Stretch );
    header->setResizeMode( 2, QHeaderView::ResizeToContents );
    header->setResizeMode( 3, QHeaderView::Stretch );
    header->setResizeMode( 4, QHeaderView::ResizeToContents );

    connect( m_eventView, SIGNAL( clicked( const QModelIndex& ) ),
             SLOT( eventViewClicked( const QModelIndex& ) ) );
    connect( m_eventView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
             SLOT(currentRowChanged(QModelIndex,QModelIndex)));
    connect( m_eventView, SIGNAL( customContextMenuRequested( const QPoint& ) ),
             SLOT( eventViewCustomContextMenuRequested( const QPoint& ) ) );

    connect( m_job, SIGNAL(resultsReady( KDevelop::VcsJob*) ),
             SLOT( jobReceivedResults( KDevelop::VcsJob* ) ) );
    KDevelop::ICore::self()->runController()->registerJob( m_job );
}

VcsLogWidget::~VcsLogWidget()
{
    delete m_logModel;
    delete m_detailModel;
}

void VcsLogWidget::eventViewCustomContextMenuRequested( const QPoint &point )
{
    m_contextIndex = m_eventView->indexAt( point );
    if( !m_contextIndex.isValid() ){
        kDebug() << "contextMenu is not in TreeView";
        return;
    }

    KMenu menu( m_eventView );

    QAction* action = menu.addAction(i18n("Diff to previous revision"));
    QObject::connect( action, SIGNAL(triggered(bool)), SLOT(diffToPrevious()) );

    action = menu.addAction(i18n("Diff between revisions"));
    QObject::connect( action, SIGNAL(triggered(bool)), SLOT(diffRevisions()) );
    action->setEnabled(m_eventView->selectionModel()->selectedRows().size()>=2);

    menu.exec( m_eventView->viewport()->mapToGlobal(point) );
}

void VcsLogWidget::currentRowChanged(const QModelIndex& start, const QModelIndex& /* end */ )
{
    if(start.isValid())
        eventViewClicked(start);
}

void VcsLogWidget::eventViewClicked( const QModelIndex &index )
{
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
}

void VcsLogWidget::jobReceivedResults( KDevelop::VcsJob* job )
{
    if( job == m_job )
    {
        QList<QVariant> l = job->fetchResults().toList();
        QList<KDevelop::VcsEvent> newevents;
        foreach( const QVariant &v, l )
        {
            if( qVariantCanConvert<KDevelop::VcsEvent>( v ) )
            {
                newevents << qVariantValue<KDevelop::VcsEvent>( v );
            }
        }
        m_logModel->addEvents( newevents );
    }
}


void VcsLogWidget::diffToPrevious()
{
    KDevelop::IPlugin* plugin = m_job->vcsPlugin();
    if( plugin )
    {
        KDevelop::IBasicVersionControl* iface = plugin->extension<KDevelop::IBasicVersionControl>();
        if( iface )
        {
            KDevelop::VcsEvent ev = m_logModel->eventForIndex( m_contextIndex );
            KDevelop::VcsRevision prev = KDevelop::VcsRevision::createSpecialRevision(KDevelop::VcsRevision::Previous);
            KDevelop::VcsJob* job = iface->diff( m_url, prev, ev.revision() );

            VcsDiffWidget* widget = new VcsDiffWidget( job );
            widget->setRevisions( prev, ev.revision() );
            KDialog* dlg = new KDialog( this );

            widget->connect(widget, SIGNAL(destroyed(QObject*)), dlg, SLOT(deleteLater()));

            dlg->setCaption( i18n("Difference To Previous") );
            dlg->setButtons( KDialog::Ok );
            dlg->setMainWidget( widget );
            dlg->show();
        }
    }
}

void VcsLogWidget::diffRevisions()
{
    KDevelop::IPlugin* plugin = m_job->vcsPlugin();
    if( plugin )
    {
        KDevelop::IBasicVersionControl* iface = plugin->extension<KDevelop::IBasicVersionControl>();
        if( iface )
        {
            QModelIndexList l = m_eventView->selectionModel()->selectedRows();
            KDevelop::VcsEvent ev1 = m_logModel->eventForIndex( l.first() );
            KDevelop::VcsEvent ev2 = m_logModel->eventForIndex( l.last() );
            KDevelop::VcsJob* job = iface->diff( m_url, ev1.revision(), ev2.revision() );

            VcsDiffWidget* widget = new VcsDiffWidget( job );
            widget->setRevisions( ev1.revision(), ev2.revision() );
            KDialog* dlg = new KDialog( this );
            dlg->setCaption( i18n("Difference between Revisions") );
            dlg->setButtons( KDialog::Ok );
            dlg->setMainWidget( widget );
            dlg->show();
        }
    }
}


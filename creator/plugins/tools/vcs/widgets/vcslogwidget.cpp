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
    if( m_job )
        m_job->setAutoDelete( false );

    setupUi();

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
    // KDevelop::ICore::self()->runController()->registerJob( m_job );
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

void VcsLogWidget::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("VcsLogWidget"));

    resize(640, 480);

    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    m_label = new KSqueezedTextLabel(this);
    m_label->setObjectName(QString::fromUtf8("label"));
    m_label->setTextFormat(Qt::PlainText);
    m_label->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    m_gridLayout->addWidget(m_label, 0, 0, 1, 1);

    m_eventView = new QTableView(this);
    m_eventView->setObjectName(QString::fromUtf8("eventView"));
    m_eventView->setAlternatingRowColors(true);
    m_eventView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_eventView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_eventView->setWordWrap(false);
    m_eventView->setCornerButtonEnabled(false);

    m_gridLayout->addWidget(m_eventView, 0, 1, 1, 3);

    m_label2 = new KSqueezedTextLabel(this);
    m_label2->setObjectName(QString::fromUtf8("label_2"));
    m_label2->setTextFormat(Qt::PlainText);
    m_label2->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    m_gridLayout->addWidget(m_label2, 1, 0, 1, 1);

    m_itemEventView = new QTableView(this);
    m_itemEventView->setObjectName(QString::fromUtf8("itemEventView"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(3);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_itemEventView->sizePolicy().hasHeightForWidth());
    m_itemEventView->setSizePolicy(sizePolicy);
    m_itemEventView->setAlternatingRowColors(true);
    m_itemEventView->setSelectionMode(QAbstractItemView::NoSelection);
    m_itemEventView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_itemEventView->setTextElideMode(Qt::ElideRight);

    m_gridLayout->addWidget(m_itemEventView, 1, 1, 1, 1);

    m_label3 = new KSqueezedTextLabel(this);
    m_label3->setObjectName(QString::fromUtf8("label_3"));
    m_label3->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    m_gridLayout->addWidget(m_label3, 1, 2, 1, 1);

    m_message = new KTextBrowser(this);
    m_message->setObjectName(QString::fromUtf8("message"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(2);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(m_message->sizePolicy().hasHeightForWidth());
    m_message->setSizePolicy(sizePolicy1);
    m_message->setAcceptRichText(false);

    m_gridLayout->addWidget(m_message, 1, 3, 1, 1);

#ifndef UI_QT_NO_SHORTCUT
    m_label->setBuddy(m_eventView);
    m_label3->setBuddy(m_message);
#endif // QT_NO_SHORTCUT
    QWidget::setTabOrder(m_eventView, m_message);

    retranslateUi();

    QMetaObject::connectSlotsByName(this);

}

void VcsLogWidget::retranslateUi()
{
    setWindowTitle(tr2i18n("Logview", 0));
    m_label->setText(tr2i18n("Events:", 0));
    m_label2->setText(tr2i18n("Event Details:", 0));
    m_label3->setText(tr2i18n("Message:", 0));
}

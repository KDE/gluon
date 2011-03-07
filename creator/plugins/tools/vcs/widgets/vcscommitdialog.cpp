/***************************************************************************
 *   Copyright 2007 Dukju Ahn <dukjuahn@gmail.com>                         *
 *   Copyright 2008 Evgeniy Ivanov <powerfox@kde.ru>                       *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "vcscommitdialog.h"

#include <kdevplatform/interfaces/icore.h>
#include <kdevplatform/interfaces/iprojectcontroller.h>
// #include <kdevplatform/vcs/interfaces/iproject.h>
#include <kdevplatform/interfaces/iplugin.h>
// #include <kdevplatform/vcs/interfaces/iuicontroller.h>
#include <kdevplatform/vcs/vcsjob.h>
#include <kdevplatform/vcs/interfaces/ibasicversioncontrol.h>
#include <kdevplatform/vcs/interfaces/idistributedversioncontrol.h>
#include <kdevplatform/vcs/interfaces/icentralizedversioncontrol.h>
#include <kdevplatform/vcs/vcsstatusinfo.h>
// #include "vcs/vcsdiffpatchsources.h"
#include <kdevplatform/vcs/vcspluginhelper.h>

#include <KDE/KTextEdit>
#include <KDE/KComboBox>
#include <KDE/KLocale>
#include <KDE/KDebug>
#include <KDE/KMessageBox>
#include <KDE/KComponentData>
#include <kparts/mainwindow.h>

#include <QtGui/QBrush>
#include <QtGui/QTreeWidget>
#include <QtGui/QCheckBox>
#include <QtCore/QHash>
#include <QtCore/QRegExp>

using namespace GluonCreator;

class VcsCommitDialog::Private
{
public:

    Private( VcsCommitDialog* dialog )
        : message( 0 )
        , files( 0 )
        , recursiveCheck( 0 )
        , lastMessages( 0 )
    {
    }

    ~Private()
    {
    }

    QList< KUrl > selection() {
        if(!m_selection.isEmpty())
            return m_selection;

        QList< KUrl > ret;

        QTreeWidgetItemIterator it( files, QTreeWidgetItemIterator::Checked );
        while( *it ){
            QVariant v = (*it)->data(0, Qt::UserRole);
            Q_ASSERT(v.canConvert<KUrl>());
            ret << v.value<KUrl>();
            ++it;
        }

        return ret;
    }

    QMap<KUrl, KDevelop::VcsStatusInfo::State> urls;
    KDevelop::IPlugin *plugin;
    QHash<KUrl, KDevelop::VcsStatusInfo> statusInfos;
    KDevelop::VcsDiff diff;
    QList< KUrl > m_selection;
    QStringList m_oldMessages;

    // UI elements
    KTextEdit* message;
    KComboBox* lastMessages;
    QTreeWidget* files;
    QCheckBox* recursiveCheck;
};

VcsCommitDialog::VcsCommitDialog( KDevelop::IPlugin *plugin, QWidget *parent )
    : KDialog( parent )
    , d( new Private( this ) )
{
    d->plugin = plugin;
    // d->m_oldMessages = KDevelop::retrieveOldCommitMessages();

    // setupUi( mainWidget() );
    setButtons( KDialog::Ok | KDialog::Cancel );

    setWindowTitle( i18n("Commit Message") );

    d->files->resizeColumnToContents(0);
    d->files->resizeColumnToContents(1);
    d->message->selectAll();
    connect(this, SIGNAL( okClicked() ), SLOT( ok() ) );
    connect(this, SIGNAL( cancelClicked() ), SLOT( cancel() ) );
}

VcsCommitDialog::~VcsCommitDialog()
{
    // KDevelop::addOldCommitMessage(d->message->toPlainText());
    delete d;
}

void VcsCommitDialog::setRecursive( bool recursive )
{
    d->recursiveCheck->setChecked( recursive );
}

void VcsCommitDialog::setMessage( const QString& msg )
{
    d->message->setPlainText( msg );
}

void VcsCommitDialog::setOldMessages( const QStringList& list )
{
    d->lastMessages->clear();
    d->lastMessages->addItems( list );
}

QString VcsCommitDialog::message() const
{
    return d->message->toPlainText();
}

KDevelop::IPlugin* VcsCommitDialog::versionControlPlugin() const
{
    return d->plugin;
}

void VcsCommitDialog::setCommitCandidatesAndShow( const KUrl &url )
{
    kDebug() << "Fetching status for urls:" << url;
    KDevelop::IBasicVersionControl *vcsiface = d->plugin->extension<KDevelop::IBasicVersionControl>();
    if( !vcsiface )
    {
        kDebug() << "oops, no vcsiface";
        return;
    }

    d->urls.clear();
    d->diff.clear();

    //DVCS uses some "hack", see DistributedVersionControlPlugin::status()
    //Thus DVCS gets statuses for all files in the repo. But project->relativeUrl() below helps us
    KDevelop::VcsJob *job = vcsiface->status( url );
    job->exec();
    if( job->status() != KDevelop::VcsJob::JobSucceeded )
    {
        kDebug() << "Couldn't get status for urls: " << url;
    }else
    {
        QVariant varlist = job->fetchResults();

        KStatefulBrush deletedRed(KColorScheme::View, KColorScheme::NegativeText);
        KStatefulBrush newGreen(KColorScheme::View, KColorScheme::ActiveText);

        foreach( const QVariant &var, varlist.toList() )
        {
            KDevelop::VcsStatusInfo info = qVariantValue<KDevelop::VcsStatusInfo>( var );

            d->statusInfos.insert(info.url(), info);

            QString state;
            KStatefulBrush brush(KColorScheme::View, KColorScheme::NormalText);
            Qt::CheckState checked = Qt::Checked;

            switch( info.state() )
            {
                case KDevelop::VcsStatusInfo::ItemAdded:
                    state = i18nc("file was added to versioncontrolsystem", "Added");
                    brush = newGreen;
                    break;
                case KDevelop::VcsStatusInfo::ItemDeleted:
                    state = i18nc("file was deleted from versioncontrolsystem", "Deleted");
                    brush = deletedRed;
                    break;
                case KDevelop::VcsStatusInfo::ItemModified:
                    state = i18nc("version controlled file was modified", "Modified");
                    break;
                case KDevelop::VcsStatusInfo::ItemUnknown:
                    state = i18nc("file is not known to versioncontrolsystem", "Unknown");
                    brush = newGreen;
                    checked = Qt::Unchecked;
                    break;
                default:
                    break;
            }

            if(!state.isEmpty())
            {
                insertRow(state, info.url(), brush, checked);
                d->urls[info.url()] = info.state();
            }
        }
    }
    if( d->files->topLevelItemCount() == 0 )
    {
        reject();
    }

    {
    KDevelop::VcsJob* job = vcsiface->diff(url,
                                        KDevelop::VcsRevision::createSpecialRevision(KDevelop::VcsRevision::Base),
                                        KDevelop::VcsRevision::createSpecialRevision(KDevelop::VcsRevision::Working));

    connect(job, SIGNAL(finished(KJob*)), SLOT(commitDiffJobFinished(KJob*)));
    job->exec();
    }

    /* KDevelop::VCSCommitDiffPatchSource* patchSource = new KDevelop::VCSCommitDiffPatchSource(d->diff, d->urls, vcsiface, d->m_oldMessages);

    if(showVcsDiff(patchSource))
    {
        connect(patchSource, SIGNAL(reviewFinished(QString,QList<KUrl>)), this, SLOT(reviewFinished(QString,QList<KUrl>)));
        connect(patchSource, SIGNAL(reviewCancelled(QString)), this, SLOT(reviewCancalled(QString)));
        connect(patchSource, SIGNAL(destroyed(QObject*)), SLOT(deleteLater()));
    }else{
        delete patchSource;
        show();
    }
    */
}

KUrl::List VcsCommitDialog::determineUrlsForCheckin()
{
    KUrl::List list;
    KUrl::List addItems;

    foreach(const KUrl& url, d->selection()) {
        KDevelop::VcsStatusInfo info = d->statusInfos[url];

        if( info.state() == KDevelop::VcsStatusInfo::ItemUnknown ) {
            addItems << info.url();
        }
        list << info.url();
    }

    if (!addItems.isEmpty()) {
        // KDevelop::IBasicVersionControl* iface = d->plugin->extension<KDevelop::IBasicVersionControl>();
        // KDevelop::VcsJob* job = iface->add( addItems, KDevelop::IBasicVersionControl::NonRecursive );
        // job->exec();
    }

    return list;
}

bool VcsCommitDialog::isRecursive() const
{
    return d->recursiveCheck->isChecked();
}

void VcsCommitDialog::commitDiffJobFinished(KJob* job)
{
    KDevelop::VcsJob* vcsjob = dynamic_cast<KDevelop::VcsJob*>(job);
    Q_ASSERT(vcsjob);

    if (vcsjob) {
        if (vcsjob->status() == KDevelop::VcsJob::JobSucceeded) {
            d->diff = vcsjob->fetchResults().value<KDevelop::VcsDiff>();
        } else {
            // KMessageBox::error(ICore::self()->uiController()->activeMainWindow(), vcsjob->errorString(), i18n("Unable to get differences."));
        }

        vcsjob->disconnect(this);
    }
}

void VcsCommitDialog::insertRow( const QString& state, const KUrl& url,
        const KStatefulBrush &foregroundColor, Qt::CheckState checkstate)
{
    QStringList strings;
    strings << "" << state << KDevelop::ICore::self()->projectController()->prettyFileName(url, KDevelop::IProjectController::FormatPlain);
    QTreeWidgetItem *item = new QTreeWidgetItem( d->files, strings );
    item->setData(0, Qt::UserRole, url);
    item->setForeground(2,  foregroundColor.brush(this));
    item->setCheckState(0, checkstate);
}

void VcsCommitDialog::doAccept()
{
    emit executeCommit(this);
}

void VcsCommitDialog::doCancel()
{
    emit cancelCommit(this);
}

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

#include <kparts/mainwindow.h>
#include <KDE/KTextEdit>
#include <KDE/KComboBox>
#include <KDE/KLocale>
#include <KDE/KMessageBox>
#include <KDE/KComponentData>
#include <KDE/KSqueezedTextLabel>
#include <KDE/KDebug>

#include <QtGui/QBrush>
#include <QtGui/QTreeWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtCore/QHash>
#include <QtCore/QRegExp>

using namespace GluonCreator;

class VcsCommitDialog::Private
{
public:

    Private( VcsCommitDialog* dialog )
    {
    }

    ~Private()
    {
    }

    QList< KUrl > selection() {
        if(!m_selection.isEmpty())
            return m_selection;

        QList< KUrl > ret;

        /* QTreeWidgetItemIterator it( files, QTreeWidgetItemIterator::Checked );
        while( *it ){
            QVariant v = (*it)->data(0, Qt::UserRole);
            Q_ASSERT(v.canConvert<KUrl>());
            ret << v.value<KUrl>();
            ++it;
        } */

        return ret;
    }

    QMap<KUrl, KDevelop::VcsStatusInfo::State> urls;
    KDevelop::IPlugin *plugin;
    QHash<KUrl, KDevelop::VcsStatusInfo> statusInfos;
    KDevelop::VcsDiff diff;
    QList< KUrl > m_selection;
    QStringList m_oldMessages;

};

VcsCommitDialog::VcsCommitDialog( KDevelop::IPlugin *plugin, QWidget *parent )
    : KDialog( parent )
    , d( new Private( this ) )
{
    d->plugin = plugin;
    // d->m_oldMessages = KDevelop::retrieveOldCommitMessages();

    setupUi( );
    setButtons( KDialog::Ok | KDialog::Cancel );

    setWindowTitle( i18n("Commit Message") );

    files->resizeColumnToContents(0);
    files->resizeColumnToContents(1);
    currMessage->selectAll();
    connect(this, SIGNAL( okClicked() ), SLOT( ok() ) );
    connect(this, SIGNAL( cancelClicked() ), SLOT( cancel() ) );
}

VcsCommitDialog::VcsCommitDialog( QWidget *parent )
    : KDialog( parent )
    , d( new Private( this ) )
{
    // d->m_oldMessages = KDevelop::retrieveOldCommitMessages();

    setupUi( );
    setButtons( KDialog::Ok | KDialog::Cancel );

    setWindowTitle( i18n("Commit Message") );

    // d->files->resizeColumnToContents(0);
    // d->files->resizeColumnToContents(1);
    currMessage->selectAll();
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
    recursiveCheck->setChecked( recursive );
}

void VcsCommitDialog::setMessage( const QString& msg )
{
    currMessage->setPlainText( msg );
}

void VcsCommitDialog::setOldMessages( const QStringList& list )
{
    lastMessages->clear();
    lastMessages->addItems( list );
}

QString VcsCommitDialog::message() const
{
    return currMessage->toPlainText();
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
    if( files->topLevelItemCount() == 0 )
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
    return recursiveCheck->isChecked();
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
    QTreeWidgetItem *item = new QTreeWidgetItem( files, strings );
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

void VcsCommitDialog::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("VcsCommitDialog"));

    setProperty("modal", QVariant(false));
    resize(640, 480);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    label = new KSqueezedTextLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    gridLayout->addWidget(label, 0, 0, 1, 1);

    currMessage = new KTextEdit(this);
    currMessage->setObjectName(QString::fromUtf8("message"));
    currMessage->setAcceptRichText(false);

    gridLayout->addWidget(currMessage, 0, 1, 1, 1);

    lastMessages = new KComboBox(this);
    lastMessages->setObjectName(QString::fromUtf8("lastmessages"));
    lastMessages->setInsertPolicy(QComboBox::InsertAtBottom);
    lastMessages->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);

    gridLayout->addWidget(lastMessages, 1, 1, 1, 1);

    label2 = new KSqueezedTextLabel(this);
    label2->setObjectName(QString::fromUtf8("label2"));
    label2->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    gridLayout->addWidget(label2, 2, 0, 1, 1);

    files = new QTreeWidget(this);
    files->setObjectName(QString::fromUtf8("files"));
    files->setIndentation(0);
    files->setAllColumnsShowFocus(true);

    gridLayout->addWidget(files, 2, 1, 1, 1);

    label4 = new KSqueezedTextLabel(this);
    label4->setObjectName(QString::fromUtf8("label4"));

    gridLayout->addWidget(label4, 3, 0, 1, 1);

    recursiveCheck = new QCheckBox(this);
    recursiveCheck->setObjectName(QString::fromUtf8("recursiveChk"));

    gridLayout->addWidget(recursiveCheck, 3, 1, 1, 1);

    label3 = new KSqueezedTextLabel(this);
    label3->setObjectName(QString::fromUtf8("label3"));

    gridLayout->addWidget(label3, 1, 0, 1, 1);

    // retranslateUi(this);
    // QObject::connect(lastmessages, SIGNAL(activated(QString)), message, SLOT(setPlainText(QString)));

    QMetaObject::connectSlotsByName(this);
}



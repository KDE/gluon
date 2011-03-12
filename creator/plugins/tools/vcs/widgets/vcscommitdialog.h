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

#ifndef GLUONCREATOR_VCSCOMMITDIALOG_H
#define GLUONCREATOR_VCSCOMMITDIALOG_H

#include "lib/gluoncreator_macros.h"

#include <KDE/KDialog>
#include <KDE/KUrl>
#include <KDE/KColorScheme>

class KJob;
class QStringList;

namespace KDevelop {
    class IBasicVersionControl;
    class IPlugin;
}

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT VcsCommitDialog : public KDialog
    {
        Q_OBJECT
        public:
            VcsCommitDialog( KDevelop::IPlugin *plugin, QWidget *parent = 0 );
            VcsCommitDialog( QWidget *parent = 0 );
            virtual ~VcsCommitDialog();

            ///Sets the commit candidates, and eventually shows the dialog
            ///Should be called as last action
            void setCommitCandidatesAndShow( const KUrl &list );
            void setMessage( const QString& );
            void setRecursive( bool );
            void setOldMessages( const QStringList& );
            bool isRecursive() const;
            QString message() const;
            KDevelop::IPlugin* versionControlPlugin() const;

            ///Returns the items that are changed and should be checked in.
            ///All other changes like adding, deleting, etc. are done in place
            KUrl::List determineUrlsForCheckin();

            void insertRow( const QString& state, const KUrl& url,
                            const KStatefulBrush &foregroundColor = KStatefulBrush(KColorScheme::View, KColorScheme::NormalText),
                            Qt::CheckState checkstate = Qt::Checked );

        private Q_SLOTS:
            void commitDiffJobFinished(KJob* job);
            void doAccept();
            void doCancel();

        Q_SIGNALS:
            void executeCommit( VcsCommitDialog* dlg );
            void cancelCommit( VcsCommitDialog* dlg );
            void accept();
            void cancel();

        private:
            void executeCommit();

            // void getDVCSfileLists(KUrl::List &resetFiles, KUrl::List &addFiles, KUrl::List &rmFiles) const;

            class Private;
            Private* const d;
    };
}

#endif // GLUONCREATOR_VCSCOMMITDIALOG

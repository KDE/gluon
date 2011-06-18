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

#ifndef VCSBRANCHWIDGET_H
#define VCSBRANCHWIDGET_H

#include "lib/gluoncreator_macros.h"

#include <vcs/models/vcseventmodel.h>

#include <KDE/KUrl>
#include <KDE/KColorScheme>
#include <KDE/KSqueezedTextLabel>
#include <KDE/KTextBrowser>

#include <QtGui/QGridLayout>
#include <QtGui/QTableView>
#include <QtGui/QWidget>
#include <QtGui/QSlider>
#include <QtGui/QStringListModel>
#include <QtCore/QModelIndex>

class QPoint;
class QModelIndex;
class QListView;
class KUrl;
class KPushButton;
class KLineEdit;

namespace KDevelop
{
    class VcsJob;
    class IDistributedVersionControl;
}

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT VcsBranchWidget : public QWidget
    {
        Q_OBJECT
        public:
            VcsBranchWidget( KDevelop::IDistributedVersionControl* vcsInterface, const QString& repositoryPath, QWidget* parent = 0 );
            virtual ~VcsBranchWidget();

        private slots:
            void createUseBranch();
            void createBranch();
            void delBranch();

        private:
            void setupUi();
            void retranslateUi();

            // UI elements
            QGridLayout* m_gridLayout;
            KLineEdit* m_newBranchName;
            KPushButton* m_createUseButton;
            KPushButton* m_createButton;
            QListView* m_branchView;
            KDevelop::IDistributedVersionControl* m_vcsInterface;
            QString m_repositoryPath;
            QStringList m_branches;
            QString m_curBranch;
            QStringListModel* m_branchNameModel;
   };
}

#endif

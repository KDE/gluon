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

#ifndef GLUONCREATOR_VCSDIFFWIDGET_H
#define GLUONCREATOR_VCSDIFFWIDGET_H

#include "lib/gluoncreator_macros.h"

#include <KDE/KTextEdit>
#include <KDE/KSqueezedTextLabel>

#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

namespace KDevelop
{
    class VcsJob;
    class VcsRevision;
}

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT VcsDiffWidget : public QWidget
    {
            Q_OBJECT
        public:
            explicit VcsDiffWidget( KDevelop::VcsJob*, QWidget* parent = 0 );
            virtual ~VcsDiffWidget();

        public:
            void setRevisions( const KDevelop::VcsRevision&, const KDevelop::VcsRevision& );

        private slots:
            void diffReady( KDevelop::VcsJob* );

        private:
            void setupUi();
            void retranslateUi();

            // UI elements
            KSqueezedTextLabel* m_revLabel;
            KDevelop::VcsJob* m_job;
            QVBoxLayout* m_vboxLayout;
            KTextEdit* m_diffDisplay;
    };
}

#endif

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Keith Rusler <xzekecomax@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef PROJECTSELECTIONDIALOG_H
#define PROJECTSELECTIONDIALOG_H

#include <KDE/KPageDialog>

namespace GluonCreator
{
    class ProjectSelectionDialog : public KPageDialog
    {
            Q_OBJECT
        public:
            enum ProjectPage
            {
                NewProjectPage,
                RecentProjectPage,
                OpenProjectPage
            };

            explicit ProjectSelectionDialog( QWidget* parent = 0, Qt::WFlags = 0 );
            ~ProjectSelectionDialog();
            void addPage( KPageWidgetItem* item, ProjectPage page );
            QString fileName() const;
        public Q_SLOTS:
            void setPage( ProjectPage page );
        private:
            Q_PRIVATE_SLOT( d, void okClicked() )
            Q_PRIVATE_SLOT( d, void projectRequested( const QString& project ) )
        private:
            class ProjectSelectionDialogPrivate;
            ProjectSelectionDialogPrivate* const d;
    };
}

#endif // PROJECTSELECTIONDIALOG_H

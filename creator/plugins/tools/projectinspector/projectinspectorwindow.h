/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef GLUONCREATOR_PROJECTINSPECTORWINDOW_H
#define GLUONCREATOR_PROJECTINSPECTORWINDOW_H

#include <QtGui/QDialog>

class QModelIndex;
namespace GluonCreator
{
    class ProjectInspectorWindow : public QDialog
    {
        Q_OBJECT
        public:
            explicit ProjectInspectorWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);
            virtual ~ProjectInspectorWindow();

            virtual QSize sizeHint() const;

        public Q_SLOTS:
            void activated( const QModelIndex& index );

        private:
            class Private;
            const QScopedPointer< Private > d;
    };
}

#endif // GLUONCREATOR_PROJECTINSPECTORWINDOW_H

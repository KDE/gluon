/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONCREATOR_FILEAREA_H
#define GLUONCREATOR_FILEAREA_H

#include "lib/gluoncreator_macros.h"

#include <QtGui/QWidget>

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT FileArea : public QWidget
    {
            Q_OBJECT
        public:
            explicit FileArea( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            virtual ~FileArea();

        public Q_SLOTS:
            void addTab( const QString& name, const QString& title );
            void removeTab( const QString& name );
            void removeTab( int index );
            void setActiveTab( const QString& name );
            void setActiveTab( int index );

        private Q_SLOTS:
            void activePartChanged( KParts::Part* part );
            void tabMoved( int, int );

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUONCREATOR_FILEAREA_H

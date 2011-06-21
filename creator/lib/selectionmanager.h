/******************************************************************************
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

#ifndef GLUON_CREATOR_SELECTIONMANAGER_H
#define GLUON_CREATOR_SELECTIONMANAGER_H

#include "gluoncreator_macros.h"

#include <core/singleton.h>

namespace GluonCore
{
    class GluonObject;
}

namespace GluonCreator
{

    class GLUONCREATOR_EXPORT SelectionManager : public GluonCore::Singleton<SelectionManager>
    {
            Q_OBJECT
            GLUON_SINGLETON( SelectionManager )
        public:
            typedef QList<GluonCore::GluonObject*> SelectionList;
            SelectionList selection() const;

        public Q_SLOTS:
            void setSelection( const SelectionList& selection );
            void clearSelection();

        Q_SIGNALS:
            void selectionChanged( SelectionManager::SelectionList );

        private:
            ~SelectionManager();

            class SelectionManagerPrivate;
            SelectionManagerPrivate* const d;
    };

}

#endif // GLUON_CREATOR_SELECTIONMANAGER_H

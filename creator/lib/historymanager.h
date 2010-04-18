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

#ifndef GLUONCREATOR_HISTORYMANAGER_H
#define GLUONCREATOR_HISTORYMANAGER_H

#include <core/singleton.h>
#include "gluoncreator_macros.h"

class KActionCollection;
class QUndoCommand;
class QVariant;

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT HistoryManager : public GluonCore::Singleton<HistoryManager>
    {
            Q_OBJECT
        public:

        public Q_SLOTS:
            void addCommand(QUndoCommand* command);

            void undo();
            void redo();

            void clear();
            void setClean();

        Q_SIGNALS:
            void historyChanged();

            void canUndoChanged(bool);
            void canRedoChanged(bool);
            void cleanChanged(bool);

        private:
            friend class GluonCore::Singleton<HistoryManager>;

            HistoryManager();
            ~HistoryManager();
            Q_DISABLE_COPY(HistoryManager)

            class HistoryManagerPrivate;
            HistoryManagerPrivate * const d;
    };
}

#endif // GLUONCREATOR_HISTORYMANAGER_H

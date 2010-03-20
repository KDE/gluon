/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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

        public slots:
            void addCommand(QUndoCommand* command);

            void undo();
            void redo();

            void clear();
            void setClean();

        signals:
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
            HistoryManagerPrivate *d;
    };
}

#endif // GLUONCREATOR_HISTORYMANAGER_H

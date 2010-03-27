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

#include "historymanager.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <KUndoStack>

using namespace GluonCreator;

template<> GLUONCREATOR_EXPORT HistoryManager* GluonCore::Singleton<HistoryManager>::m_instance = 0;

class HistoryManager::HistoryManagerPrivate
{
    public:
        HistoryManagerPrivate()
        {
            stack = new KUndoStack();
        }
        ~HistoryManagerPrivate()
        {
            delete stack;
        }

        KUndoStack* stack;
};

void HistoryManager::addCommand(QUndoCommand* command)
{
    d->stack->push(command);
    emit historyChanged();
}

void HistoryManager::redo()
{
    d->stack->redo();
    emit historyChanged();
}

void HistoryManager::undo()
{
    d->stack->undo();
    emit historyChanged();
}

void HistoryManager::clear()
{
    d->stack->clear();
}

void HistoryManager::setClean()
{
    d->stack->setClean();
}

HistoryManager::HistoryManager() : d(new HistoryManagerPrivate)
{
    connect(d->stack, SIGNAL(canRedoChanged(bool)), SIGNAL(canRedoChanged(bool)));
    connect(d->stack, SIGNAL(canUndoChanged(bool)), SIGNAL(canUndoChanged(bool)));
    connect(d->stack, SIGNAL(cleanChanged(bool)), SIGNAL(cleanChanged(bool)));
}

HistoryManager::~HistoryManager()
{
    delete d;
}

#include "historymanager.moc"

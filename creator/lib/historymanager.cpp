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

#include "historymanager.h"

#include <KDE/KUndoStack>

#include "filemanager.h"

using namespace GluonCreator;

GLUON_DEFINE_SINGLETON( HistoryManager )

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

void HistoryManager::addCommand( QUndoCommand* command )
{
    d->stack->push( command );
    emit historyChanged( command );
}

void HistoryManager::redo()
{
    if( FileManager::instance()->redoOnCurrent() )
        return;

    d->stack->redo();
    const QUndoCommand* command = d->stack->command( d->stack->index() - 1 );
    emit historyChanged( command );
}

void HistoryManager::undo()
{
    if( FileManager::instance()->undoOnCurrent() )
        return;

    d->stack->undo();
    const QUndoCommand* command = d->stack->command( d->stack->index() );
    emit historyChanged( command );
}

void HistoryManager::clear()
{
    d->stack->clear();
}

void HistoryManager::setClean()
{
    d->stack->setClean();
}

HistoryManager::HistoryManager( QObject* parent )
    : GluonCore::Singleton< GluonCreator::HistoryManager >( parent ), d( new HistoryManagerPrivate )
{
    connect( d->stack, SIGNAL(canRedoChanged(bool)), SIGNAL(canRedoChanged(bool)) );
    connect( d->stack, SIGNAL(canUndoChanged(bool)), SIGNAL(canUndoChanged(bool)) );
    connect( d->stack, SIGNAL(cleanChanged(bool)), SIGNAL(cleanChanged(bool)) );
}

HistoryManager::~HistoryManager()
{
    delete d;
}

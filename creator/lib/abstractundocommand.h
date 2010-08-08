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

#ifndef GLUONCREATOR_ABSTRACTUNDOCOMMAND_H
#define GLUONCREATOR_ABSTRACTUNDOCOMMAND_H

#include <QUndoStack>

#include "gluoncreator_macros.h"

namespace GluonCore
{
    class GluonObject;
}

namespace GluonCreator {

    class GLUONCREATOR_EXPORT AbstractUndoCommand : public QUndoCommand
    {
        public:
            AbstractUndoCommand(QUndoCommand* parent = 0);
            virtual ~AbstractUndoCommand();

            virtual void undo() = 0;
            virtual void redo() = 0;
            virtual int id() const;

            GluonCore::GluonObject * object() const;
            QString commandName() const;
	    QString commandDirection() const;

        protected:
            void setObject(GluonCore::GluonObject* obj);
            void setCommandName(const QString& name);
	    void setCommandDirection(const QString& direction);

        private:
            class AbstractUndoCommandPrivate;
            AbstractUndoCommandPrivate * const d;
    };
}

#endif // GLUONCREATOR_ABSTRACTUNDOCOMMAND_H

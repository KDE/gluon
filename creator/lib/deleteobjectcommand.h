/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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

#ifndef GLUON_CREATOR_DELETEOBJECTCOMMAND_H
#define GLUON_CREATOR_DELETEOBJECTCOMMAND_H

#include "abstractundocommand.h"
#include "gluoncreator_macros.h"

namespace GluonEngine
{
    class GameObject;
}

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT DeleteObjectCommand : public QObject,public AbstractUndoCommand
    {
        Q_OBJECT
	public:
            DeleteObjectCommand( GluonCore::GluonObject* object, GluonCore::GluonObject* parent );
            virtual ~DeleteObjectCommand();

            virtual void undo();
            virtual void redo();

        private:
            class DeleteObjectCommandPrivate;
            DeleteObjectCommandPrivate* const d;
    };
}

#endif // GLUON_CREATOR_DELETEOBJECTCOMMAND_H

/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef GLUON_SMARTS_BTSEQUENCENODE_H
#define GLUON_SMARTS_BTSEQUENCENODE_H

#include "gluon_smarts_export.h"

#include "btfactory.h"
#include "btcharacter.h"

namespace GluonSmarts
{

    class btNode;

    class GLUON_SMARTS_EXPORT btSequenceNode : public btNode
    {
            Q_OBJECT

        public:
            Q_INVOKABLE btSequenceNode( QObject* parent = 0 );
            status run( btCharacter* self );
    };
}

#endif // GLUON_SMARTS_BTSEQUENCENODE_H

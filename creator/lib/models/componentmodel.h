/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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
#ifndef GLUON_CREATOR_COMPONENTMODEL_H
#define GLUON_CREATOR_COMPONENTMODEL_H

#include "gluoncreator_macros.h"

#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT ComponentModel : public QStandardItemModel
    {
            Q_OBJECT
        public:
            ComponentModel( QObject* parent = 0 );
            ~ComponentModel();

        private:
            class ComponentModelPrivate;
            ComponentModelPrivate* const d;
    };

}

#endif // GLUON_CREATOR_COMPONENTMODEL_H

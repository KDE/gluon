/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUON_GAMEPROJECTPRIVATE_H
#define GLUON_GAMEPROJECTPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QUrl>

namespace GluonCore
{
    class GluonObject;
}

namespace GluonEngine
{
    class Scene;

    class GameProjectPrivate : public QSharedData
    {
        public:
            GameProjectPrivate();
            GameProjectPrivate( const GameProjectPrivate& other );
            ~GameProjectPrivate();

            QString description;
            QUrl homepage;
            QList<QUrl> mediaInfo;
            QUrl filename;
            Scene* entryPoint;

            static bool saveChildren( const GluonCore::GluonObject* parent );
    };
}

#endif // GLUON_GAMEPROJECTPRIVATE_H

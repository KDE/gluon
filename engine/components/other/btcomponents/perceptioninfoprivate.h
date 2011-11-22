/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#ifndef PERCEPTIONINFOPRIVATE_H
#define PERCEPTIONINFOPRIVATE_H

#include <QtCore/QDebug>
#include <QtCore/QSharedData>
#include <QtScript/QScriptEngine>
#include "engine/asset.h"

namespace GluonEngine
{
    class btPerceptionInfoScriptable;

    class PerceptionInfoPrivate : public QSharedData
    {
        public:
            PerceptionInfoPrivate( QObject* parent = 0 );
            PerceptionInfoPrivate( const PerceptionInfoPrivate& other );
            ~PerceptionInfoPrivate();

            btPerceptionInfoScriptable* info;
            QScriptEngine engine;

            QScriptValue drawFunc;
            QScriptValue updateFunc;
            QScriptValue getAdjustedValueFunc;

            GluonEngine::Asset* script;
    };
}

#endif

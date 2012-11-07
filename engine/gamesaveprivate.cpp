/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Vinay S Rao <sr.vinay@gmail.com>
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

#include "gamesaveprivate.h"
#include "gamesave.h"

#include "game.h"
#include "gameproject.h"

#include <core/directoryprovider.h>
#include <QDir>
#include <QFileInfo>

using namespace GluonEngine;

GameSavePrivate::GameSavePrivate( GameSave* sg )
    : s( sg )
{
    saveGamesDirectory = GluonCore::DirectoryProvider::instance()->saveGamesDirectory();
    userName = GluonEngine::Game::instance()->gameProject()->userName();
    saveGamesDirectory += '/' + userName;
}

GameSavePrivate::~GameSavePrivate()
{
}

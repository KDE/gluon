/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#include "gameviewitem.h"

using namespace GluonPlayer;

GameViewItem::GameViewItem(const QString& gameName, const QString& gameDescription,
                           const QString& projectDirName, const QString& projectFileName, const Status& status,
                           const QString& id)
    : m_gameName(gameName)
    , m_gameDescription(gameDescription)
    , m_projectDirName(projectDirName)
    , m_projectFileName(projectFileName)
    , m_status(status)
    , m_id(id)
{
}

QString GameViewItem::gameName() const
{
    return m_gameName;
}

QString GameViewItem::gameDescription() const
{
    return m_gameDescription;
}

QString GameViewItem::projectDirName() const
{
    return m_projectDirName;
}

QString GameViewItem::projectFileName() const
{
    return m_projectFileName;
}

QStringList GameViewItem::screenshotUrls() const
{
    return m_screenshotUrls;
}

QString GameViewItem::id() const
{
    return m_id;
}

GameViewItem::Status GameViewItem::status() const
{
    return m_status;
}

#include "gameviewitem.moc"

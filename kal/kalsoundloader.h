/*
* This file is part of the Gluon project.
* Copyright (C) 2000 Geert Jansen <jansen@kde.org>
* Copyright (C) 2000 Antonio Larrosa <larrosa@kde.org>
* Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/

#ifndef KALSOUNDLOADER_H
#define KALSOUNDLOADER_H

#include <QObject>

#include "kalengine_export.h"

class KALSoundLoaderPrivate;
class KComponentData;
class KStandardDirs;

/**
* @class KALSoundLoader kalsoundloader.h <KALSoundLoader>
* KALSoundLoader ...
*/
class KALENGINE_EXPORT KALSoundLoader : public QObject
{
    Q_OBJECT

public:
    /**
    * Constructs a soundloader.
    * @param componentData the KComponentData to use to create this icon loader.
    *
    * Usually, you use the default soundloader, which can be accessed via
    * KSoundLoader::global(), so you hardly ever have to create a
    * soundloader object yourself. That one is the current KComponentData's
    * (typically KApplication's) iconloader.
    */
    explicit KALSoundLoader(const KComponentData &componentData, QObject* parent = 0);

    QString soundPath(const QString &name) const;

    /**
    * Returns the global icon loader initialized with the global KComponentData.
    * Therefore you must have a KComponentData instantiated before calling this.
    * @return global icon loader
    */
    static KALSoundLoader* global();

private:
    KALSoundLoaderPrivate *d;
};

#endif // KALSOUNDLOADER_H

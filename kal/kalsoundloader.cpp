/*
* This file is part of the KALEngine project.
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

#include "kalsoundloader.h"

#include <KDE/KStandardDirs>
#include <KDE/KComponentData>

class KALSoundLoaderPrivate
{
public:
    KALSoundLoaderPrivate() {}
    virtual ~KALSoundLoaderPrivate() {}

    /**
    * @internal
    * Remove the extension of the sound file, which can only be .wav
    * @param the file name
    * @return the file name without extension or @p name if the extension
    * could not be removed
    */
    QString removeSoundExtension(const QString &name) const;

    KStandardDirs *standardDirs;
};

// stolen from KIconLoader::KIconLoader(const KComponentData &componentData, QObject* parent)
KALSoundLoader::KALSoundLoader(const KComponentData &componentData, QObject* parent)
        : QObject(parent)
{
    setObjectName(componentData.componentName());
    d = new KALSoundLoaderPrivate;
    d->standardDirs = new KStandardDirs;
}

// stolen from KIconLoader::iconPath
QString KALSoundLoader::soundPath(const QString &_name) const
{
    if (_name.isEmpty()
#ifdef Q_OS_WIN
            || (_name.length() > 1 &&
                (_name[0].isLetter() && _name[1] == QLatin1Char(':') ||
                 _name[0] == '/'     && _name[1] == '/' ||
                 _name[0] == '\\'    && _name[1] == '\\')))
#else
            || _name[0] == '/')
#endif
    {
        // we have either an absolute path or nothing to work with
        return _name;
    }

    QString name = d->removeSoundExtension(_name);

    static const QString &wav_ext = KGlobal::staticQString(".wav");
    QString path = d->standardDirs->findResource("sound", name + wav_ext);

    return path;
}

// stolen from KIconLoader::removeIconExtension
QString KALSoundLoaderPrivate::removeSoundExtension(const QString &name) const
{
    if (name.endsWith(QLatin1String(".wav"))) {
        return name.left(name.length() - 4);
    }

    return name;
}

/*** the global sound loader ***/
K_GLOBAL_STATIC_WITH_ARGS(KALSoundLoader, globalSoundLoader, (KGlobal::mainComponent(), 0))

KALSoundLoader *KALSoundLoader::global()
{
    return globalSoundLoader;
}

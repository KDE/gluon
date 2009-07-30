/*
* This file is part of the Gluon project.
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
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

#ifndef KALENGINE2_H
#define KALENGINE2_H

#include "kalsource.h"
#include "kalbuffer.h"
#include "kalphonon.h"

#include <Phonon/Global>
#include <KDebug>

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QList>

#include <alc.h>
#include <alut.h>

class KALSource;
class KALBuffer;

class KALEngine : public QObject
{
private:
    KALEngine(QString deviceName = QString(), QObject *parent = 0);
    KALEngine(Phonon::Category category, QObject *parent = 0);
    ~KALEngine();

public:
    bool setDevice(QString deviceName);

    ALCcontext * context() {
        return m_context;
    }

    ALCdevice* device() {
        return m_device;
    }

    static QStringList deviceList();

    static KALEngine *getInstance(QString deviceName = QString());
    static KALEngine *getInstance(Phonon::Category category);

    static void kill();

    int sourceCount() {
        return m_sourceList.size();
    }

    void addSource(KALSource * source) {
        m_sourceList.append(source);
    }
    void removeSource(KALSource * source) {
        m_sourceList.removeOne(source);
    }

    void addBuffer(KALBuffer * buffer) {
        m_bufferList.append(buffer);
    }
    void removeBuffer(KALBuffer * buffer) {
        m_bufferList.removeOne(buffer);
    }

private:
    static KALEngine *instance;
    ALCcontext *m_context;
    ALCdevice *m_device;
    KALPhonon *m_phonon;
    QList<KALSource *> m_sourceList;
    QList<KALBuffer *> m_bufferList;
};

#endif // KALENGINE2_H

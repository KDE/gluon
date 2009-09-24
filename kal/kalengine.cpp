/*
* This file is part of the Gluon project.
* Copyright (C) 2007 Laurent Gomila <laurent.gom@gmail.com>
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

#include "kalengine.h"

#include <QtCore/QCoreApplication>

KALEngine *KALEngine::m_instance = NULL;

KALEngine::KALEngine(QString deviceName, QObject *parent)
    : QObject(parent)
{
    alutInitWithoutContext(0, 0);
    m_context = NULL;
    m_device = NULL;

    if (setDevice(deviceName)) {
        if (deviceName.isEmpty()) {
            kDebug() << "set device to default";
        } else {
            kDebug() << "set device to " << deviceName;
        }
    } else {
        kDebug() << "cannot set openAL device...";
    }

    kDebug() << alGetError();
}

KALEngine::KALEngine(Phonon::Category category, QObject *parent)
{
    m_phonon = new KALPhonon(this);
    m_phonon->setCategory(category);
}

KALEngine::~KALEngine()
{
    qDeleteAll(m_sourceList);
    qDeleteAll(m_bufferList);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

// TODO: factor the getInstance or remove one of them
KALEngine *KALEngine::instance(QString deviceName)
{
    if (!m_instance) {
        QObject *parent = QCoreApplication::instance();
        if (!parent) {
            kWarning() << "No QCoreApplication instance found, the KALEngine instance may be leaked when leaving";
        }
        m_instance =  new KALEngine(deviceName, parent);
    }
    return m_instance;
}

KALEngine *KALEngine::instance(Phonon::Category category)
{
    if (!m_instance) {
        QObject *parent = QCoreApplication::instance();
        if (!parent) {
            kWarning() << "No QCoreApplication instance found, the KALEngine instance may be leaked when leaving";
        }
        m_instance =  new KALEngine(category, parent);
    }
    return m_instance;
}

QStringList KALEngine::deviceList()
{
    const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

    // alcGetString returns a list of devices separated by a null char (the list itself ends with a double null char)
    // So we can't pass it directly to QStringList
    QStringList deviceStringList;
    if (devices) {
        while (strlen(devices) > 0) {
            deviceStringList << QString(devices);
            devices += strlen(devices) + 1;
        }
    }
    return deviceStringList;
}

bool KALEngine::setDevice(QString deviceName)
{
    if (m_device) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(m_context);
        alcCloseDevice(m_device);
    }

    if (!deviceName.isEmpty()) {
        m_device = alcOpenDevice(deviceName.toUtf8());
    } else {
        m_device = alcOpenDevice(0);
    }

    if (!m_device) {
        return false;
    }

    m_context = alcCreateContext(m_device, 0);

    if (!m_context) {
        return false;
    }

    if (!alcMakeContextCurrent(m_context)) {
        return false;
    }

    return true;
}
void KALEngine::disableAllSound()
{
  KALEngine * al  = instance();
  foreach ( KALSound * sound,  *al->getSoundList())
  sound->pause();
}
void KALEngine::enableAllSound()
{
  KALEngine * al  = instance();
  foreach ( KALSound * sound,  *al->getSoundList())
  sound->play();
}
bool KALEngine::isExtensionSupported(QString name)
{
  if (alcIsExtensionPresent(instance()->device(), name.toUtf8()) == ALC_TRUE)
      return true;
  else return false;

}
